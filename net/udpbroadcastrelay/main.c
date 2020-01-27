/*
******************************************************************
udp-broadcast-relay-redux
    Relays UDP broadcasts to other networks, forging
    the sender address.

Copyright (c) 2017 Michael Morrison <github.com/sonicsnes>
Copyright (c) 2003 Joachim Breitner <mail@joachim-breitner.de>
Copyright (C) 2002 Nathan O'Sullivan

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
******************************************************************
*/

#define MAXIFS    256
#define MAXMULTICAST 256
/*
 * MAXID used to be 99 when TTL was marked with the ID but
 * now that DSCP is used it needs to be limited to 6 bits.
 */
#define MAXID   63
#define DPRINT  if (debug) printf
#define IPHEADER_LEN 20
#define UDPHEADER_LEN 8
#define HEADER_LEN (IPHEADER_LEN + UDPHEADER_LEN)
#define TTL_ID_OFFSET 64
#define SIGF_TERM 0x1

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#ifdef __FreeBSD__
#include <net/if.h>
#include <net/if_dl.h>
#else
#include <linux/if.h>
#endif
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>



static int exit_ok = 0;
static sig_atomic_t sig_flags = 0;
static char g_pidfile[128];

/* list of addresses and interface numbers on local machine */
struct Iface {
    struct in_addr dstaddr;
    struct in_addr ifaddr;
    int ifindex;
    int raw_socket;
};
static struct Iface ifs[MAXIFS];

/* Where we forge our packets */
static u_char gram[4096]=
{
    0x45,    0x00,    0x00,    0x26,
    0x12,    0x34,    0x00,    0x00,
    0xFF,    0x11,    0,    0,
    0,    0,    0,    0,
    0,    0,    0,    0,
    0,    0,    0,    0,
    0x00,    0x12,    0x00,    0x00,
    '1','2','3','4','5','6','7','8','9','0'
};

void inet_ntoa2(struct in_addr in, char* chr, int len) {
    char* from = inet_ntoa(in);
    strncpy(chr, from, len);
}

void sig_term_handler(int signum, siginfo_t *info, void *ptr)
{
    unlink(g_pidfile);
    exit(0);
}

void catch_sigterm()
{
    static struct sigaction _sigact;

    memset(&_sigact, 0, sizeof(_sigact));
    _sigact.sa_sigaction = sig_term_handler;
    _sigact.sa_flags = SA_SIGINFO;

    sigaction(SIGTERM, &_sigact, NULL);
}

void display_usage(FILE *stream, const char *arg0) {
    fprintf(stream, "usage: %s [--id ID] [--port udp-port]\n"
	    "       [--dev dev1] [--dev dev2] [--dev devX]\n"
	    "       [-s IP] [--multicast ip1] [--multicast ipX]\n"
            "       [-t|--ttl-id] [-d] [-f]\n"
	    "       [-h|--help]\n", arg0);
}

void display_help(const char *arg0) {
    printf("This program listens for packets on a specified UDP broadcast\n"
	   "port. When a packet is received, it sends that packet to all\n"
	   "specified interfaces but the one it came from as though it\n"
	   "originated from the original sender.\n"
	   "The primary purpose of this is to allow devices or game servers\n"
	   "on separated local networks (Ethernet, WLAN, VLAN) that use udp\n"
	   "broadcasts to find each other to do so.\n");
    printf("Required Parameters:\n"
	   "  --id ID  Set a unique ID for this instance of the tool.\n"
	   "           Valid range 1 - %i. The IP DSCP field of a relayed\n"
	   "           packet is set to this value so the tool may\n"
	   "           identify and drop already relayed packets in order\n"
	   "           to avoid packet storms.\n"
	   "  --port udp-port   Destination UDP port to listen for.\n"
	   "                    Valid range 1 - 65535.\n"
	   "                    e.g.  5353 - mDNS/Chromecast/Apple Bonjour\n"
	   "                          1900 - UPnP Discovery/SSDP\n"
	   "                          37 - NetBIOS name service (Windows)\n"
	   "                          38 - SMB Browser (Windows)\n"
	   "                    Only specify one udp-port per instance.\n"
	   "  --dev device   Name of an interface to listen for and to \n"
	   "                 relay packets to. This option must be specified\n"
	   "                 at least twice for two separate interfaces in\n"
	   "                 order for this tool to have any effect.\n", MAXID);
    printf("Optional Parameters:\n"
	   "  -s IP    Sets the source IP of forwarded packets. If not\n"
	   "           specified the original IP source address is used.\n"
	   "           Special values :\n"
	   "           1.1.1.1 - Use the outgoing interface ip address as\n"
	   "                     source IP. Also forces the outgoing packet\n"
	   "                     source UDP port to the same as the destination\n"
	   "                     UDP port.\n"
	   "           1.1.1.2 - Use the outgoing interface ip address as \n"
	   "                     source IP. Does not modify UDP ports.\n"
	   "           These special values help in rare cases e.g. Chromecast\n"
	   "  --multicast IP   As well as listening for broadcasts the program\n"
	   "                   will listen for and relay multicast packets\n"
	   "                   using the specified multicast IP address(es).\n"
	   "                   e.g. 224.0.0.251 - mDNS/Chromecast/Apple Bonjour\n"
	   "                        239.255.255.250 - UPnP Discovery/SSDP\n"
	   "                   This argument may be specified more than once.\n"
	   "  --ttl-id|-t   Preserve DSCP and mark relayed packets by setting\n"
	   "                the IP TTL header field to ID + %i. This is how the\n"
	   "                original version of this tool operated by default.\n"
	   "  -d       Enables debugging.\n"
	   "  -f       Forces forking to background. A PID file will be created\n"
	   "           at /var/run/udpbroadcastrelay_ID.pid\n"
	   "  --help|-h   Display this detailed help dialog.\n", TTL_ID_OFFSET);
}

int main(int argc,char **argv) {
    /* Debugging, forking, other settings */
    FILE *pidfp;
    int debug = 0, forking = 0, pid;
    int use_ttl_id = 0;
    u_int16_t port = 0;
    u_char id = 0;
    char *usr_pid = 0;
    char* multicastAddrs[MAXMULTICAST];
    int multicastAddrsNum = 0;
    char* interfaceNames[MAXIFS];
    int interfaceNamesNum = 0;
    in_addr_t spoof_addr = 0;

    /* Address broadcast packet was sent from */
    struct sockaddr_in rcv_addr;
    struct msghdr rcv_msg;
    struct iovec iov;
    iov.iov_base = gram + HEADER_LEN;
    iov.iov_len = 4006 - HEADER_LEN - 1;
    u_char pkt_infos[16384];
    rcv_msg.msg_name = &rcv_addr;
    rcv_msg.msg_namelen = sizeof(rcv_addr);
    rcv_msg.msg_iov = &iov;
    rcv_msg.msg_iovlen = 1;
    rcv_msg.msg_control = pkt_infos;
    rcv_msg.msg_controllen = sizeof(pkt_infos);
    static char pidfile[128];
   
    int child_pid;
#ifndef HAVE_ARC4RANDOM
srandom(time(NULL) & getpid());
#endif



    if(argc < 2) {
	display_usage(stderr, argv[0]);
	exit(1);
    }

    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i],"-d") == 0) {
            DPRINT ("Debugging Mode enabled\n");
            debug = 1;
        }
	if ((strcmp(argv[i], "--help") == 0) ||
	    (strcmp(argv[i], "-h") == 0)) {
	    display_usage(stdout, argv[0]);
	    display_help(argv[0]);
	    exit(0);
	}
    }

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i],"-d") == 0) {
            // Already handled
        } else if (strcmp(argv[i],"-f") == 0) {
            DPRINT ("Forking Mode enabled\n");
            forking = 1;
        }
        else if (strcmp(argv[i],"-s") == 0) {
            /* INADDR_NONE is a valid IP address (-1 = 255.255.255.255),
             * so inet_pton() would be a better choice. But in this case it
             * does not matter. */
            i++;
            spoof_addr = inet_addr(argv[i]);
            if (spoof_addr == INADDR_NONE) {
                fprintf (stderr,"invalid IP address: %s\n", argv[i]);
                exit(1);
            }
            DPRINT ("Outgoing source IP set to %s\n", argv[i]);
        }
        else if (strcmp(argv[i],"--id") == 0) {
            i++;
            id = atoi(argv[i]);
            DPRINT ("ID set to %i\n", id);
        }
        else if (strcmp(argv[i],"--port") == 0) {
            i++;
            port = atoi(argv[i]);
            DPRINT ("Port set to %i\n", port);
        }
        else if (strcmp(argv[i],"--dev") == 0) {
	    if (interfaceNamesNum >= MAXIFS) {
		fprintf(stderr, "More than %i interfaces specified.\n", MAXIFS);
		exit(1);
	    }
            i++;
            interfaceNames[interfaceNamesNum] = argv[i];
            interfaceNamesNum++;
        }
        else if (strcmp(argv[i],"--pid") == 0) {
            i++;
            usr_pid = argv[i];            
        }
        else if (strcmp(argv[i],"--multicast") == 0) {
	    if (multicastAddrsNum >= MAXMULTICAST) {
		fprintf(stderr, "More than %i multicast addresses specified", MAXMULTICAST);
		exit(1);
	    }
            i++;
            multicastAddrs[multicastAddrsNum] = argv[i];
            multicastAddrsNum++;
        }
	else if ((strcmp(argv[i], "--ttl-id") == 0) ||
		 (strcmp(argv[i], "-t") == 0)) {
	    use_ttl_id = 1;
	}
        else if (strncmp(argv[i], "-", 1) == 0) {
            fprintf (stderr, "Unknown arg: %s\n", argv[i]);
            exit(1);
        }
        else {
            break;
        }
    }

    if (id < 1 || id > MAXID)
    {
        fprintf (stderr,"ID argument %i not between 1 and %i\n", id, MAXID);
        exit(1);
    }
    if (port < 1 || port > 65535) {
        fprintf (stderr,"Port argument not valid\n");
        exit(1);
    }


	
    
    u_char ttl = 0;
    u_char tos = 0;
    if (use_ttl_id) {
	ttl = id + TTL_ID_OFFSET;
	DPRINT ("ID: %i (ttl: %i), Port %i\n",id,ttl,port);
    } else {
	/*
	 * DSCP occupies the most significant 6 bits of the IP
	 * TOS field. We do not use the remaining 2 bits (ECN)
	 * because there are reports that in rare cases hosts
	 * can react poorly to these being set spuriously.
	 */
	tos = id << 2;
	DPRINT ("ID: %i (DSCP: %i, ToS: 0x%02x), Port %i\n", id, id,
		tos, port);
    }



    /* We need to find out what IP's are bound to this host - set up a temporary socket to do so */
    int fd;
     if((fd=socket(AF_INET,SOCK_RAW,IPPROTO_RAW)) < 0)
    {
          perror("socket");
        fprintf(stderr,"You must be root to create a raw socket\n");
          exit(1);
      };


    /* For each interface on the command line */
    int maxifs = 0;
    for (int i = 0; i < interfaceNamesNum; i++) {
        struct Iface* iface = &ifs[maxifs];

        struct ifreq basereq;
        strncpy(basereq.ifr_name,interfaceNames[i],IFNAMSIZ);

        /* Request index for this interface */
        {
            #ifdef ___APPLE__
                /*
                TODO: Supposedly this works for all OS, including non-Apple, 
                and could replace the code below
                */
                iface->ifindex = if_nametoindex(interfaceNames[i]);
            #else
                struct ifreq req;
                memcpy(&req, &basereq, sizeof(req));
                if (ioctl(fd,SIOCGIFINDEX, &req) < 0) {
                    perror("ioctl(SIOCGIFINDEX)");
                    exit(1);
                }
                #ifdef __FreeBSD__
                iface->ifindex = req.ifr_index;
                #else
                iface->ifindex = req.ifr_ifindex;
                #endif
            #endif
        }

        /* Request flags for this interface */
        short ifFlags;
        {
            struct ifreq req;
            memcpy(&req, &basereq, sizeof(req));
            if (ioctl(fd,SIOCGIFFLAGS, &req) < 0) {
                perror("ioctl(SIOCGIFFLAGS)");
                exit(1);
            }
            ifFlags = req.ifr_flags;
        }

        /* if the interface is not up or a loopback, ignore it */
        if ((ifFlags & IFF_UP) == 0 || (ifFlags & IFF_LOOPBACK)) {
            continue;
        }

        /* Get local IP for interface */
        {
            struct ifreq req;
            memcpy(&req, &basereq, sizeof(req));
            if (ioctl(fd,SIOCGIFADDR, &req) < 0) {
                perror("ioctl(SIOCGIFADDR)");
                exit(1);
            }
            memcpy(
                &iface->ifaddr,
                &((struct sockaddr_in *)&req.ifr_addr)->sin_addr,
                sizeof(struct in_addr)
            );
        }

        /* Get broadcast address for interface */
        {
            struct ifreq req;
            memcpy(&req, &basereq, sizeof(req));
            if (ifFlags & IFF_BROADCAST) {
                if (ioctl(fd,SIOCGIFBRDADDR, &req) < 0) {
                    perror("ioctl(SIOCGIFBRDADDR)");
                    exit(1);
                }
                memcpy(
                    &iface->dstaddr,
                    &((struct sockaddr_in *)&req.ifr_broadaddr)->sin_addr,
                    sizeof(struct in_addr)
                );
            } else {
                if (ioctl(fd,SIOCGIFDSTADDR, &req) < 0) {
                    perror("ioctl(SIOCGIFBRDADDR)");
                    exit(1);
                }
                memcpy(
                    &iface->dstaddr,
                    &((struct sockaddr_in *)&req.ifr_dstaddr)->sin_addr,
                    sizeof(struct in_addr)
                );
            }
        }

        char ifaddr[255];
        inet_ntoa2(iface->ifaddr, ifaddr, sizeof(ifaddr));
        char dstaddr[255];
        inet_ntoa2(iface->dstaddr, dstaddr, sizeof(dstaddr));

        DPRINT(
            "%s: %i / %s / %s\n",
            basereq.ifr_name,
            iface->ifindex,
            ifaddr,
            dstaddr
        );

        // Set up a one raw socket per interface for sending our packets through
        if((iface->raw_socket = socket(AF_INET,SOCK_RAW,IPPROTO_RAW)) < 0) {
            perror("socket");
            exit(1);
        }
        {
            int yes = 1;
            int no = 0;
            if (setsockopt(iface->raw_socket, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes))<0) {
                perror("setsockopt SO_BROADCAST");
                exit(1);
            }
            if (setsockopt(iface->raw_socket, IPPROTO_IP, IP_HDRINCL, &yes, sizeof(yes))<0) {
                perror("setsockopt IP_HDRINCL");
                exit(1);
            }
            if (setsockopt(iface->raw_socket, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(yes))<0) {
                perror("setsockopt SO_REUSEPORT");
                exit(1);
            }
            #ifdef __FreeBSD__
                if((setsockopt(iface->raw_socket, IPPROTO_IP, IP_MULTICAST_LOOP, &no, sizeof(no))) < 0) {
                    perror("setsockopt IP_MULTICAST_LOOP");
                }
                if((setsockopt(iface->raw_socket, IPPROTO_IP, IP_MULTICAST_IF, &iface->ifaddr, sizeof(iface->ifaddr))) < 0) {
                    perror("setsockopt IP_MULTICAST_IF");
                }
		if (use_ttl_id) {
		    int setttl = ttl;
		    if((setsockopt(iface->raw_socket, IPPROTO_IP, IP_MULTICAST_TTL, &setttl, sizeof(setttl))) < 0) {
			perror("setsockopt IP_MULTICAST_TTL");
		    }
		}
            #else
                // bind socket to dedicated NIC (override routing table)
                if (setsockopt(iface->raw_socket, SOL_SOCKET, SO_BINDTODEVICE, interfaceNames[i], strlen(interfaceNames[i])+1)<0)
                {
                    perror("setsockopt SO_BINDTODEVICE");
                    exit(1);
                };
            #endif
        }

        /* ... and count it */
        maxifs++;
    }

    DPRINT("found %i interfaces total\n",maxifs);

    /* Free our allocated buffer and close the socket */
    close(fd);

    /* Create our broadcast receiving socket */
    int rcv;
    {
        if((rcv=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) < 0)
          {
              perror("socket");
              exit(1);
          }
        int yes = 1;
        if(setsockopt(rcv, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes))<0){
            perror("SO_BROADCAST on rcv");
            exit(1);
        };
        if (setsockopt(rcv, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(yes))<0) {
            perror("SO_REUSEPORT on rcv");
            exit(1);
        }
        #ifdef __FreeBSD__
            if(setsockopt(rcv, IPPROTO_IP, IP_RECVTTL, &yes, sizeof(yes))<0){
                perror("IP_RECVTTL on rcv");
                exit(1);
            };
	    if(setsockopt(rcv, IPPROTO_IP, IP_RECVTOS, &yes, sizeof(yes))<0){
		perror("IP_RECVTOS on rcv");
		exit(1);
	    };
            if(setsockopt(rcv, IPPROTO_IP, IP_RECVIF, &yes, sizeof(yes))<0){
                perror("IP_RECVIF on rcv");
                exit(1);
            };
            if(setsockopt(rcv, IPPROTO_IP, IP_RECVDSTADDR, &yes, sizeof(yes))<0){
                perror("IP_RECVDSTADDR on rcv");
                exit(1);
            };
        #else
            if(setsockopt(rcv, SOL_IP, IP_RECVTTL, &yes, sizeof(yes))<0){
                perror("IP_RECVTTL on rcv");
                exit(1);
            };
	    if(setsockopt(rcv, SOL_IP, IP_RECVTOS, &yes, sizeof(yes))<0){
		perror("IP_RECVTOS on rcv");
		exit(1);
	    };
            if(setsockopt(rcv, SOL_IP, IP_PKTINFO, &yes, sizeof(yes))<0){
                perror("IP_PKTINFO on rcv");
                exit(1);
            };
        #endif
        for (int i = 0; i < multicastAddrsNum; i++) {
            for (int x = 0; x < maxifs; x++) {
                struct ip_mreq mreq;
                memset(&mreq, 0, sizeof(struct ip_mreq));
                mreq.imr_interface.s_addr = ifs[x].ifaddr.s_addr;
                mreq.imr_multiaddr.s_addr = inet_addr(multicastAddrs[i]);
                DPRINT("IP_ADD_MEMBERSHIP:\t\t%s %s\n",inet_ntoa(ifs[x].ifaddr),multicastAddrs[i]);
                if(setsockopt(rcv, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))<0){
                    perror("IP_ADD_MEMBERSHIP on rcv");
                    exit(1);
                }
            }
        }

        struct sockaddr_in bind_addr;
        bind_addr.sin_family = AF_INET;
        bind_addr.sin_port = htons(port);
        bind_addr.sin_addr.s_addr = INADDR_ANY;
        if(bind(rcv, (struct sockaddr *)&bind_addr, sizeof(bind_addr)) < 0) {
            perror("bind");
            fprintf(stderr,"rcv bind\n");
            exit(1);
        }
    }


    DPRINT("Done Initializing\n\n");
    sprintf(pidfile,"/var/run/udpbroadcastrelay_%d.pid",id);
    if ((pidfp = fopen(pidfile, "w")) != NULL) {                 
    fprintf(pidfp, "%d\n", child_pid);
    fclose(pidfp);
    strcpy(g_pidfile,pidfile);
    }     
    /* Fork to background */
    if (! debug) {
        if (forking && (child_pid=fork())) {
            sprintf(pidfile,"/var/run/udpbroadcastrelay_%d.pid",id);
            if ((pidfp = fopen(pidfile, "w")) != NULL) {                 
            fprintf(pidfp, "%d\n", child_pid);
            fclose(pidfp);
            strcpy(g_pidfile,pidfile);
            }
        
        exit(0);
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);
        }
    }
    

    for (;;) /* endless loop */
    {
        
        catch_sigterm();
        /* Receive a broadcast packet */
        int len = recvmsg(rcv,&rcv_msg,0);
        if (len <= 0) continue;    /* ignore broken packets */

        /* Find the ToS, ttl and the receiving interface */
        struct cmsghdr *cmsg;
        int rcv_ttl = 0;
	int rcv_tos = 0;
	int found_rcv_tos = 0;
        int rcv_ifindex = 0;
        struct in_addr rcv_inaddr;
        int foundRcvIf = 0;
        int foundRcvIp = 0;
        if (rcv_msg.msg_controllen > 0) {
            for (cmsg=CMSG_FIRSTHDR(&rcv_msg);cmsg;cmsg=CMSG_NXTHDR(&rcv_msg,cmsg)) {
                #ifdef __FreeBSD__
                    if (cmsg->cmsg_type==IP_RECVTTL) {
                        rcv_ttl = *(int *)CMSG_DATA(cmsg);
                    }
		    if (cmsg->cmsg_type==IP_RECVTOS) {
			rcv_tos = *(int *)CMSG_DATA(cmsg);
			found_rcv_tos = 1;
		    }
                    if (cmsg->cmsg_type==IP_RECVDSTADDR) {
                        rcv_inaddr=*((struct in_addr *)CMSG_DATA(cmsg));
                        foundRcvIp = 1;
                    }
                    if (cmsg->cmsg_type==IP_RECVIF) {
                        rcv_ifindex=((struct sockaddr_dl *)CMSG_DATA(cmsg))->sdl_index;
                        foundRcvIf = 1;
                    }
                #else
                    if (cmsg->cmsg_type==IP_TTL) {
                        rcv_ttl = *(int *)CMSG_DATA(cmsg);
                    }
		    if (cmsg->cmsg_type==IP_TOS) {
			rcv_tos = *(int *)CMSG_DATA(cmsg);
			found_rcv_tos = 1;
		    }
                    if (cmsg->cmsg_type==IP_PKTINFO) {
                        rcv_ifindex=((struct in_pktinfo *)CMSG_DATA(cmsg))->ipi_ifindex;
                        foundRcvIf = 1;
                        rcv_inaddr=((struct in_pktinfo *)CMSG_DATA(cmsg))->ipi_addr;
                        foundRcvIp = 1;
                    }
                #endif
            }
        }

        if (!foundRcvIp) {
            perror("Source IP not found on incoming packet\n");
            continue;
        }
        if (!foundRcvIf) {
            perror("Interface not found on incoming packet\n");
            continue;
        }
        if (!rcv_ttl) {
            perror("TTL not found on incoming packet\n");
            continue;
        }
	if (!found_rcv_tos) {
	    if (use_ttl_id) {
		/*
		 * If we're not using DSCP as the tag field then
		 * this error doesn't matter but print the warning
		 * anyway.
		 */
		perror("Warning : ToS not found on incoming packet - continuing processing\n");
	    } else {
		perror("ToS not found on incoming packet\n");
		continue;
	    }
	}

        struct Iface* fromIface = NULL;
        for (int iIf = 0; iIf < maxifs; iIf++) {
            if (ifs[iIf].ifindex == rcv_ifindex) {
                fromIface = &ifs[iIf];
            }
        }

        struct in_addr origFromAddress = rcv_addr.sin_addr;
        u_short origFromPort = ntohs(rcv_addr.sin_port);
        struct in_addr origToAddress = rcv_inaddr;
        u_short origToPort = port;

        gram[HEADER_LEN + len] = 0;

        char origFromAddressStr[255];
        inet_ntoa2(origFromAddress, origFromAddressStr, sizeof(origFromAddressStr));
        char origToAddressStr[255];
        inet_ntoa2(origToAddress, origToAddressStr, sizeof(origToAddressStr));
        DPRINT("<- [ %s:%d -> %s:%d (iface=%d len=%i tos=0x%02x DSCP=%i ttl=%i)\n",
            origFromAddressStr, origFromPort,
            origToAddressStr, origToPort,
	    rcv_ifindex, len, rcv_tos,
	    rcv_tos >> 2, rcv_ttl
        );

	if (use_ttl_id) {
	    if (rcv_ttl == ttl) {
		DPRINT("IP TTL (%i) matches ID (%i) + %i. Packet Ignored.\n\n",
		       rcv_ttl, id, TTL_ID_OFFSET);
		continue;
	    }
        } else {
	    if ((rcv_tos & 0xfc) == tos) {
		DPRINT("IP DSCP (%i) matches ID. IP ToS 0x%2x. Packet Ignored.\n\n",
		       tos >> 2, tos);
		continue;
	    }
	}
        if (!fromIface) {
            DPRINT("Not from managed iface\n\n");
            continue;
        }

        /* Iterate through our interfaces and send packet to each one */
        for (int iIf = 0; iIf < maxifs; iIf++) {
            struct Iface* iface = &ifs[iIf];

            /* no bounces, please */
            if (iface == fromIface) {
                continue;
            }

            struct in_addr fromAddress;
            u_short fromPort;
            if (spoof_addr == inet_addr("1.1.1.1")) {
                fromAddress = iface->ifaddr;
                fromPort = port;
            } else if (spoof_addr == inet_addr("1.1.1.2")) {
                fromAddress = iface->ifaddr;
                fromPort = origFromPort;
            } else if (spoof_addr) {
                fromAddress.s_addr = spoof_addr;
                fromPort = origFromPort;
            } else {
                fromAddress = origFromAddress;
                fromPort = origFromPort;
            }

            struct in_addr toAddress;
            if (rcv_inaddr.s_addr == INADDR_BROADCAST
                || rcv_inaddr.s_addr == fromIface->dstaddr.s_addr) {
                // Received on interface broadcast address -- rewrite to new interface broadcast addr
                toAddress = iface->dstaddr;
            } else {
                // Send to whatever IP it was originally to
                toAddress = rcv_inaddr;
            }
            u_short toPort = origToPort;

            char fromAddressStr[255];
            inet_ntoa2(fromAddress, fromAddressStr, sizeof(fromAddressStr));
            char toAddressStr[255];
            inet_ntoa2(toAddress, toAddressStr, sizeof(toAddressStr));
            DPRINT (
                "-> [ %s:%d -> %s:%d (iface=%d len=%i ",
                fromAddressStr, fromPort,
                toAddressStr, toPort,
                iface->ifindex, len);
	    if (use_ttl_id) {
		DPRINT("tos=0x%02x DSCP=%i ttl=%i)\n",
		       rcv_tos, rcv_tos >> 2, ttl);
	    } else {
		DPRINT("tos=0x%02x DSCP=%i ttl=%i)\n",
		       tos + (rcv_tos & 0x03), tos >> 2, rcv_ttl);
	    }
            /* Send the packet */

	    if (use_ttl_id) {
		/* Set IP TTL field */
		/* Note. The following statement has no effect on
		 * multicast packets, only on relayed broadcasts.
		 * For mcast packets we have to set socket
		 * option IP_MULTICAST_TTL to change TTL */
		gram[8] = ttl;
	    } else {
		/*
		 * Set IP ToS byte so that DSCP = instance ID and ECN is
		 * preserved from the original packet.
		 */
		gram[1] = tos + (rcv_tos & 0x03);
		/* Set TTL to the same as the received packet */
		gram[8] = rcv_ttl;
		if((setsockopt(iface->raw_socket, IPPROTO_IP, IP_MULTICAST_TTL, &rcv_ttl, sizeof(rcv_ttl))) < 0) {
		    perror("setsockopt IP_MULTICAST_TTL");
		}
	    }
            memcpy(gram+12, &fromAddress.s_addr, 4);
            memcpy(gram+16, &toAddress.s_addr, 4);
            *(u_short*)(gram+20)=htons(fromPort);
            *(u_short*)(gram+22)=htons(toPort);
            #if (defined __FreeBSD__ && __FreeBSD__ <= 10) || defined __APPLE__
            *(u_short*)(gram+24)=htons(UDPHEADER_LEN + len);
            *(u_short*)(gram+2)=HEADER_LEN + len;
            #else
            *(u_short*)(gram+24)=htons(UDPHEADER_LEN + len);
            *(u_short*)(gram+2)=htons(HEADER_LEN + len);
            #endif
            struct sockaddr_in sendAddr;
            sendAddr.sin_family = AF_INET;
            sendAddr.sin_port = htons(toPort);
            sendAddr.sin_addr = toAddress;

            if (sendto(
                iface->raw_socket,
                &gram,
                HEADER_LEN+len,
                0,
                (struct sockaddr*)&sendAddr,
                sizeof(sendAddr)
            ) < 0) {
                perror("sendto");
            }
        }
        DPRINT ("\n");
    }
}

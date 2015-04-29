/*
        Copyright (C) 2010 Ermal Luçi
        All rights reserved.

        Redistribution and use in source and binary forms, with or without
        modification, are permitted provided that the following conditions are met:

        1. Redistributions of source code must retain the above copyright notice,
           this list of conditions and the following disclaimer.

        2. Redistributions in binary form must reproduce the above copyright
           notice, this list of conditions and the following disclaimer in the
           documentation and/or other materials provided with the distribution.

        THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
        INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
        AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
        AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
        OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
        SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
        INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
        CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
        ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
        POSSIBILITY OF SUCH DAMAGE.

*/

/*

Functions copied from util.c and modem.c of mpd5 source are protected by
this copyright.
They are ExclusiveOpenDevice/ExclusiveCloseDevice and
OpenSerialDevice.

Copyright (c) 1995-1999 Whistle Communications, Inc. All rights reserved.

Subject to the following obligations and disclaimer of warranty,
use and redistribution of this software, in source or object code
forms, with or without modifications are expressly permitted by
Whistle Communications; provided, however, that:   (i) any and
all reproductions of the source or object code must include the
copyright notice above and the following disclaimer of warranties;
and (ii) no rights are granted, in any manner or form, to use
Whistle Communications, Inc. trademarks, including the mark "WHISTLE
COMMUNICATIONS" on advertising, endorsements, or otherwise except
as such appears in the above copyright notice or in the software.

THIS SOFTWARE IS BEING PROVIDED BY WHISTLE COMMUNICATIONS "AS IS",
AND TO THE MAXIMUM EXTENT PERMITTED BY LAW, WHISTLE COMMUNICATIONS
MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED,
REGARDING THIS SOFTWARE, INCLUDING WITHOUT LIMITATION, ANY AND
ALL IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE, OR NON-INFRINGEMENT.  WHISTLE COMMUNICATIONS DOES NOT
WARRANT, GUARANTEE, OR MAKE ANY REPRESENTATIONS REGARDING THE USE
OF, OR THE RESULTS OF THE USE OF THIS SOFTWARE IN TERMS OF ITS
CORRECTNESS, ACCURACY, RELIABILITY OR OTHERWISE.  IN NO EVENT
SHALL WHISTLE COMMUNICATIONS BE LIABLE FOR ANY DAMAGES RESULTING
FROM OR ARISING OUT OF ANY USE OF THIS SOFTWARE, INCLUDING WITHOUT
LIMITATION, ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
PUNITIVE, OR CONSEQUENTIAL DAMAGES, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES, LOSS OF USE, DATA OR PROFITS, HOWEVER CAUSED
AND UNDER ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF WHISTLE COMMUNICATIONS
IS ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#define IS_EXT_MODULE

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_pfSense.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <net/ethernet.h>
#include <net/if_types.h>
#include <net/if.h>
#include <net/if_var.h>
#include <net/if_vlan_var.h>
#include <net/if_dl.h>
#include <net/if_mib.h>
#include <net/if_bridgevar.h>
#include <netinet/in.h>
#include <netinet/in_var.h>
#include <net/pfvar.h>
#include <net/route.h>

#include <netinet/ip_fw.h>
#include <sys/ioctl.h>
#include <sys/sysctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>

#include <netgraph/ng_message.h>
#include <netgraph/ng_ether.h>

#include <netinet/ip_fw.h>

#include <vm/vm_param.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#include <glob.h>
#include <termios.h>
#include <poll.h>

#include <netgraph.h>
#include <netdb.h>

ZEND_DECLARE_MODULE_GLOBALS(pfSense)

static zend_function_entry pfSense_functions[] = {
    PHP_FE(pfSense_get_interface_addresses, NULL)
    PHP_FE(pfSense_getall_interface_addresses, NULL)
    PHP_FE(pfSense_get_interface_stats, NULL)
    PHP_FE(pfSense_vlan_create, NULL)
    PHP_FE(pfSense_interface_rename, NULL)
    PHP_FE(pfSense_interface_mtu, NULL)
    PHP_FE(pfSense_bridge_add_member, NULL)
    PHP_FE(pfSense_interface_listget, NULL)
    PHP_FE(pfSense_interface_create, NULL)
    PHP_FE(pfSense_interface_destroy, NULL)
    PHP_FE(pfSense_interface_flags, NULL)
    PHP_FE(pfSense_interface_capabilities, NULL)
    PHP_FE(pfSense_interface_setaddress, NULL)
    PHP_FE(pfSense_interface_deladdress, NULL)
    PHP_FE(pfSense_ngctl_name, NULL)
    PHP_FE(pfSense_ngctl_attach, NULL)
    PHP_FE(pfSense_ngctl_detach, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry pfSense_module_entry = {
    STANDARD_MODULE_HEADER,
    "pfSense",
    pfSense_functions,
    PHP_MINIT(pfSense_module_init),
    PHP_MSHUTDOWN(pfSense_module_exit),
    NULL,
    NULL,
    NULL,
    "1.0",
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PFSENSE
ZEND_GET_MODULE(pfSense)
#endif

/* interface management code */
static int
pfi_get_ifaces(int dev, const char *filter, struct pfi_kif *buf, int *size)
{
	struct pfioc_iface io;
	caddr_t buff[sizeof(struct pfi_kif) + 1] = { 0 };

	bzero(&io, sizeof io);
	if (filter != NULL)
		if (strlcpy(io.pfiio_name, filter, sizeof(io.pfiio_name)) >=
		    sizeof(io.pfiio_name)) {
			errno = EINVAL;
			return (-1);
		}
	io.pfiio_buffer = buf;
	io.pfiio_esize = sizeof(struct pfi_kif);
	io.pfiio_size = *size;
	if (ioctl(dev, DIOCIGETIFACES, &io))
		return (-1);
	*size = io.pfiio_size;
	return (0);
}

/* returns prefixlen, obtained from sbin/ifconfig/af_inet6.c */
static int
prefix(void *val, int size)
{
	u_char *name = (u_char *)val;
	int byte, bit, plen = 0;

	for (byte = 0; byte < size; byte++, plen += 8)
		if (name[byte] != 0xff)
			break;
	if (byte == size)
		return (plen);
	for (bit = 7; bit != 0; bit--, plen++)
		if (!(name[byte] & (1 << bit)))
			break;
	for (; bit != 0; bit--)
		if (name[byte] & (1 << bit))
			return(0);
	byte++;
	for (; byte < size; byte++)
		if (name[byte])
			return(0);
	return (plen);
}

PHP_MINIT_FUNCTION(pfSense_module_init)
{
	int csock = -1;

	PFSENSE_G(locals) = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (PFSENSE_G(locals) < 0) {
		return FAILURE;
	}

	PFSENSE_G(inets) = socket(AF_INET, SOCK_DGRAM, 0);
	if (PFSENSE_G(inets) < 0) {
		close(PFSENSE_G(locals));
		return FAILURE;
	}

	if (geteuid() == 0 || getuid() == 0) {
		/* Create a new socket node */
		if (NgMkSockNode(NULL, &csock, NULL) < 0) {
			csock = -1;
		} else {
			fcntl(csock, F_SETFD, fcntl(csock, F_GETFD, 0) | FD_CLOEXEC);
		}
	}

	PFSENSE_G(ngsock) = csock;

	/* Don't leak these sockets to child processes */
	fcntl(PFSENSE_G(locals), F_SETFD, fcntl(PFSENSE_G(locals), F_GETFD, 0) | FD_CLOEXEC);
	fcntl(PFSENSE_G(inets), F_SETFD, fcntl(PFSENSE_G(inets), F_GETFD, 0) | FD_CLOEXEC);

	REGISTER_LONG_CONSTANT("IFF_UP", IFF_UP, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFF_LINK0", IFF_LINK0, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFF_LINK1", IFF_LINK1, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFF_LINK2", IFF_LINK2, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFF_NOARP", IFF_NOARP, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFF_STATICARP", IFF_STATICARP, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_RXCSUM", IFCAP_RXCSUM, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_TXCSUM", IFCAP_TXCSUM, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_POLLING", IFCAP_POLLING, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_TSO", IFCAP_TSO, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_LRO", IFCAP_LRO, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_WOL", IFCAP_WOL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_WOL_UCAST", IFCAP_WOL_UCAST, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_WOL_MCAST", IFCAP_WOL_MCAST, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_WOL_MAGIC", IFCAP_WOL_MAGIC, CONST_PERSISTENT | CONST_CS);

	REGISTER_LONG_CONSTANT("IFCAP_VLAN_HWTAGGING", IFCAP_VLAN_HWTAGGING, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_VLAN_MTU", IFCAP_VLAN_MTU, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFCAP_VLAN_HWFILTER", IFCAP_VLAN_HWFILTER, CONST_PERSISTENT | CONST_CS);
#ifdef IFCAP_VLAN_HWCSUM
	REGISTER_LONG_CONSTANT("IFCAP_VLAN_HWCSUM", IFCAP_VLAN_HWCSUM, CONST_PERSISTENT | CONST_CS);
#endif
#ifdef IFCAP_VLAN_HWTSO
	REGISTER_LONG_CONSTANT("IFCAP_VLAN_HWTSO", IFCAP_VLAN_HWTSO, CONST_PERSISTENT | CONST_CS);
#endif

	REGISTER_LONG_CONSTANT("IFBIF_LEARNING", IFBIF_LEARNING, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_DISCOVER", IFBIF_DISCOVER, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_STP", IFBIF_STP, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_SPAN", IFBIF_SPAN, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_STICKY", IFBIF_STICKY, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_BSTP_EDGE", IFBIF_BSTP_EDGE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_BSTP_AUTOEDGE", IFBIF_BSTP_AUTOEDGE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_BSTP_PTP", IFBIF_BSTP_PTP, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_BSTP_AUTOPTP", IFBIF_BSTP_AUTOPTP, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_BSTP_ADMEDGE", IFBIF_BSTP_ADMEDGE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_BSTP_ADMCOST", IFBIF_BSTP_ADMCOST, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("IFBIF_PRIVATE", IFBIF_PRIVATE, CONST_PERSISTENT | CONST_CS);

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(pfSense_module_exit)
{
	if (PFSENSE_G(ngsock) != -1) {
		close(PFSENSE_G(ngsock));
	}

	if (PFSENSE_G(inets) != -1) {
		close(PFSENSE_G(inets));
	}

	if (PFSENSE_G(locals) != -1) {
		close(PFSENSE_G(locals));
	}

	return SUCCESS;
}

static int
pfctl_addrprefix(char *addr, struct pf_addr *mask)
{
	char *p;
	const char *errstr;
	int prefix, ret_ga, q, r;
	struct addrinfo hints, *res;

	if ((p = strchr(addr, '/')) == NULL)
		return 0;

	*p++ = '\0';
	prefix = strtonum(p, 0, 128, &errstr);
	if (errstr) {
		php_printf("prefix is %s: %s", errstr, p);
		return (-1);
	}

	bzero(&hints, sizeof(hints));
	/* prefix only with numeric addresses */
	hints.ai_flags |= AI_NUMERICHOST;

	if ((ret_ga = getaddrinfo(addr, NULL, &hints, &res))) {
		php_printf("getaddrinfo: %s", gai_strerror(ret_ga));
		return (-1);
		/* NOTREACHED */
	}

	if (res->ai_family == AF_INET && prefix > 32) {
		php_printf("prefix too long for AF_INET");
		return (-1);
	} else if (res->ai_family == AF_INET6 && prefix > 128) {
		php_printf("prefix too long for AF_INET6");
		return (-1);
	}

	q = prefix >> 3;
	r = prefix & 7;
	switch (res->ai_family) {
	case AF_INET:
		bzero(&mask->v4, sizeof(mask->v4));
		mask->v4.s_addr = htonl((u_int32_t)
		    (0xffffffffffULL << (32 - prefix)));
		break;
	case AF_INET6:
		bzero(&mask->v6, sizeof(mask->v6));
		if (q > 0)
			memset((void *)&mask->v6, 0xff, q);
		if (r > 0)
			*((u_char *)&mask->v6 + q) =
			    (0xff00 >> r) & 0xff;
		break;
	}
	freeaddrinfo(res);

	return (0);
}

PHP_FUNCTION(pfSense_getall_interface_addresses)
{
	struct ifaddrs *ifdata, *mb;
	struct if_data *md;
	struct sockaddr_in *tmp;
	struct sockaddr_in6 *tmp6;
	char outputbuf[132];
	char *ifname;
	int ifname_len, s;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ifname, &ifname_len) == FAILURE)
		RETURN_NULL();

	getifaddrs(&ifdata);
	if (ifdata == NULL)
		RETURN_NULL();

	array_init(return_value);

	for(mb = ifdata; mb != NULL; mb = mb->ifa_next) {
		if (mb == NULL)
			continue;
		if (ifname_len != strlen(mb->ifa_name))
			continue;
		if (strncmp(ifname, mb->ifa_name, ifname_len) != 0)
			continue;
		if (mb->ifa_addr == NULL)
			continue;

		switch (mb->ifa_addr->sa_family) {
		case AF_INET:
			bzero(outputbuf, sizeof outputbuf);
			tmp = (struct sockaddr_in *)mb->ifa_addr;
			inet_ntop(AF_INET, (void *)&tmp->sin_addr, outputbuf, 132);
			tmp = (struct sockaddr_in *)mb->ifa_netmask;
			unsigned char mask;
			const unsigned char *byte = (unsigned char *)&tmp->sin_addr.s_addr;
			int i = 0, n = sizeof(tmp->sin_addr.s_addr);
			while (n--) {
				mask = ((unsigned char)-1 >> 1) + 1;
					do {
						if (mask & byte[n])
							i++;
						mask >>= 1;
					} while (mask);
			}
			snprintf(outputbuf + strlen(outputbuf), sizeof(outputbuf) - strlen(outputbuf), "/%d", i);
			add_next_index_string(return_value, outputbuf, 1);
			break;
		case AF_INET6:
			bzero(outputbuf, sizeof outputbuf);
			tmp6 = (struct sockaddr_in6 *)mb->ifa_addr;
			if (IN6_IS_ADDR_LINKLOCAL(&tmp6->sin6_addr)) {
				tmp6->sin6_scope_id = ntohs(*(u_int16_t *)&tmp6->sin6_addr.s6_addr[2]);
				tmp6->sin6_addr.s6_addr[2] = tmp6->sin6_addr.s6_addr[3] = 0;
				if (getnameinfo((struct sockaddr *)tmp6, tmp6->sin6_len, outputbuf, sizeof(outputbuf), NULL, 0, NI_NUMERICHOST))
					inet_ntop(AF_INET6, (void *)&tmp6->sin6_addr, outputbuf, INET6_ADDRSTRLEN);
			} else
				inet_ntop(AF_INET6, (void *)&tmp6->sin6_addr, outputbuf, INET6_ADDRSTRLEN);
			tmp6 = (struct sockaddr_in6 *)mb->ifa_netmask;
			snprintf(outputbuf + strlen(outputbuf), sizeof(outputbuf) - strlen(outputbuf),
				"/%d", prefix(&tmp6->sin6_addr, sizeof(struct in6_addr)));
			add_next_index_string(return_value, outputbuf, 1);
			break;
		}
	}
}

PHP_FUNCTION(pfSense_get_interface_addresses)
{
	struct ifaddrs *ifdata, *mb;
	struct if_data *md;
	struct sockaddr_in *tmp;
	struct sockaddr_in6 *tmp6;
	struct sockaddr_dl *tmpdl;
	struct ifreq ifr;
	char outputbuf[128];
	char *ifname;
	int ifname_len, s, addresscnt = 0, addresscnt6 = 0;
	zval *caps;
	zval *encaps;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ifname, &ifname_len) == FAILURE)
		RETURN_NULL();

	getifaddrs(&ifdata);
	if (ifdata == NULL)
		RETURN_NULL();

	array_init(return_value);

	for(mb = ifdata; mb != NULL; mb = mb->ifa_next) {
		if (mb == NULL)
			continue;
		if (ifname_len != strlen(mb->ifa_name))
			continue;
		if (strncmp(ifname, mb->ifa_name, ifname_len) != 0)
			continue;

		if (mb->ifa_flags & IFF_UP)
			add_assoc_string(return_value, "status", "up", 1);
		else
			add_assoc_string(return_value, "status", "down", 1);
		if (mb->ifa_flags & IFF_LINK0)
			add_assoc_long(return_value, "link0", 1);
		if (mb->ifa_flags & IFF_LINK1)
			add_assoc_long(return_value, "link1", 1);
		if (mb->ifa_flags & IFF_LINK2)
			add_assoc_long(return_value, "link2", 1);
		if (mb->ifa_flags & IFF_MULTICAST)
			add_assoc_long(return_value, "multicast", 1);
		if (mb->ifa_flags & IFF_LOOPBACK)
			add_assoc_long(return_value, "loopback", 1);
		if (mb->ifa_flags & IFF_POINTOPOINT)
			add_assoc_long(return_value, "pointtopoint", 1);
		if (mb->ifa_flags & IFF_PROMISC)
			add_assoc_long(return_value, "promisc", 1);
		if (mb->ifa_flags & IFF_PPROMISC)
			add_assoc_long(return_value, "permanentpromisc", 1);
		if (mb->ifa_flags & IFF_OACTIVE)
			add_assoc_long(return_value, "oactive", 1);
		if (mb->ifa_flags & IFF_ALLMULTI)
			add_assoc_long(return_value, "allmulti", 1);
		if (mb->ifa_flags & IFF_SIMPLEX)
			add_assoc_long(return_value, "simplex", 1);
		if (mb->ifa_data != NULL) {
			md = mb->ifa_data;
			if (md->ifi_link_state == LINK_STATE_UP)
				add_assoc_long(return_value, "linkstateup", 1);
			add_assoc_long(return_value, "mtu", md->ifi_mtu);
			switch (md->ifi_type) {
			case IFT_IEEE80211:
				add_assoc_string(return_value, "iftype", "wireless", 1);
				break;
			case IFT_ETHER:
			case IFT_FASTETHER:
			case IFT_FASTETHERFX:
			case IFT_GIGABITETHERNET:
				add_assoc_string(return_value, "iftype", "ether", 1);
				break;
			case IFT_L2VLAN:
				add_assoc_string(return_value, "iftype", "vlan", 1);
				break;
			case IFT_BRIDGE:
				add_assoc_string(return_value, "iftype", "bridge", 1);
				break;
			case IFT_TUNNEL:
			case IFT_GIF:
			case IFT_ENC:
			case IFT_PFLOG: 
			case IFT_PFSYNC:
				add_assoc_string(return_value, "iftype", "virtual", 1);
				break;
			default:
				add_assoc_string(return_value, "iftype", "other", 1);
			}
		}
		ALLOC_INIT_ZVAL(caps);
		ALLOC_INIT_ZVAL(encaps);
		array_init(caps);
		array_init(encaps);
		strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
		if (ioctl(PFSENSE_G(locals), SIOCGIFCAP, (caddr_t)&ifr) == 0) {
			add_assoc_long(caps, "flags", ifr.ifr_reqcap);
			if (ifr.ifr_reqcap & IFCAP_POLLING)
				add_assoc_long(caps, "polling", 1);
			if (ifr.ifr_reqcap & IFCAP_RXCSUM)
				add_assoc_long(caps, "rxcsum", 1);
			if (ifr.ifr_reqcap & IFCAP_TXCSUM)
				add_assoc_long(caps, "txcsum", 1);
			if (ifr.ifr_reqcap & IFCAP_VLAN_MTU)
				add_assoc_long(caps, "vlanmtu", 1);
			if (ifr.ifr_reqcap & IFCAP_JUMBO_MTU)
				add_assoc_long(caps, "jumbomtu", 1);
			if (ifr.ifr_reqcap & IFCAP_VLAN_HWTAGGING)
				add_assoc_long(caps, "vlanhwtag", 1);
			if (ifr.ifr_reqcap & IFCAP_VLAN_HWCSUM)
				add_assoc_long(caps, "vlanhwcsum", 1);
			if (ifr.ifr_reqcap & IFCAP_TSO4)
				add_assoc_long(caps, "tso4", 1);
			if (ifr.ifr_reqcap & IFCAP_TSO6)
				add_assoc_long(caps, "tso6", 1);
			if (ifr.ifr_reqcap & IFCAP_LRO)
				add_assoc_long(caps, "lro", 1);
			if (ifr.ifr_reqcap & IFCAP_WOL_UCAST)
				add_assoc_long(caps, "wolucast", 1);
			if (ifr.ifr_reqcap & IFCAP_WOL_MCAST)
				add_assoc_long(caps, "wolmcast", 1);
			if (ifr.ifr_reqcap & IFCAP_WOL_MAGIC)
				add_assoc_long(caps, "wolmagic", 1);
			if (ifr.ifr_reqcap & IFCAP_TOE4)
				add_assoc_long(caps, "toe4", 1);
			if (ifr.ifr_reqcap & IFCAP_TOE6)
				add_assoc_long(caps, "toe6", 1);
			if (ifr.ifr_reqcap & IFCAP_VLAN_HWFILTER)
				add_assoc_long(caps, "vlanhwfilter", 1);
			add_assoc_long(encaps, "flags", ifr.ifr_curcap);
			if (ifr.ifr_curcap & IFCAP_POLLING)
				add_assoc_long(encaps, "polling", 1);
			if (ifr.ifr_curcap & IFCAP_RXCSUM)
				add_assoc_long(encaps, "rxcsum", 1);
			if (ifr.ifr_curcap & IFCAP_TXCSUM)
				add_assoc_long(encaps, "txcsum", 1);
			if (ifr.ifr_curcap & IFCAP_VLAN_MTU)
				add_assoc_long(encaps, "vlanmtu", 1);
			if (ifr.ifr_curcap & IFCAP_JUMBO_MTU)
				add_assoc_long(encaps, "jumbomtu", 1);
			if (ifr.ifr_curcap & IFCAP_VLAN_HWTAGGING)
				add_assoc_long(encaps, "vlanhwtag", 1);
			if (ifr.ifr_curcap & IFCAP_VLAN_HWCSUM)
				add_assoc_long(encaps, "vlanhwcsum", 1);
			if (ifr.ifr_curcap & IFCAP_TSO4)
				add_assoc_long(encaps, "tso4", 1);
			if (ifr.ifr_curcap & IFCAP_TSO6)
				add_assoc_long(encaps, "tso6", 1);
			if (ifr.ifr_curcap & IFCAP_LRO)
				add_assoc_long(encaps, "lro", 1);
			if (ifr.ifr_curcap & IFCAP_WOL_UCAST)
				add_assoc_long(encaps, "wolucast", 1);
			if (ifr.ifr_curcap & IFCAP_WOL_MCAST)
				add_assoc_long(encaps, "wolmcast", 1);
			if (ifr.ifr_curcap & IFCAP_WOL_MAGIC)
				add_assoc_long(encaps, "wolmagic", 1);
			if (ifr.ifr_curcap & IFCAP_TOE4)
				add_assoc_long(encaps, "toe4", 1);
			if (ifr.ifr_curcap & IFCAP_TOE6)
				add_assoc_long(encaps, "toe6", 1);
			if (ifr.ifr_curcap & IFCAP_VLAN_HWFILTER)
				add_assoc_long(encaps, "vlanhwfilter", 1);
		}
		add_assoc_zval(return_value, "caps", caps);
		add_assoc_zval(return_value, "encaps", encaps);
		if (mb->ifa_addr == NULL)
			continue;
		switch (mb->ifa_addr->sa_family) {
		case AF_INET:
			if (addresscnt > 0)
				break;
			bzero(outputbuf, sizeof outputbuf);
			tmp = (struct sockaddr_in *)mb->ifa_addr;
			inet_ntop(AF_INET, (void *)&tmp->sin_addr, outputbuf, 128);
			add_assoc_string(return_value, "ipaddr", outputbuf, 1);
			addresscnt++;
			tmp = (struct sockaddr_in *)mb->ifa_netmask;
			unsigned char mask;
			const unsigned char *byte = (unsigned char *)&tmp->sin_addr.s_addr;
			int i = 0, n = sizeof(tmp->sin_addr.s_addr);
			while (n--) {
				mask = ((unsigned char)-1 >> 1) + 1;
					do {
						if (mask & byte[n])
							i++;
						mask >>= 1;
					} while (mask);
			}
			add_assoc_long(return_value, "subnetbits", i);

			bzero(outputbuf, sizeof outputbuf);
			inet_ntop(AF_INET, (void *)&tmp->sin_addr, outputbuf, 128);
			add_assoc_string(return_value, "subnet", outputbuf, 1);

			if (mb->ifa_flags & IFF_BROADCAST) {
				bzero(outputbuf, sizeof outputbuf);
				tmp = (struct sockaddr_in *)mb->ifa_broadaddr;
				inet_ntop(AF_INET, (void *)&tmp->sin_addr, outputbuf, 128);
				add_assoc_string(return_value, "broadcast", outputbuf, 1);
			}

			if (mb->ifa_flags & IFF_POINTOPOINT) {
				bzero(outputbuf, sizeof outputbuf);
				tmp6 = (struct sockaddr_in6 *)mb->ifa_dstaddr;
				inet_ntop(AF_INET, (void *)&tmp6->sin6_addr, outputbuf, 128);
				add_assoc_string(return_value, "tunnel", outputbuf, 1);
			}

		break;
		case AF_INET6:
			if (addresscnt6 > 0)
                                break;
                        bzero(outputbuf, sizeof outputbuf);
                        tmp6 = (struct sockaddr_in6 *)mb->ifa_addr;
			if (IN6_IS_ADDR_LINKLOCAL(&tmp6->sin6_addr))
				break;
                        inet_ntop(AF_INET6, (void *)&tmp6->sin6_addr, outputbuf, 128);
                        add_assoc_string(return_value, "ipaddr6", outputbuf, 1);
                        addresscnt6++;
                        tmp6 = (struct sockaddr_in6 *)mb->ifa_netmask;
                        add_assoc_long(return_value, "subnetbits6", prefix(&tmp6->sin6_addr, sizeof(struct in6_addr)));
                
                        if (mb->ifa_flags & IFF_POINTOPOINT) {
                                bzero(outputbuf, sizeof outputbuf);
                                tmp = (struct sockaddr_in *)mb->ifa_dstaddr;
                                inet_ntop(AF_INET, (void *)&tmp->sin_addr, outputbuf, 128);
                                add_assoc_string(return_value, "tunnel6", outputbuf, 1);
                        }
		break;
		case AF_LINK:
			tmpdl = (struct sockaddr_dl *)mb->ifa_addr;
			bzero(outputbuf, sizeof outputbuf);
			ether_ntoa_r((struct ether_addr *)LLADDR(tmpdl), outputbuf);
			add_assoc_string(return_value, "macaddr", outputbuf, 1);
			md = (struct if_data *)mb->ifa_data;

		break;
		}
	}
	freeifaddrs(ifdata);
}

PHP_FUNCTION(pfSense_bridge_add_member) {
	char *ifname, *ifchld;
	int ifname_len, ifchld_len;
	struct ifdrv drv;
	struct ifbreq req;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &ifname, &ifname_len, &ifchld, &ifchld_len) == FAILURE) {
		RETURN_NULL();
	}

	memset(&drv, 0, sizeof(drv));
	memset(&req, 0, sizeof(req));
	strlcpy(drv.ifd_name, ifname, sizeof(drv.ifd_name));
	strlcpy(req.ifbr_ifsname, ifchld, sizeof(req.ifbr_ifsname));
	drv.ifd_cmd = BRDGADD;
	drv.ifd_data = &req;
	drv.ifd_len = sizeof(req);
	if (ioctl(PFSENSE_G(locals), SIOCSDRVSPEC, (caddr_t)&drv) < 0)
		RETURN_FALSE;

	RETURN_TRUE;
}

PHP_FUNCTION(pfSense_interface_listget) {
	struct ifaddrs *ifdata, *mb;
	char *ifname;
	int ifname_len;
	long flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &flags) == FAILURE)
		RETURN_NULL();

	getifaddrs(&ifdata);
	if (ifdata == NULL)
		RETURN_NULL();

	array_init(return_value);
	ifname = NULL;
	ifname_len = 0;
	for(mb = ifdata; mb != NULL; mb = mb->ifa_next) {
		if (mb == NULL)
			continue;

		if (flags != 0) {
			if (mb->ifa_flags & IFF_UP && flags < 0)
				continue;
			if (!(mb->ifa_flags & IFF_UP) && flags > 0)
				continue;
		}

		if (ifname != NULL && ifname_len == strlen(mb->ifa_name) && strcmp(ifname, mb->ifa_name) == 0)
			continue;
		ifname = mb->ifa_name;
		ifname_len = strlen(mb->ifa_name);

		add_next_index_string(return_value, mb->ifa_name, 1);
	}

	freeifaddrs(ifdata);
}

PHP_FUNCTION(pfSense_interface_create) {
	char *ifname;
	int ifname_len, len;
	struct ifreq ifr;
	struct vlanreq params;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ifname, &ifname_len) == FAILURE) {
		RETURN_NULL();
	}

	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	if (ioctl(PFSENSE_G(locals), SIOCIFCREATE2, &ifr) < 0) {
		array_init(return_value);
		add_assoc_string(return_value, "error", "Could not create interface", 1);
	} else
		RETURN_STRING(ifr.ifr_name, 1)
}

PHP_FUNCTION(pfSense_interface_destroy) {
	char *ifname;
	int ifname_len;
	struct ifreq ifr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ifname, &ifname_len) == FAILURE) {
		RETURN_NULL();
	}

	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	if (ioctl(PFSENSE_G(locals), SIOCIFDESTROY, &ifr) < 0) {
		array_init(return_value);
		add_assoc_string(return_value, "error", "Could not create interface", 1);
	} else
		RETURN_TRUE;
}

PHP_FUNCTION(pfSense_interface_setaddress) {
	char *ifname, *ip, *p = NULL;
	int ifname_len, ip_len;
	struct sockaddr_in *sin;
	struct in_aliasreq ifra;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &ifname, &ifname_len, &ip, &ip_len) == FAILURE) {
		RETURN_NULL();
	}

	memset(&ifra, 0, sizeof(ifra));
	strlcpy(ifra.ifra_name, ifname, sizeof(ifra.ifra_name));
	sin =  &ifra.ifra_mask;
	sin->sin_family = AF_INET;
	sin->sin_len = sizeof(*sin);
	sin->sin_addr.s_addr = 0;
	if ((p = strrchr(ip, '/')) != NULL) {
		/* address is `name/masklen' */
		int masklen;
		int ret;
		*p = '\0';
		ret = sscanf(p+1, "%u", &masklen);
		if(ret != 1 || (masklen < 0 || masklen > 32)) {
			*p = '/';
			RETURN_FALSE;
		}
		sin->sin_addr.s_addr = htonl(~((1LL << (32 - masklen)) - 1) &
			0xffffffff);
	}
	sin =  &ifra.ifra_addr;
	sin->sin_family = AF_INET;
	sin->sin_len = sizeof(*sin);
	if (inet_pton(AF_INET, ip, &sin->sin_addr) <= 0)
		RETURN_FALSE;

	if (ioctl(PFSENSE_G(inets), SIOCAIFADDR, &ifra) < 0) {
		array_init(return_value);
		add_assoc_string(return_value, "error", "Could not set interface address", 1);
	} else
		RETURN_TRUE;
}

PHP_FUNCTION(pfSense_interface_deladdress) {
	char *ifname, *ip = NULL;
	int ifname_len, ip_len;
	struct sockaddr_in *sin;
	struct in_aliasreq ifra;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &ifname, &ifname_len, &ip, &ip_len) == FAILURE) {
		RETURN_NULL();
	}

	memset(&ifra, 0, sizeof(ifra));
	strlcpy(ifra.ifra_name, ifname, sizeof(ifra.ifra_name));
	sin =  &ifra.ifra_addr;
	sin->sin_family = AF_INET;
	sin->sin_len = sizeof(*sin);
	if (inet_pton(AF_INET, ip, &sin->sin_addr) <= 0)
		RETURN_FALSE;

	if (ioctl(PFSENSE_G(inets), SIOCDIFADDR, &ifra) < 0) {
		array_init(return_value);
		add_assoc_string(return_value, "error", "Could not delete interface address", 1);
	} else
		RETURN_TRUE;
}

PHP_FUNCTION(pfSense_ngctl_name)
{
	char *ifname, *newifname;
	int ifname_len, newifname_len;

	if (PFSENSE_G(ngsock) == -1) {
		RETURN_NULL();
	}

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &ifname, &ifname_len, &newifname, &newifname_len) == FAILURE) {
		RETURN_NULL();
	}

	/* Send message */
	if (NgNameNode(PFSENSE_G(ngsock), ifname, "%s", newifname) < 0) {
		RETURN_NULL();
	}

	RETURN_TRUE;
}

PHP_FUNCTION(pfSense_ngctl_attach)
{
	char *ifname, *newifname;
	int ifname_len, newifname_len;
	struct ngm_name name;

	if (PFSENSE_G(ngsock) == -1) {
		RETURN_NULL();
	}

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &ifname, &ifname_len, &newifname, &newifname_len) == FAILURE) {
		RETURN_NULL();
	}

	snprintf(name.name, sizeof(name.name), "%s", newifname);
	/* Send message */
	if (NgSendMsg(PFSENSE_G(ngsock), ifname, NGM_GENERIC_COOKIE,
		NGM_ETHER_ATTACH, &name, sizeof(name)) < 0) {
			RETURN_NULL();
	}

	RETURN_TRUE;
}

PHP_FUNCTION(pfSense_ngctl_detach)
{
	char *ifname, *newifname;
	int ifname_len, newifname_len;
	struct ngm_name name;

	if (PFSENSE_G(ngsock) == -1) {
		RETURN_NULL();
	}

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &ifname, &ifname_len, &newifname, &newifname_len) == FAILURE) {
		RETURN_NULL();
	}

	snprintf(name.name, sizeof(name.name), "%s", newifname);
	/* Send message */
	if (NgSendMsg(PFSENSE_G(ngsock), ifname, NGM_ETHER_COOKIE,
		NGM_ETHER_DETACH, &name, sizeof(name)) < 0) {
			RETURN_NULL();
	}

	RETURN_TRUE;
}

PHP_FUNCTION(pfSense_vlan_create) {
	char *ifname = NULL;
	char *parentifname = NULL;
	int ifname_len, parent_len;
	long tag; 
	struct ifreq ifr;
	struct vlanreq params;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssl", &ifname, &ifname_len, &parentifname, &parent_len, &tag) == FAILURE) {
		RETURN_NULL();
	}

	memset(&ifr, 0, sizeof(ifr));
	memset(&params, 0, sizeof(params));
	strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	strlcpy(params.vlr_parent, parentifname, sizeof(params.vlr_parent));
	params.vlr_tag = (u_short) tag;
	ifr.ifr_data = (caddr_t) &params;
	if (ioctl(PFSENSE_G(locals), SIOCSETVLAN, (caddr_t) &ifr) < 0)
		RETURN_NULL();

	RETURN_TRUE;
}

PHP_FUNCTION(pfSense_interface_mtu) {
	char *ifname;
	int ifname_len;
	long mtu;
	struct ifreq ifr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &ifname, &ifname_len, &mtu) == FAILURE) {
		RETURN_NULL();
	}
	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	ifr.ifr_mtu = (int) mtu;
	if (ioctl(PFSENSE_G(locals), SIOCSIFMTU, (caddr_t)&ifr) < 0)
		RETURN_NULL();
	RETURN_TRUE;
}

PHP_FUNCTION(pfSense_interface_flags) {
	struct ifreq ifr;
	char *ifname;
	int flags, ifname_len;
	long value;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &ifname, &ifname_len, &value) == FAILURE) {
		RETURN_NULL();
	}

	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	if (ioctl(PFSENSE_G(locals), SIOCGIFFLAGS, (caddr_t)&ifr) < 0) {
		RETURN_NULL();
	}
	flags = (ifr.ifr_flags & 0xffff) | (ifr.ifr_flagshigh << 16);
	if (value < 0) {
		value = -value;
		flags &= ~(int)value;
	} else
		flags |= (int)value; 
	ifr.ifr_flags = flags & 0xffff;
	ifr.ifr_flagshigh = flags >> 16;
	if (ioctl(PFSENSE_G(locals), SIOCSIFFLAGS, (caddr_t)&ifr) < 0)
		RETURN_NULL();
	RETURN_TRUE;
}

PHP_FUNCTION(pfSense_interface_capabilities) {
	struct ifreq ifr;
	char *ifname;
	int flags, ifname_len;
	long value;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &ifname, &ifname_len, &value) == FAILURE) {
		RETURN_NULL();
	}

	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	if (ioctl(PFSENSE_G(locals), SIOCGIFCAP, (caddr_t)&ifr) < 0) {
		RETURN_NULL();
	}
	flags = ifr.ifr_curcap;
	if (value < 0) {
		value = -value;
		flags &= ~(int)value;
	} else
		flags |= (int)value; 
	flags &= ifr.ifr_reqcap;
	ifr.ifr_reqcap = flags;
	if (ioctl(PFSENSE_G(locals), SIOCSIFCAP, (caddr_t)&ifr) < 0)
		RETURN_NULL();
	RETURN_TRUE;

}

PHP_FUNCTION(pfSense_get_interface_stats)
{
	struct ifmibdata ifmd;
	struct if_data *tmpd;
	char outputbuf[128];
	char *ifname;
	int ifname_len, error;
	int name[6];
	size_t len;
	unsigned int ifidx;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ifname, &ifname_len) == FAILURE) {
		RETURN_NULL();
	}

	ifidx = if_nametoindex(ifname);
	if (ifidx == 0)
		RETURN_NULL();

	name[0] = CTL_NET;
	name[1] = PF_LINK;
	name[2] = NETLINK_GENERIC;
	name[3] = IFMIB_IFDATA;
	name[4] = ifidx;
	name[5] = IFDATA_GENERAL;

	len = sizeof(ifmd);

	if (sysctl(name, 6, &ifmd, &len, (void *)0, 0) < 0)
		RETURN_NULL();
	
	tmpd = &ifmd.ifmd_data;

	array_init(return_value);
	add_assoc_long(return_value, "inpkts", (long)tmpd->ifi_ipackets);
	add_assoc_long(return_value, "inbytes", (long)tmpd->ifi_ibytes);
	add_assoc_long(return_value, "outpkts", (long)tmpd->ifi_opackets);
	add_assoc_long(return_value, "outbytes", (long)tmpd->ifi_obytes);
	add_assoc_long(return_value, "inerrs", (long)tmpd->ifi_ierrors);
	add_assoc_long(return_value, "outerrs", (long)tmpd->ifi_oerrors);
	add_assoc_long(return_value, "collisions", (long)tmpd->ifi_collisions);
	add_assoc_long(return_value, "inmcasts", (long)tmpd->ifi_imcasts);
	add_assoc_long(return_value, "outmcasts", (long)tmpd->ifi_omcasts);
	add_assoc_long(return_value, "unsuppproto", (long)tmpd->ifi_noproto);
	add_assoc_long(return_value, "mtu", (long)tmpd->ifi_mtu);
}

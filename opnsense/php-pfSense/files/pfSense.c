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

#define IS_EXT_MODULE

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_pfSense.h"

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <net/if_bridgevar.h>
#include <net/if_dl.h>
#include <net/if_mib.h>
#include <net/if_types.h>
#include <net/if_var.h>
#include <net/if_vlan_var.h>
#include <net/pfvar.h>
#include <net/route.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <netinet/in_var.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <glob.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <termios.h>
#include <unistd.h>

ZEND_DECLARE_MODULE_GLOBALS(pfSense)

static zend_function_entry pfSense_functions[] = {
    PHP_FE(pfSense_get_interface_addresses, NULL)
    PHP_FE(pfSense_getall_interface_addresses, NULL)
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
	PFSENSE_G(locals) = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (PFSENSE_G(locals) < 0) {
		return FAILURE;
	}

	/* Don't leak these sockets to child processes */
	fcntl(PFSENSE_G(locals), F_SETFD, fcntl(PFSENSE_G(locals), F_GETFD, 0) | FD_CLOEXEC);

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(pfSense_module_exit)
{
	if (PFSENSE_G(locals) != -1) {
		close(PFSENSE_G(locals));
	}

	return SUCCESS;
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

/*
 * Copyright (c) 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>

#include <netinet/udp.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

#include <pcap/pcap.h>

#include "common.h"

#define IP_RES 0x8000

static struct tok ip_frag_values[] = {
        { IP_MF,        "+" },
        { IP_DF,        "DF" },
	{ IP_RES,       "rsvd" }, /* The RFC3514 evil ;-) bit */
        { 0,            NULL }
};

struct ip_print_demux_state {
	const struct ip *ip;
	const u_char *cp;
	u_int   len, off;
	u_char  nh;
	int     advance;
};

static void
ip_print_demux(struct sbuf *sbuf, struct ip_print_demux_state *ipds)
{
	switch (ipds->nh) {
	case IPPROTO_TCP:
		/* pass on the MF bit plus the offset to detect fragments */
		tcp_print(sbuf, ipds->cp, ipds->len);
		break;
	case IPPROTO_UDP: {
		const struct udphdr *up = (const struct udphdr *)ipds->cp;
		sbuf_printf(sbuf, "%d,%d,%d",
		    EXTRACT_16BITS(&up->uh_sport),
		    EXTRACT_16BITS(&up->uh_dport),
		    EXTRACT_16BITS(&up->uh_ulen));
		break;
	}
	case IPPROTO_VRRP:
		/* Type, ttl, vhid, version, adbskew, advbase */
		sbuf_printf(sbuf, "%s,%d,%d,%d,%d,%d",
				(ipds->cp[0] & 0x0f) == 1 ? "advertise" : "unkwn",
				ipds->ip->ip_ttl, ipds->cp[1], (ipds->cp[0] & 0xf0) >> 4,
				ipds->cp[2], ipds->cp[5]);
		break;
	default:
		sbuf_printf(sbuf, "datalength=%d", ipds->len);
		break;
	}
}

/*
 * print an IP datagram.
 * it requires fixed length fields to be put as null always
 */
void
ip_print(struct sbuf *sbuf,
	 const u_char *bp,
	 u_int length)
{
	struct ip_print_demux_state  ipd;
	struct ip_print_demux_state *ipds=&ipd;
	u_int hlen;
	char ubuf[64];

	ipds->ip = (const struct ip *)bp;
	sbuf_printf(sbuf, "%u,", IP_V(ipds->ip));

	if (ntohs(ipds->ip->ip_len) > MAXIMUM_SNAPLEN) {
		sbuf_printf(sbuf, "[|ip],");
		return;
	}
	if (length < sizeof (struct ip)) {
		sbuf_printf(sbuf, "truncated-ip=%u,", length);
		return;
	}
	hlen = IP_HL(ipds->ip) * 4;
	if (hlen < sizeof (struct ip)) {
		sbuf_printf(sbuf, "bad-hlen=%u,", hlen);
		return;
	}

	ipds->len = EXTRACT_16BITS(&ipds->ip->ip_len);
	if (length < ipds->len)
		sbuf_printf(sbuf, "truncated-ip=%u,", ipds->len);
	if (ipds->len < hlen) {
	    sbuf_printf(sbuf, "bad-len=%u,", ipds->len);
	    return;
	}

	/*
	 * Cut off the snapshot length to the end of the IP payload.
	 */
	ipds->len -= hlen;
	ipds->off = EXTRACT_16BITS(&ipds->ip->ip_off);

	sbuf_printf(sbuf, "0x%x,", (int)ipds->ip->ip_tos);
	/* ECN bits */
	if (ipds->ip->ip_tos & 0x03) {
		switch (ipds->ip->ip_tos & 0x03) {
		case 1:
			sbuf_printf(sbuf, "1");
			break;
		case 2:
			sbuf_printf(sbuf, "0");
			break;
		case 3:
			sbuf_printf(sbuf, "CE");
			break;
		}
	}
	sbuf_printf(sbuf, ",%u,", ipds->ip->ip_ttl);

	struct protoent *protoent = getprotobynumber(ipds->ip->ip_p);

        sprintf(ubuf, "unknown(%hhu)", ipds->ip->ip_p);

	const char *proto = protoent != NULL ? protoent->p_name :
	    code2str(ipproto_values, ubuf, ipds->ip->ip_p);

	/*
	 * for the firewall guys, print id, offset.
	 * On all but the last stick a "+" in the flags portion.
	 * For unfragmented datagrams, note the don't fragment flag.
	 */
	sbuf_printf(sbuf, "%u,%u,%s,%u,%s,%u,",
	    EXTRACT_16BITS(&ipds->ip->ip_id), (ipds->off & 0x1fff) * 8,
	    code2str(ip_frag_values, "none", ipds->off & 0xe000),
	    ipds->ip->ip_p, proto, EXTRACT_16BITS(&ipds->ip->ip_len));

	sbuf_printf(sbuf, "%s,", inet_ntoa(ipds->ip->ip_src));
	sbuf_printf(sbuf, "%s,", inet_ntoa(ipds->ip->ip_dst));

	/*
	 * If this is fragment zero, hand it to the next higher
	 * level protocol.
	 */
	if ((ipds->off & 0x1fff) == 0) {
		ipds->cp = (const u_char *)ipds->ip + hlen;
		ipds->nh = ipds->ip->ip_p;
		ip_print_demux(sbuf, ipds);
	}
}

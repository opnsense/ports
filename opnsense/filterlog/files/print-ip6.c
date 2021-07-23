/*
 * Copyright (c) 1988, 1989, 1990, 1991, 1992, 1993, 1994
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
 *
 * $FreeBSD$
 */

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip6.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <netinet/udp.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

static int
rt6_print(struct sbuf *sbuf, register const u_char *bp, int datalen)
{
	register const struct ip6_rthdr *dp;
	register const struct ip6_rthdr0 *dp0;
	register const u_char *ep;
	int i, len;
	register const struct in6_addr *addr;
	char ip6addr[INET6_ADDRSTRLEN];

	dp = (struct ip6_rthdr *)bp;
	len = dp->ip6r_len;

	/* 'ep' points to the end of available data. */
	ep = bp + datalen;

	sbuf_printf(sbuf, "%d,%d,%d,", dp->ip6r_len, dp->ip6r_type, dp->ip6r_segleft);	/*)*/

	switch (dp->ip6r_type) {
#ifndef IPV6_RTHDR_TYPE_0
#define IPV6_RTHDR_TYPE_0 0
#endif
#ifndef IPV6_RTHDR_TYPE_2
#define IPV6_RTHDR_TYPE_2 2
#endif
	case IPV6_RTHDR_TYPE_0:
	case IPV6_RTHDR_TYPE_2:			/* Mobile IPv6 ID-20 */
		dp0 = (struct ip6_rthdr0 *)dp;

		sbuf_printf(sbuf, "0x%0x,",
			    EXTRACT_32BITS(&dp0->ip6r0_reserved));

		if (len % 2 == 1)
			goto trunc;
		len >>= 1;
		addr = (struct in6_addr *)(dp0+1);
		for (i = 0; i < len; i++) {
			if ((u_char *)(addr + 1) > ep)
				goto trunc;

			memset(ip6addr, 0, INET6_ADDRSTRLEN);
			sbuf_printf(sbuf, "%d, %s", i, inet_ntop(AF_INET6, addr, ip6addr, INET6_ADDRSTRLEN));
			addr++;
		}
		/*(*/
		return((dp0->ip6r0_len + 1) << 3);
		break;
	default:
		goto trunc;
		break;
	}

 trunc:
	sbuf_printf(sbuf, "TRUNC,[|srcrt],");
	return -1;
}

static int
frag6_print(struct sbuf *sbuf, register const u_char *bp, register const u_char *bp2)
{
	register const struct ip6_frag *dp;
	register const struct ip6_hdr *ip6;

	dp = (const struct ip6_frag *)bp;
	ip6 = (const struct ip6_hdr *)bp2;


	sbuf_printf(sbuf, "FRAG6, 0x%08x:%d|%ld,",
		       EXTRACT_32BITS(&dp->ip6f_ident),
		       EXTRACT_16BITS(&dp->ip6f_offlg) & IP6F_OFF_MASK,
		       sizeof(struct ip6_hdr) + EXTRACT_16BITS(&ip6->ip6_plen) -
			       (long)(bp - bp2) - sizeof(struct ip6_frag));

	/* it is meaningless to decode non-first fragment */
	if ((EXTRACT_16BITS(&dp->ip6f_offlg) & IP6F_OFF_MASK) != 0)
		return -1;
	else
	{
		sbuf_printf(sbuf, ",");
		return sizeof(struct ip6_frag);
	}
}

/*
 * print an IP6 datagram.
 */
void
ip6_print(struct sbuf *sbuf, const u_char *bp, u_int length)
{
	register const struct ip6_hdr *ip6;
	register int advance;
	u_int len;
	const u_char *ipend;
	register const u_char *cp;
	register u_int payload_len;
	int nh;
	int fragmented = 0;
	u_int flow;

	ip6 = (const struct ip6_hdr *)bp;
	sbuf_printf(sbuf, "6,");

	if (length < sizeof (struct ip6_hdr)) {
		sbuf_printf(sbuf, "truncated-ip6=%u,", length);
		return;
	}

	payload_len = EXTRACT_16BITS(&ip6->ip6_plen);
	len = payload_len + sizeof(struct ip6_hdr);
	if (length < len)
		sbuf_printf(sbuf, "error='truncated-ip6 - %u bytes missing!',",
			len - length);

	flow = EXTRACT_32BITS(&ip6->ip6_flow);

	/* RFC 2460 */
	sbuf_printf(sbuf, "0x%02x,", (flow & 0x0ff00000) >> 20);
	sbuf_printf(sbuf, "0x%05x,", flow & 0x000fffff);

	struct protoent *protoent = getprotobynumber(ip6->ip6_nxt);
	const char *proto = protoent != NULL ? protoent->p_name :
	    code2str(ipproto_values, "unknown", ip6->ip6_nxt);

	sbuf_printf(sbuf, "%u,%s,%u,%u,",
	    ip6->ip6_hlim, proto, ip6->ip6_nxt, payload_len);

	/*
	 * Cut off the snapshot length to the end of the IP payload.
	 */
	ipend = bp + len;

	cp = (const u_char *)ip6;
	advance = sizeof(struct ip6_hdr);
	nh = ip6->ip6_nxt;
	while (cp < ipend && advance > 0) {
		char ip6addr[INET6_ADDRSTRLEN];

		cp += advance;
		len -= advance;

		if (cp == (const u_char *)(ip6 + 1)) {
			sbuf_printf(sbuf, "%s,", inet_ntop(AF_INET6, &ip6->ip6_src, ip6addr, INET6_ADDRSTRLEN));
			sbuf_printf(sbuf, "%s,", inet_ntop(AF_INET6, &ip6->ip6_dst, ip6addr, INET6_ADDRSTRLEN));
		}

		switch (nh) {
		case IPPROTO_HOPOPTS:
			advance = hbhopt_print(sbuf, cp);
			nh = *cp;
			break;
		case IPPROTO_DSTOPTS:
			advance = dstopt_print(sbuf, cp);
			nh = *cp;
			break;
		case IPPROTO_FRAGMENT:
			advance = frag6_print(sbuf, cp, (const u_char *)ip6);
			nh = *cp;
			fragmented = 1;
			break;

		case IPPROTO_MOBILITY_OLD:
		case IPPROTO_MOBILITY:
			/*
			 * XXX - we don't use "advance"; the current
			 * "Mobility Support in IPv6" draft
			 * (draft-ietf-mobileip-ipv6-24) says that
			 * the next header field in a mobility header
			 * should be IPPROTO_NONE, but speaks of
			 * the possiblity of a future extension in
			 * which payload can be piggybacked atop a
			 * mobility header.
			 */
			sbuf_printf(sbuf, "MOBILITY,");
			advance = mobility_print(sbuf, cp, len);
			nh = *cp;
			return;
		case IPPROTO_ROUTING:
			sbuf_printf(sbuf, "ROUTING,");
			advance = rt6_print(sbuf, cp, len);
			nh = *cp;
			break;
		case IPPROTO_TCP:
			tcp_print(sbuf, cp, len, (const u_char *)ip6);
			return;
		case IPPROTO_UDP: {
			const struct udphdr *up = (const struct udphdr *)cp;
			sbuf_printf(sbuf, "%d,%d,%d", EXTRACT_16BITS(&up->uh_sport), EXTRACT_16BITS(&up->uh_dport),
				EXTRACT_16BITS(&up->uh_ulen));
			return;
		}
		case IPPROTO_VRRP:
			sbuf_printf(sbuf, "%s,%d,%d,%d,%d,%d",
			    (cp[0] & 0x0f) == 1 ? "advertise" : "unkwn",
			    ip6->ip6_hlim, cp[1], (cp[0] & 0xf0) >> 4,
			    cp[2], cp[5]);
		case IPPROTO_IPV6:
			sbuf_printf(sbuf, "IPV6-IN-IPV6,");
			return;
		case IPPROTO_IPV4:
			sbuf_printf(sbuf, "IPV4-IN-IPV6,");
			return;
		default:
			return;
		}
	}
}

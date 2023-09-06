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

static void
ip6_print_post(struct sbuf *sbuf, const struct ip6_hdr *ip6, u_char nh, u_int payload_len)
{
	struct protoent *protoent = getprotobynumber(nh);
	char ip6addr[INET6_ADDRSTRLEN];
	const char *proto;
	char ubuf[64];

	sprintf(ubuf, "unknown(%hhu)", nh);

	proto = protoent != NULL ? protoent->p_name : code2str(ipproto_values, ubuf, nh);

	sbuf_printf(sbuf, "%u,%s,%u,%u,",
	    ip6->ip6_hlim, proto, nh, payload_len);
	sbuf_printf(sbuf, "%s,", inet_ntop(AF_INET6, &ip6->ip6_src, ip6addr,
	    INET6_ADDRSTRLEN));
	sbuf_printf(sbuf, "%s,", inet_ntop(AF_INET6, &ip6->ip6_dst, ip6addr,
	    INET6_ADDRSTRLEN));
}

/*
 * print an IP6 datagram.
 */
void
ip6_print(struct sbuf *sbuf, const u_char *bp, u_int length)
{
	const struct ip6_hdr *ip6, *ip6_next;
	int advance;
	u_int len;
	const u_char *ipend;
	const u_char *cp;
	u_int payload_len;
	u_char nh;
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
		sbuf_printf(sbuf, "truncated-ip6=%u,", len);

	flow = EXTRACT_32BITS(&ip6->ip6_flow);

	/* RFC 2460 */
	sbuf_printf(sbuf, "0x%02x,", (flow & 0x0ff00000) >> 20);
	sbuf_printf(sbuf, "0x%05x,", flow & 0x000fffff);

	cp = (const u_char *)ip6;
	advance = sizeof(struct ip6_hdr);
	nh = ip6->ip6_nxt;

	/*
	 * Cut off the snapshot length to the end of the IP payload.
	 */
	ipend = bp + len;

	while (cp < ipend && advance > 0) {
		cp += advance;
		len -= advance;

		ip6_next = (const struct ip6_hdr *)cp;

		switch (nh) {
		case IPPROTO_HOPOPTS:
			/* FALLTHROUGH */
		case IPPROTO_ROUTING:
			/* FALLTHROUGH */
		case IPPROTO_DSTOPTS:
			/* FALLTHROUGH */
		case IPPROTO_ESP:
			/* FALLTHROUGH */
		case IPPROTO_AH:
			/* variable extension header */
			if (ip6_next->ip6_plen % 8) {
				ip6_print_post(sbuf, ip6, nh, payload_len);
				sbuf_printf(sbuf, "INVALIDOPT");
				return;
			}
			advance = ip6_next->ip6_plen;
			nh = ip6_next->ip6_nxt;
			break;
		case IPPROTO_FRAGMENT:
			/* fixed extension header */
			advance = sizeof(struct ip6_frag);
			nh = ip6_next->ip6_nxt;
			break;
		case IPPROTO_TCP:
			ip6_print_post(sbuf, ip6, nh, payload_len);
			tcp_print(sbuf, cp, len);
			return;
		case IPPROTO_UDP: {
			const struct udphdr *up = (const struct udphdr *)cp;
			ip6_print_post(sbuf, ip6, nh, payload_len);
			sbuf_printf(sbuf, "%d,%d,%d", EXTRACT_16BITS(&up->uh_sport), EXTRACT_16BITS(&up->uh_dport),
				EXTRACT_16BITS(&up->uh_ulen));
			return;
		}
		case IPPROTO_VRRP:
			ip6_print_post(sbuf, ip6, nh, payload_len);
			sbuf_printf(sbuf, "%s,%d,%d,%d,%d,%d",
			    (cp[0] & 0x0f) == 1 ? "advertise" : "unkwn",
			    ip6->ip6_hlim, cp[1], (cp[0] & 0xf0) >> 4,
			    cp[2], cp[5]);
			return;
		default:
			ip6_print_post(sbuf, ip6, nh, payload_len);
			sbuf_printf(sbuf, "datalength=%d", len);
			return;
		}
	}

	ip6_print_post(sbuf, ip6, nh, payload_len);
	sbuf_printf(sbuf, "truncated-ip6=%u", len);
}

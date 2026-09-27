/*
 * Copyright (C) 2026 Brendan Bank
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sbuf.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

/* type and code names follow the pf.conf(5) icmp-type / icmp-code keywords */

struct icmp_code_tok {
	int type;
	int code;
	const char *descr;
};

static const struct tok icmp_type_values[] = {
	{ ICMP_ECHOREPLY, "echorep" },
	{ ICMP_UNREACH, "unreach" },
	{ ICMP_SOURCEQUENCH, "squench" },
	{ ICMP_REDIRECT, "redir" },
	{ ICMP_ALTHOSTADDR, "althost" },
	{ ICMP_ECHO, "echoreq" },
	{ ICMP_ROUTERADVERT, "routeradv" },
	{ ICMP_ROUTERSOLICIT, "routersol" },
	{ ICMP_TIMXCEED, "timex" },
	{ ICMP_PARAMPROB, "paramprob" },
	{ ICMP_TSTAMP, "timereq" },
	{ ICMP_TSTAMPREPLY, "timerep" },
	{ ICMP_IREQ, "inforeq" },
	{ ICMP_IREQREPLY, "inforep" },
	{ ICMP_MASKREQ, "maskreq" },
	{ ICMP_MASKREPLY, "maskrep" },
	{ ICMP_TRACEROUTE, "trace" },
	{ ICMP_DATACONVERR, "dataconv" },
	{ ICMP_MOBILE_REDIRECT, "mobredir" },
	{ ICMP_IPV6_WHEREAREYOU, "ipv6-where" },
	{ ICMP_IPV6_IAMHERE, "ipv6-here" },
	{ ICMP_MOBILE_REGREQUEST, "mobregreq" },
	{ ICMP_MOBILE_REGREPLY, "mobregrep" },
	{ ICMP_SKIP, "skip" },
	{ ICMP_PHOTURIS, "photuris" },
	{ 0, NULL }
};

static const struct icmp_code_tok icmp_code_values[] = {
	{ ICMP_UNREACH, ICMP_UNREACH_NET, "net-unr" },
	{ ICMP_UNREACH, ICMP_UNREACH_HOST, "host-unr" },
	{ ICMP_UNREACH, ICMP_UNREACH_PROTOCOL, "proto-unr" },
	{ ICMP_UNREACH, ICMP_UNREACH_PORT, "port-unr" },
	{ ICMP_UNREACH, ICMP_UNREACH_NEEDFRAG, "needfrag" },
	{ ICMP_UNREACH, ICMP_UNREACH_SRCFAIL, "srcfail" },
	{ ICMP_UNREACH, ICMP_UNREACH_NET_UNKNOWN, "net-unk" },
	{ ICMP_UNREACH, ICMP_UNREACH_HOST_UNKNOWN, "host-unk" },
	{ ICMP_UNREACH, ICMP_UNREACH_ISOLATED, "isolate" },
	{ ICMP_UNREACH, ICMP_UNREACH_NET_PROHIB, "net-prohib" },
	{ ICMP_UNREACH, ICMP_UNREACH_HOST_PROHIB, "host-prohib" },
	{ ICMP_UNREACH, ICMP_UNREACH_TOSNET, "net-tos" },
	{ ICMP_UNREACH, ICMP_UNREACH_TOSHOST, "host-tos" },
	{ ICMP_UNREACH, ICMP_UNREACH_FILTER_PROHIB, "filter-prohib" },
	{ ICMP_UNREACH, ICMP_UNREACH_HOST_PRECEDENCE, "host-preced" },
	{ ICMP_UNREACH, ICMP_UNREACH_PRECEDENCE_CUTOFF, "cutoff-preced" },
	{ ICMP_REDIRECT, ICMP_REDIRECT_NET, "redir-net" },
	{ ICMP_REDIRECT, ICMP_REDIRECT_HOST, "redir-host" },
	{ ICMP_REDIRECT, ICMP_REDIRECT_TOSNET, "redir-tos-net" },
	{ ICMP_REDIRECT, ICMP_REDIRECT_TOSHOST, "redir-tos-host" },
	{ ICMP_ROUTERADVERT, ICMP_ROUTERADVERT_NORMAL, "normal-adv" },
	{ ICMP_ROUTERADVERT, ICMP_ROUTERADVERT_NOROUTE_COMMON, "common-adv" },
	{ ICMP_TIMXCEED, ICMP_TIMXCEED_INTRANS, "transit" },
	{ ICMP_TIMXCEED, ICMP_TIMXCEED_REASS, "reassemb" },
	{ ICMP_PARAMPROB, ICMP_PARAMPROB_ERRATPTR, "badhead" },
	{ ICMP_PARAMPROB, ICMP_PARAMPROB_OPTABSENT, "optmiss" },
	{ ICMP_PARAMPROB, ICMP_PARAMPROB_LENGTH, "badlen" },
	{ ICMP_PHOTURIS, ICMP_PHOTURIS_UNKNOWN_INDEX, "unknown-ind" },
	{ ICMP_PHOTURIS, ICMP_PHOTURIS_AUTH_FAILED, "auth-fail" },
	{ ICMP_PHOTURIS, ICMP_PHOTURIS_DECRYPT_FAILED, "decrypt-fail" },
	{ 0, 0, NULL }
};

static const struct tok icmp6_type_values[] = {
	{ ICMP6_DST_UNREACH, "unreach" },
	{ ICMP6_PACKET_TOO_BIG, "toobig" },
	{ ICMP6_TIME_EXCEEDED, "timex" },
	{ ICMP6_PARAM_PROB, "paramprob" },
	{ ICMP6_ECHO_REQUEST, "echoreq" },
	{ ICMP6_ECHO_REPLY, "echorep" },
	{ MLD_LISTENER_QUERY, "listqry" },
	{ MLD_LISTENER_REPORT, "listenrep" },
	{ MLD_LISTENER_DONE, "listendone" },
	{ ND_ROUTER_SOLICIT, "routersol" },
	{ ND_ROUTER_ADVERT, "routeradv" },
	{ ND_NEIGHBOR_SOLICIT, "neighbrsol" },
	{ ND_NEIGHBOR_ADVERT, "neighbradv" },
	{ ND_REDIRECT, "redir" },
	{ ICMP6_ROUTER_RENUMBERING, "routrrenum" },
	{ ICMP6_NI_QUERY, "niqry" },
	{ ICMP6_NI_REPLY, "nirep" },
	{ MLD_MTRACE_RESP, "mtraceresp" },
	{ MLD_MTRACE, "mtrace" },
	{ MLDV2_LISTENER_REPORT, "listenrepv2" },
	{ 0, NULL }
};

static const struct icmp_code_tok icmp6_code_values[] = {
	{ ICMP6_DST_UNREACH, ICMP6_DST_UNREACH_NOROUTE, "noroute-unr" },
	{ ICMP6_DST_UNREACH, ICMP6_DST_UNREACH_ADMIN, "admin-unr" },
	{ ICMP6_DST_UNREACH, ICMP6_DST_UNREACH_BEYONDSCOPE, "beyond-unr" },
	{ ICMP6_DST_UNREACH, ICMP6_DST_UNREACH_ADDR, "addr-unr" },
	{ ICMP6_DST_UNREACH, ICMP6_DST_UNREACH_NOPORT, "port-unr" },
	{ ICMP6_TIME_EXCEEDED, ICMP6_TIME_EXCEED_TRANSIT, "transit" },
	{ ICMP6_TIME_EXCEEDED, ICMP6_TIME_EXCEED_REASSEMBLY, "reassemb" },
	{ ICMP6_PARAM_PROB, ICMP6_PARAMPROB_HEADER, "badhead" },
	{ ICMP6_PARAM_PROB, ICMP6_PARAMPROB_NEXTHEADER, "nxthdr" },
	{ ND_REDIRECT, ND_REDIRECT_ONLINK, "redironlink" },
	{ ND_REDIRECT, ND_REDIRECT_ROUTER, "redirrouter" },
	{ 0, 0, NULL }
};

static void
icmp_print_code(struct sbuf *sbuf, const struct icmp_code_tok *lp, u_int type,
    u_int code)
{
	for (; lp->descr != NULL; lp++) {
		if (lp->type == (int)type && lp->code == (int)code) {
			sbuf_printf(sbuf, "%s,", lp->descr);
			return;
		}
	}

	sbuf_printf(sbuf, "%u,", code);
}

/*
 * print an ICMP or ICMPv6 message as: datalength, type, code, id, seq, mtu
 *
 * "length" is the payload length claimed by the IP header, "caplen" is
 * what was actually captured.  Only the smaller of the two is ever read.
 * Fields not applicable to the message type are left empty.
 */
void
icmp_print(struct sbuf *sbuf, const u_char *bp, u_int length, u_int caplen,
    int v6)
{
	u_int avail = length < caplen ? length : caplen;
	u_int type, code;
	int has_idseq = 0;
	char ubuf[64];

	sbuf_printf(sbuf, "datalength=%u,", length);

	/* type and code are the only fields every ICMP message carries */
	if (avail < 2) {
		sbuf_printf(sbuf, "truncated-icmp=%u,,,,", avail);
		return;
	}

	type = bp[0];
	code = bp[1];

	sprintf(ubuf, "unknown(%u)", type);
	sbuf_printf(sbuf, "%s,", code2str(v6 ? icmp6_type_values :
	    icmp_type_values, ubuf, type));
	icmp_print_code(sbuf, v6 ? icmp6_code_values : icmp_code_values,
	    type, code);

	if (v6) {
		switch (type) {
		case ICMP6_ECHO_REQUEST:
		case ICMP6_ECHO_REPLY:
			has_idseq = 1;
			break;
		}
	} else {
		switch (type) {
		case ICMP_ECHO:
		case ICMP_ECHOREPLY:
		case ICMP_TSTAMP:
		case ICMP_TSTAMPREPLY:
		case ICMP_IREQ:
		case ICMP_IREQREPLY:
		case ICMP_MASKREQ:
		case ICMP_MASKREPLY:
			has_idseq = 1;
			break;
		}
	}

	/* id and seq are the 16 bit words at offset 4 and 6 */
	if (has_idseq && avail >= 8)
		sbuf_printf(sbuf, "%u,%u,", EXTRACT_16BITS(bp + 4),
		    EXTRACT_16BITS(bp + 6));
	else
		sbuf_printf(sbuf, ",,");

	if (v6 && type == ICMP6_PACKET_TOO_BIG && avail >= 8)
		sbuf_printf(sbuf, "%u", EXTRACT_32BITS(bp + 4));
	else if (!v6 && type == ICMP_UNREACH && code == ICMP_UNREACH_NEEDFRAG &&
	    avail >= 8)
		sbuf_printf(sbuf, "%u", EXTRACT_16BITS(bp + 6));
}

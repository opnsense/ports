
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sbuf.h>
#include <sys/file.h>
#include <sys/ioctl.h>

#include <net/if.h>
#include <pcap/pcap.h>

#include <net/pfvar.h>
#include <net/if_pflog.h>

#include <netinet/ip.h>

#include <stdlib.h>
#include <syslog.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

static pcap_t *tap = NULL;
static char *filterlog_pcap_file = NULL;
static char errbuf[PCAP_ERRBUF_SIZE];
static struct sbuf sbuf;
static char *sbuf_buf;
static char *pidfile;
static char **rulelabels = NULL;
static int rulelabels_max = -1;

#define RULELABELS_STEP 64 /* could be higher but force use of realloc to ensure it works */

static const struct tok pf_reasons[] = {
	{ 0,	"match" },
	{ 1,	"bad-offset" },
	{ 2,	"fragment" },
	{ 3,	"short" },
	{ 4,	"normalize" },
	{ 5,	"memory" },
	{ 6,	"bad-timestamp" },
	{ 7,	"congestion" },
	{ 8,	"ip-option" },
	{ 9,	"proto-cksum" },
	{ 10,	"state-mismatch" },
	{ 11,	"state-insert" },
	{ 12,	"state-limit" },
	{ 13,	"src-limit" },
	{ 14,	"synproxy" },
	{ 0,	NULL }
};

static const struct tok pf_actions[] = {
	{ PF_PASS,		"pass" },
	{ PF_DROP,		"block" },
	{ PF_SCRUB,		"scrub" },
	{ PF_NAT,		"nat" },
	{ PF_NONAT,		"nat" },
	{ PF_BINAT,		"binat" },
	{ PF_NOBINAT,		"binat" },
	{ PF_RDR,		"rdr" },
	{ PF_NORDR,		"rdr" },
	{ PF_SYNPROXY_DROP,	"synproxy-drop" },
	{ 0,			NULL }
};

static const struct tok pf_directions[] = {
	{ PF_INOUT,	"in/out" },
	{ PF_IN,	"in" },
	{ PF_OUT,	"out" },
	{ 0,		NULL }
};

const char *
code2str(const struct tok *trans, const char *unknown, int action)
{
	int i = 0;

	for (;;) {
		if (trans[i].descr == NULL)
			return unknown;

		if (action == trans[i].action)
			return (trans[i].descr);

		i++;
	}

	return (unknown);
}

static void
decode_packet(u_char *user __unused, const struct pcap_pkthdr *pkthdr, const u_char *packet)
{
	const char *label = "0";
	const struct pfloghdr *hdr;
	const struct ip *ip;
	u_int length = pkthdr->len;
	u_int hdrlen;
	u_int caplen = pkthdr->caplen;
	u_int32_t subrulenr;
	u_int32_t rulenr;
	char ubuf[64];

	/* check length */
	if (caplen < sizeof(u_int8_t)) {
		sbuf_printf(&sbuf, "[|pflog]");
		goto printsbuf;
	}

#define MIN_PFLOG_HDRLEN	45
	hdr = (const struct pfloghdr *)packet;
	if (hdr->length < MIN_PFLOG_HDRLEN) {
		sbuf_printf(&sbuf, "[pflog: invalid header length!]");
		goto printsbuf;
	}
	hdrlen = BPF_WORDALIGN(hdr->length);

	if (caplen < hdrlen) {
		sbuf_printf(&sbuf, "[|pflog]");
		goto printsbuf;
	}

	/* print what we know */
	rulenr = EXTRACT_32BITS(&hdr->rulenr);
	if (rulenr == (u_int32_t)-1)
		sbuf_printf(&sbuf, ",");
	else
		sbuf_printf(&sbuf, "%u,", rulenr);
	subrulenr = EXTRACT_32BITS(&hdr->subrulenr);
	if (subrulenr == (u_int32_t)-1)
		sbuf_printf(&sbuf, ",,");
	else
		sbuf_printf(&sbuf, "%u,%s,", subrulenr, hdr->ruleset); 

	if (rulelabels) {
		switch (hdr->action) {
		case PF_NAT:
		case PF_NONAT:
		case PF_BINAT:
		case PF_NOBINAT:
		case PF_RDR:
		case PF_NORDR:
			/* no label support for NAT types */
			break;
		default:
			if ((int)rulenr >= 0 &&
			    (int)rulenr < rulelabels_max + 1) {
				if (rulelabels[rulenr]) {
					label = rulelabels[rulenr];
				}
			}
			break;
		}
	}

	sbuf_printf(&sbuf, "%s,%s,", label, hdr->ifname);
        sprintf(ubuf, "unknown(%u)", hdr->reason);
	sbuf_printf(&sbuf, "%s,", code2str(pf_reasons, ubuf, hdr->reason));
        sprintf(ubuf, "unknown(%u)", hdr->action);
	sbuf_printf(&sbuf, "%s,", code2str(pf_actions, ubuf, hdr->action));
        sprintf(ubuf, "unknown(%u)", hdr->dir);
	sbuf_printf(&sbuf, "%s,", code2str(pf_directions, ubuf, hdr->dir));

	/* skip to the real packet */
	length -= hdrlen;
	packet += hdrlen;
	ip = (const struct ip *)packet;

        if (length < 4) {
                sbuf_printf(&sbuf, "%d,truncated-ip=%u", IP_V(ip), length);
		goto printsbuf;
        }

        switch (IP_V(ip)) {
        case 4:
                ip_print(&sbuf, packet, length);
		break;
        case 6:
                ip6_print(&sbuf, packet, length);
		break;
        default:
                sbuf_printf(&sbuf, "%d", IP_V(ip));
                break;
        }

printsbuf:
	sbuf_finish(&sbuf);
	if (filterlog_pcap_file != NULL)
		printf("%s\n", sbuf_data(&sbuf));
	else
		syslog(LOG_INFO, "%s", sbuf_data(&sbuf));
	memset(sbuf_data(&sbuf), 0, sbuf_len(&sbuf));
	sbuf_clear(&sbuf);
	return;
}

static void
free_rulelabels(void)
{
	int i;

	if (!rulelabels) {
		return;
	}

	/* one more for probable offset */
	for (i = 0; i < rulelabels_max + 1; ++i) {
		if (rulelabels[i]) {
			free(rulelabels[i]);
			rulelabels[i] = NULL;
		}
	}

	free(rulelabels);

	rulelabels_max = -1;
	rulelabels = NULL;
}

static int
realloc_rulelabels(int nr)
{
	void *new = NULL;

	if (rulelabels_max >= nr && rulelabels) {
		return (0);
	}

	nr += RULELABELS_STEP;

	/* one more for probable offset */
	new = calloc(nr + 1, sizeof(char *));
	if (!new) {
		return (1);
	}

	if (rulelabels) {
		/* one more for probable offset */
		memcpy(new, rulelabels, sizeof(char *) * (rulelabels_max + 1));
		free(rulelabels);
	}

	rulelabels = new;
	rulelabels_max = nr;

	return (0);
}

static int
get_rulelabels(void)
{
	struct pfioc_rule pr;
	u_int32_t nr, i;
	int dev;

	bzero(&pr, sizeof(pr));
	pr.rule.action = PF_PASS;

	if ((dev = open("/dev/pf", O_RDONLY)) == -1) {
		return (1);
	}

	bzero(&pr, sizeof(pr));
	pr.rule.action = PF_PASS;

	if (ioctl(dev, DIOCGETRULES, &pr)) {
		return (1);
	}

	for (nr = pr.nr, i = 0; i < nr; i++) {
		pr.nr = i;

		if (ioctl(dev, DIOCGETRULE, &pr)) {
			return (1);
		}

		if (realloc_rulelabels(pr.rule.nr)) {
			return (1);
		}

		if (pr.rule.label[0]) {
			rulelabels[pr.rule.nr] = strdup(pr.rule.label);
		}
	}

	close(dev);

	return (0);
}

int
main(int argc, char **argv)
{
	int perr, ch, labels_only = 0;
	char *interface;

	pidfile = NULL;
	interface = filterlog_pcap_file = NULL;
	tzset();

	while ((ch = getopt(argc, argv, "i:lp:P:")) != -1) {
		switch (ch) {
		case 'i':
			interface = optarg;
			break;
		case 'l':
			labels_only = 1;
			break;
		case 'p':
			pidfile = optarg;
			break;
		case 'P':
			filterlog_pcap_file = optarg;
			break;
		default:
			printf("Unknown option specified\n");
			return (-1);
		}
	}

	if (get_rulelabels()) {
		printf("Could not load rule labels: continuing without them\n");
		free_rulelabels();
	}

	if (labels_only) {
		int i;

		/* one more for probable offset */
		for (i = 0; i < rulelabels_max + 1; ++i) {
			if (rulelabels[i]) {
				printf("%d: %s\n", i, rulelabels[i]);
			}
		}

		exit(rulelabels ? 0 : 1);
	}

	if (interface == NULL && filterlog_pcap_file == NULL) {
		printf("Should specify an interface or a pcap file\n");
		exit(-1);
	}

	if (filterlog_pcap_file == NULL)
		daemon(0, 0);

	if (pidfile) {
		FILE *pidfd;

                /* write PID to file */
                pidfd = fopen(pidfile, "w");
                if (pidfd) {
                        while (flock(fileno(pidfd), LOCK_EX) != 0)
                                ;
                        fprintf(pidfd, "%d\n", getpid());
                        flock(fileno(pidfd), LOCK_UN);
                        fclose(pidfd);
                } else
                        syslog(LOG_WARNING, "could not open pid file");
        }

	do {
		sbuf_buf = calloc(1, 2048);
	} while (sbuf_buf == NULL);

	sbuf_new(&sbuf, sbuf_buf, 2048, SBUF_AUTOEXTEND);

	openlog("filterlog", LOG_NDELAY, LOG_LOCAL0);

	while (1) {
		if (tap != NULL)
			pcap_close(tap);

		if (filterlog_pcap_file != NULL)
			tap = pcap_open_offline(filterlog_pcap_file, errbuf);
		else
			tap = pcap_open_live(interface, MAXIMUM_SNAPLEN, 1, 1000, errbuf);
		if (tap == NULL) {
			syslog(LOG_ERR, "Failed to initialize: %s(%m)", errbuf);
			return (-1);
		}

		if (pcap_datalink(tap) != DLT_PFLOG) {
			syslog(LOG_ERR, "Invalid datalink type");
			pcap_close(tap);
			tap = NULL;
			return (-1);
		}

		perr = pcap_loop(tap, -1, decode_packet, NULL);
		if (perr == -1) {
			syslog(LOG_ERR, "An error occured while reading device %s: %m", interface);
		} else if (perr == -2) {
			pcap_close(tap);
			break;
		} else if (perr == 0) {
			pcap_close(tap);
			tap = NULL;
		}

		if (filterlog_pcap_file != NULL)
			break;
	}

	free_rulelabels();
	closelog();

	return (0);
}

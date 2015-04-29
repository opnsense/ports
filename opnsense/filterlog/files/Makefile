PROG=	filterlog
BINDIR= ${PREFIX}/sbin

SRCS=	print-ip.c print-ip6.c print-ip6opts.c print-tcp.c \
	print-mobility.c filterlog.c
MAN=

LDADD+=	-lsbuf -lpcap

.include <bsd.prog.mk>

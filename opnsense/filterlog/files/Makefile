PROG=	filterlog
BINDIR= ${PREFIX}/sbin

SRCS=	print-ip.c print-ip6.c print-tcp.c filterlog.c
MAN=

WARNS=	3

LDADD+=	-lsbuf -lpcap ${LIBS} -lpfctl

.include <bsd.prog.mk>

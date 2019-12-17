#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD$

.include <bsd.own.mk>

.PATH: ${SRCTOP}/usr.bin/wall

PROG=	syslogd
MAN=	syslog.conf.5 syslogd.8
SRCS=	syslogd.c ttymsg.c

LIBADD=	util
DPADD=	${LIBUTIL}	# XXX FreeBSD 11.1
LDADD=	-lutil		# XXX FreeBSD 11.1

WARNS?= 3

.if ${MK_INET6_SUPPORT} != "no"
CFLAGS+= -DINET6
.endif

CFLAGS+= -I${SRCTOP}/usr.bin/wall

.include <bsd.prog.mk>

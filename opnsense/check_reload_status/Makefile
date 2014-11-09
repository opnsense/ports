# New ports collection makefile for:	php4
# Date created:				Tue Feb 18 11:17:13 CET 2003
# Whom:					Alex Dupre <sysadmin@alexdupre.com>
#
# $FreeBSD: ports/lang/php4/Makefile,v 1.88 2005/07/13 19:56:27 ale Exp $
#

PORTNAME=	check_reload_status
PORTVERSION=	0.0.3
PORTREVISION?=	0
CATEGORIES?=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER?=	eri@pfsense.org
COMMENT?=	run various pfSense scripts on event.

WHERE=		/usr/local/sbin
PLIST_FILES=    ${WHERE}/${PORTNAME} ${WHERE}/pfSctl ${WHERE}/fcgicli
CFLAGS+=	-I/usr/local/include -L/usr/local/lib 

CFLAGS+=	-Wsystem-headers -Werror -Wall -Wno-format-y2k -W \
                -Wno-unused-parameter -Wstrict-prototypes \
                -Wmissing-prototypes -Wpointer-arith -Wreturn-type \
                -Wcast-qual -Wwrite-strings -Wswitch -Wshadow \
                -Wunused-parameter -Wchar-subscripts -Winline \
                -Wnested-externs -Wredundant-decls -Wno-pointer-sign

LIB_DEPENDS=   event:${PORTSDIR}/devel/libevent2

do-extract:
	mkdir -p ${WRKSRC}

do-build:
#	${CC} ${CFLAGS} -lsbuf -levent -o ${WRKSRC}/${PORTNAME} ${FILESDIR}/${PORTNAME}.c
	${CC} ${CFLAGS} -o ${WRKSRC}/pfSctl ${FILESDIR}/pfSctl.c
#	${CC} ${CFLAGS} -lsbuf -o ${WRKSRC}/fcgicli ${FILESDIR}/fcgicli.c
	

do-install:
#	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${WHERE}/
	${INSTALL_PROGRAM} ${WRKSRC}/pfSctl ${WHERE}/
#	${INSTALL_PROGRAM} ${WRKSRC}/fcgicli ${WHERE}/

.include <bsd.port.mk>

# New ports collection makefile for:	php4
# Date created:				Tue Feb 18 11:17:13 CET 2003
# Whom:					Alex Dupre <sysadmin@alexdupre.com>
#
# $FreeBSD: ports/lang/php4/Makefile,v 1.88 2005/07/13 19:56:27 ale Exp $
#

PORTNAME=	clog
PORTVERSION=	1.0.1
PORTREVISION?=	0
CATEGORIES?=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER?=	sullrich@gmail.com
COMMENT?=	Circular log support for FreeBSD syslogd

PREFIX=		/usr/local
WHERE=		sbin
PLIST_FILES=    ${WHERE}/${PORTNAME} local/include/clog.h

# -O2 is dangerous for clog! It breaks on i386 -O works.
CFLAGS+=	-O

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -o ${WRKSRC}/${PORTNAME} ${FILESDIR}/${PORTNAME}.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/${WHERE}
	${MKDIR} ${STAGEDIR}/${PREFIX}/local/include
	${INSTALL_DATA} ${FILESDIR}/${PORTNAME}.h ${STAGEDIR}${PREFIX}/local/include

.include <bsd.port.mk>

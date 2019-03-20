# $FreeBSD$

PORTNAME=	ifinfo
PORTVERSION=	10.1
CATEGORIES=	sysutils
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	Interface statistics reader

LICENSE=	MIT

USE_HARDENING=	safestack

MAKE_ENV=	BINDIR=${PREFIX}/sbin

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

.include <bsd.port.mk>

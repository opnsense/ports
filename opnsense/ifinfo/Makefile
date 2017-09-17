# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	ifinfo
PORTVERSION=	10.1
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	Interface statistics reader

LICENSE=	MIT

USE_HARDENING=	safestack

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

.include <bsd.port.mk>

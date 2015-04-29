# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	pfSense
PORTVERSION=	0.2
PORTREVISION=	2
CATEGORIES=	devel
MASTER_SITES=
DISTFILES=
PKGNAMEPREFIX=	php-

MAINTAINER=	franco@opnsense.org
COMMENT=	Library for getting useful info

USE_PHP=	yes
USE_PHPEXT=	yes

CONFIGURE_ARGS=	--enable-pfSense

do-extract:
	${MKDIR} ${WRKSRC}
	${CP} ${FILESDIR}/* ${WRKSRC}

.include <bsd.port.mk>

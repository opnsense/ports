# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	pfSense
PORTVERSION=	0.2
PORTREVISION=	4
PKGNAMEPREFIX=	php-
CATEGORIES=	devel
MASTER_SITES=
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	Library for getting useful info

USE_PHP=	yes
USE_PHPEXT=	yes

CONFIGURE_ARGS=	--enable-pfSense

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

.include <bsd.port.mk>

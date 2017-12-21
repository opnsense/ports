# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	snuffleupagus
PORTVERSION=	0.1.0
DISTVERSIONPREFIX=v
CATEGORIES=	security

MAINTAINER=	franco@opnsense.org
COMMENT=	Security module for PHP 7

LICENSE=	LGPL3
LICENSE_FILE=	${WRKSRC}/../LICENSE

WRKSRC_SUBDIR=	src

USES=		localbase php:ext
USE_PHP=	hash:build

USE_GITHUB=	yes
GH_ACCOUNT=	nbs-system

CONFIGURE_ARGS=	--enable-snuffleupagus

.include <bsd.port.mk>

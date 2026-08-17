PORTNAME=	xmlrpc
DISTVERSIONPREFIX=	xmlrpc-
DISTVERSION=	1.0.0RC3
PORTREVISION=	4
PORTEPOCH=	1
CATEGORIES=	net pear
PKGNAMEPREFIX=	${PHP_PKGNAMEPREFIX}

MAINTAINER=	dereks@lifeofadishwasher.com
COMMENT=	Functions to write XML-RPC servers and clients
WWW=		https://github.com/php/pecl-networking-xmlrpc

LICENSE=	PHP301
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		gnome iconv:translit php:ext pkgconfig
USE_GITHUB=	yes
GH_ACCOUNT=	php
GH_PROJECT=	pecl-networking-xmlrpc
USE_GNOME=	libxml2
USE_PHP=	xml:build
IGNORE_WITH_PHP=	86

CONFIGURE_ARGS+=	--with-iconv-dir=${LOCALBASE}

TEST_ENV=	NO_INTERACTION=yes
TEST_TARGET=	test

.include <bsd.port.mk>

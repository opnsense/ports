# $FreeBSD$

PORTNAME=	snuffleupagus
DISTVERSIONPREFIX=v
DISTVERSION=	0.5.1
CATEGORIES=	security
PKGNAMEPREFIX=	${PHP_PKGNAMEPREFIX}

MAINTAINER=	franco@opnsense.org
COMMENT=	Security module for PHP 7+

LICENSE=	LGPL3
LICENSE_FILE=	${WRKSRC}/../LICENSE

LIB_DEPENDS=	libpcre.so:devel/pcre

USES=		localbase:ldflags php:ext
USE_PHP=	hash:build session:build

TEST_TARGET=	test

WRKSRC_SUBDIR=	src

USE_GITHUB=	yes
GH_ACCOUNT=	jvoisin

CONFIGURE_ARGS=	--enable-snuffleupagus

# Fix build with clang11
CFLAGS+=	-fcommon

.include <bsd.port.mk>

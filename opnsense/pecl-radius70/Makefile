# Created by: Antonio Carlos Venancio Junior (<antonio@inf.ufsc.br>)
# $FreeBSD$

PORTNAME=	radius
DISTVERSION=	1.4.0b1
CATEGORIES=	net security pear
PKGNAMESUFFIX=	70

MAINTAINER=	joneum@FreeBSD.org
COMMENT=	Radius client library for PHP

LICENSE=	BSD3CLAUSE

USES=		php:pecl

CONFLICTS_INSTALL=pecl-radius pecl-radius[!7][!0]

BUILD_DEPENDS=	php${PKGNAMESUFFIX}>=0:lang/php${PKGNAMESUFFIX}

CONFIGURE_ARGS=	--enable-radius

post-install:
	${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/examples/* ${STAGEDIR}${EXAMPLESDIR}

.include <bsd.port.mk>

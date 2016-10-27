# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	suhosin7
PORTVERSION=	0.0.0.20161013
CATEGORIES=	security
PKGNAMEPREFIX=	php-

MAINTAINER=	franco@opnsense.org
COMMENT=	PHP extension that implements high-level protections

LICENSE=	PHP301
LICENSE_FILE=	${WRKSRC}/LICENSE

USE_GITHUB=	yes
GH_ACCOUNT=	sektioneins
GH_TAGNAME=	e55e273

OPTIONS_DEFINE=	EXAMPLES

USES=		php:ext
USE_PHP=	hash:build session:build
IGNORE_WITH_PHP=55 56

CONFIGURE_ARGS=	--enable-suhosin

PORTEXAMPLES=	suhosin7.ini

post-install:
	${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/suhosin7.ini ${STAGEDIR}${EXAMPLESDIR}

.include <bsd.port.mk>

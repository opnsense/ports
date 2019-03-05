# $FreeBSD$

PORTNAME=	phpseclib
DISTVERSION=	2.0.14
CATEGORIES=	security devel
PKGNAMEPREFIX=	${PHP_PKGNAMEPREFIX}

MAINTAINER=	franco@opnsense.org
COMMENT=	PHP Secure Communications Library

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		php:flavors

USE_GITHUB=	yes

NO_ARCH=	yes
NO_BUILD=	yes

do-install:
	@cd ${WRKSRC}/${PORTNAME} && ${COPYTREE_SHARE} . ${STAGEDIR}${DATADIR}

.include <bsd.port.mk>

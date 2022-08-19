PORTNAME=	phpseclib2_compat
DISTVERSION=	1.0.4
CATEGORIES=	security devel
PKGNAMEPREFIX=	${PHP_PKGNAMEPREFIX}

MAINTAINER=	franco@opnsense.org
COMMENT=	PHP Secure Communications Library

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		php:flavors

USE_GITHUB=	yes
GH_ACCOUNT=	phpseclib

NO_ARCH=	yes
NO_BUILD=	yes

do-install:
	@cd ${WRKSRC}/src && ${COPYTREE_SHARE} . ${STAGEDIR}${DATADIR}

.include <bsd.port.mk>

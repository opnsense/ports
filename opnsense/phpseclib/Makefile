PORTNAME=	phpseclib
DISTVERSION=	3.0.47
CATEGORIES=	security devel
PKGNAMEPREFIX=	${PHP_PKGNAMEPREFIX}

MAINTAINER=	franco@opnsense.org
COMMENT=	PHP Secure Communications Library
WWW=		https://phpseclib.com

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		php:flavors

USE_GITHUB=	yes
GH_ACCOUNT=	phpseclib paragonie:cte
GH_PROJECT=	constant_time_encoding:cte
GH_TAGNAME=	v2.6.3:cte

NO_ARCH=	yes
NO_BUILD=	yes

do-install:
	@cd ${WRKSRC}/${PORTNAME} && ${COPYTREE_SHARE} . ${STAGEDIR}${DATADIR}
	@cd ${WRKSRC_cte}/src && ${COPYTREE_SHARE} . \
		 ${STAGEDIR}${DATADIR}/paragonie

.include <bsd.port.mk>

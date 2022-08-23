PORTNAME=	phpseclib
DISTVERSION=	3.0.14
CATEGORIES=	security devel
PKGNAMEPREFIX=	${PHP_PKGNAMEPREFIX}

MAINTAINER=	franco@opnsense.org
COMMENT=	PHP Secure Communications Library

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		php:flavors

USE_GITHUB=	yes
GH_ACCOUNT=	phpseclib paragonie:depend
GH_PROJECT=	constant_time_encoding:depend
GH_TAGNAME=	v2.6.3:depend

NO_ARCH=	yes
NO_BUILD=	yes

post-extract:
	@${MV} ${WRKSRC_depend}/src ${WRKSRC}/${PORTNAME}/paragonie

do-install:
	@cd ${WRKSRC}/${PORTNAME} && ${COPYTREE_SHARE} . ${STAGEDIR}${DATADIR}

.include <bsd.port.mk>

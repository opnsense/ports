PORTNAME=	google-api-php-client
DISTVERSION=	2.4.0
MASTER_SITES=	https://github.com/googleapis/${PORTNAME}/releases/download/v${DISTVERSION}/
EXTRACT_SUFX=	.zip
CATEGORIES=	devel
PKGNAMEPREFIX=	${PHP_PKGNAMEPREFIX}

MAINTAINER=	ad@opnsense.org
COMMENT=	Google APIs Client Library for PHP
WWW=		https://github.com/googleapis/google-api-php-client

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		php:flavors

NO_ARCH=	yes
NO_BUILD=	yes

do-install:
	@cd ${WRKSRC} && ${COPYTREE_SHARE} . ${STAGEDIR}${DATADIR}

.include <bsd.port.mk>

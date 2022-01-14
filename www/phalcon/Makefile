PORTNAME=	phalcon
DISTVERSIONPREFIX=	v
DISTVERSION=	5.0.0beta2
CATEGORIES=	www
PKGNAMEPREFIX=	${PHP_PKGNAMEPREFIX}

MAINTAINER=	franco@opnsense.org
COMMENT=	Phalcon PHP Framework written in C-language

LICENSE=	BSD3CLAUSE

RUN_DEPENDS=	${PHPBASE}/lib/php/${PHP_EXT_DIR}/psr.so:devel/pecl-psr@${PHP_FLAVOR}

IGNORE_WITH_PHP=73 81
USES=		localbase php:ext
USE_PHP=	json:build pdo:build session:build

CONFLICTS_INSTALL=	${PKGNAMEPREFIX}phalcon4

USE_GITHUB=	yes
GH_PROJECT=	c${PORTNAME}

CONFIGURE_ARGS=	--enable-phalcon
WRKSRC_SUBDIR=	build/phalcon

.include <bsd.port.mk>

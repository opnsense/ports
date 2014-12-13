PORTNAME=	pfSense
PORTVERSION=	0.1
PORTREVISION=	6
CATEGORIES=	devel
MASTER_SITES=
DISTFILES=
PKGNAMEPREFIX=	php-

MAINTAINER=	franco@opnsense.org
COMMENT=	Library for getting useful info

USE_PHP=	yes
USE_PHPEXT=	yes

CONFIGURE_ARGS=	--enable-pfSense

extract:
	mkdir -p ${WRKSRC}
	cp -r files/* ${WRKSRC}

.include <bsd.port.mk>

PORTNAME=	pfSense
PORTVERSION=	0.2
PORTREVISION=	0
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
	cp ${FILESDIR}/* ${WRKSRC}

.include <bsd.port.mk>

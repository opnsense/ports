PORTNAME=	update
PORTVERSION=	25.7
CATEGORIES=	sysutils
PKGNAMEPREFIX=	${GH_ACCOUNT}-

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense update utilities
WWW=		https://github.com/opnsense/update

LICENSE=	BSD2CLAUSE

LIB_DEPENDS+=	libucl.so:textproc/libucl

USES=		ssl

MAKE_ENV=	UPDATE_RELEASE=${PORTVERSION} UPDATE_FREEBSD=${OSREL}

USE_GITHUB=	yes
GH_ACCOUNT=	${CATEGORIES:[1]}
#GH_TAGNAME=	0c9eb09

.include <bsd.port.mk>

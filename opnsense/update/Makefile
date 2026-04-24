PORTNAME=	update
PORTVERSION=	26.1.6
CATEGORIES=	sysutils
PORTREVISION=	1
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
GH_TAGNAME=	322b953

.include <bsd.port.mk>

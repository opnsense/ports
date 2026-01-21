PORTNAME=	update
.if "${PRODUCT_ABI}" == "26.1"
PORTVERSION=	26.1.r1
.else
PORTVERSION=	25.7.11
.endif
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
.if "${PRODUCT_ABI}" == "26.1"
GH_TAGNAME=	0e4b7e4
.else
GH_TAGNAME=	4a0f430
.endif

.include <bsd.port.mk>

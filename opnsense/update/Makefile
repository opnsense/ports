PORTNAME=	update
.if "${PRODUCT_ABI}" == "26.7"
PORTVERSION=	26.7.b
.else
PORTVERSION=	26.1.11
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
GH_TAGNAME=	b97e990

.include <bsd.port.mk>

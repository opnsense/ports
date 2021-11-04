PORTNAME=	update
.if "${PRODUCT_ABI}" != 22.1
PORTVERSION=	21.7.4
PORTREVISION=	1
.else
PORTVERSION=	22.1.b1
.endif
CATEGORIES=	sysutils
PKGNAMEPREFIX=	${GH_ACCOUNT}-

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense update utilities

LICENSE=	BSD2CLAUSE

LIB_DEPENDS+=	libucl.so:textproc/libucl

USES=		ssl

MAKE_ENV=	UPDATE_RELEASE=${PORTVERSION}

USE_GITHUB=	yes
GH_ACCOUNT=	${CATEGORIES:[1]}
.if "${PRODUCT_ABI}" != 22.1
GH_TAGNAME=	2187ea8
.else
GH_TAGNAME=	83d69c3
.endif

.include <bsd.port.mk>

PORTNAME=	update
.if "${PRODUCT_ABI}" == 22.7
PORTVERSION=	22.7.r
.else
PORTVERSION=	22.1.9
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
.if "${PRODUCT_ABI}" == 22.7
GH_TAGNAME=	8425bb9
.else
GH_TAGNAME=	7f6e385
.endif


.include <bsd.port.mk>

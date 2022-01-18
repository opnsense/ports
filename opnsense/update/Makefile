PORTNAME=	update
.if "${PRODUCT_ABI}" != 22.1
PORTVERSION=	21.7.8
.else
PORTVERSION=	22.1.r2
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
GH_TAGNAME=	a78649a
.else
GH_TAGNAME=	7f7c464
.endif

.include <bsd.port.mk>

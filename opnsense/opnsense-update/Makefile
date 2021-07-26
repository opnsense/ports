PORTNAME=	opnsense-update
.if "${PRODUCT_ABI}" != 21.7
PORTVERSION=	21.1.8
PORTREVISION=	1 # GH_TAGNAME
.else
PORTVERSION=	21.7
#PORTREVISION=	1 # GH_TAGNAME
.endif
CATEGORIES=	sysutils

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense update utilities

LICENSE=	BSD2CLAUSE

LIB_DEPENDS+=	libucl.so:textproc/libucl

USES=		ssl

USE_HARDENING=	safestack

MAKE_ENV=	UPDATE_RELEASE=${PORTVERSION}

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
GH_PROJECT=	update
.if "${PRODUCT_ABI}" != 21.7
GH_TAGNAME=	eba62c4
.endif

.include <bsd.port.mk>

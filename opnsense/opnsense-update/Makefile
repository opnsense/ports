# $FreeBSD$

PORTNAME=	opnsense-update
.if "${PRODUCT_ABI}" == 20.7
PORTVERSION=	20.7.8
.else
PORTVERSION=	21.1.1
PORTREVISION=	2 # GH_TAGNAME
.endif
CATEGORIES=	sysutils

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense update utilities

LICENSE=	BSD2CLAUSE

LIB_DEPENDS+=	libucl.so:textproc/libucl

USES=		ssl

USE_HARDENING=	safestack

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
GH_PROJECT=	update
.if "${PRODUCT_ABI}" != 20.7
GH_TAGNAME=	808cb31
.endif

.include <bsd.port.mk>

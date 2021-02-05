# $FreeBSD$

PORTNAME=	opnsense-update
.if "${PRODUCT_ABI}" == 21.1
PORTVERSION=	21.1
PORTREVISION=	2 # GH_TAGNAME
.else
PORTVERSION=	20.7.8
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
.if "${PRODUCT_ABI}" == 21.1
GH_TAGNAME=	09f015c
.endif

.include <bsd.port.mk>

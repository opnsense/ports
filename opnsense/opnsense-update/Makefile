# $FreeBSD$

PORTNAME=	opnsense-update
.if "${PRODUCT_ABI}" == 21.1
PORTVERSION=	21.1
.else
PORTVERSION=	20.7.8
.endif
#PORTREVISION=	0 # GH_TAGNAME
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
#GH_TAGNAME=	823183f

.include <bsd.port.mk>

# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	opnsense-update
PORTVERSION=	17.1.7
PORTREVISION=	2 # GH_TAGNAME
CATEGORIES=	sysutils

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense update utilities

LICENSE=	BSD2CLAUSE

LIB_DEPENDS+=	libucl.so:textproc/libucl

USES=		ssl
USE_HARDENING=	pie relro safestack

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
GH_PROJECT=	update
GH_TAGNAME=	17bd3ca

.include <bsd.port.mk>

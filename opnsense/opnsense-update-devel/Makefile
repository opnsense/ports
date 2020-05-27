# $FreeBSD$

PORTNAME=	opnsense-update
PORTVERSION=	20.7.b2
PORTREVISION=	0 # GH_TAGNAME
PKGNAMESUFFIX=	-devel
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
GH_TAGNAME=	8b453b4

.include <bsd.port.mk>

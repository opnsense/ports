# $FreeBSD$

PORTNAME=	opnsense-update
PORTVERSION=	19.7.2
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
#GH_TAGNAME=	dec6ce2

.include <bsd.port.mk>

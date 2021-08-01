PORTNAME=	opnsense-update
PORTVERSION=	21.7
#PORTREVISION=	1 # GH_TAGNAME
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
#GH_TAGNAME=	9abe08e

.include <bsd.port.mk>

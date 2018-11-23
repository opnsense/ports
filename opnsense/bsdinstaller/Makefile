# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	bsdinstaller
PORTVERSION=	18.7
#PORTREVISION=	0 # GH_TAGNAME
CATEGORIES=	sysutils

MAINTAINER=	franco@opnsense.org
COMMENT=	BSD Installer mega-package

LICENSE=	BSD3CLAUSE

RUN_DEPENDS=	cpdup:sysutils/cpdup

USE_HARDENING=	pie:off relro:off
USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
#GH_TAGNAME=	a95d672

.include <bsd.port.mk>

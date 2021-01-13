# $FreeBSD$

PORTNAME=	bsdinstaller
.if "${PRODUCT_ABI}" == 21.1
PORTVERSION=	21.1
.else
PORTVERSION=	20.7
.endif
#PORTREVISION=	1 # GH_TAGNAME
CATEGORIES=	sysutils

MAINTAINER=	franco@opnsense.org
COMMENT=	BSD Installer mega-package

LICENSE=	BSD3CLAUSE

RUN_DEPENDS=	cpdup:sysutils/cpdup

USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
#GH_TAGNAME=	4fa95bb

.include <bsd.port.mk>

# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	bsdinstaller
PORTVERSION=	17.1
CATEGORIES=	sysutils

MAINTAINER=	franco@opnsense.org
COMMENT=	BSD Installer mega-package

LICENSE=	BSD3CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense

RUN_DEPENDS=	cpdup:sysutils/cpdup

post-install:
	${MV} ${STAGEDIR}${PREFIX}/bin/lua ${STAGEDIR}${PREFIX}/bin/lua50
	${MV} ${STAGEDIR}${PREFIX}/bin/luac ${STAGEDIR}${PREFIX}/bin/lua50c

.include <bsd.port.mk>

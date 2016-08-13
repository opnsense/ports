# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	bsdinstaller
PORTVERSION=	16.7
PORTREVISION=	1
CATEGORIES=	sysutils

MAINTAINER=	franco@opnsense.org
COMMENT=	BSD Installer mega-package

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
GH_PROJECT=	bsdinstaller
GH_TAGNAME=	7cd41b1

RUN_DEPENDS=	cpdup:sysutils/cpdup

post-install:
	# XXX migrate this to upstream repository
	${MV} ${STAGEDIR}${PREFIX}/bin/lua ${STAGEDIR}${PREFIX}/bin/lua50
	${MV} ${STAGEDIR}${PREFIX}/bin/luac ${STAGEDIR}${PREFIX}/bin/lua50c

.include <bsd.port.mk>

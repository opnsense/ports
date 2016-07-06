# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	bsdinstaller
PORTVERSION=	16.7.r
PORTREVISION=	1
CATEGORIES=	sysutils
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	BSD Installer mega-package

RUN_DEPENDS=	cpdup:sysutils/cpdup

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

post-install:
	${MV} ${STAGEDIR}${PREFIX}/bin/lua ${STAGEDIR}${PREFIX}/bin/lua50
	${MV} ${STAGEDIR}${PREFIX}/bin/luac ${STAGEDIR}${PREFIX}/bin/lua50c

.include <bsd.port.mk>

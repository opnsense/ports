# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	bsdinstaller
PORTVERSION=	2.3
PORTREVISION=	2
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	BSD Installer mega-package

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

post-install:
	${MV} ${STAGEDIR}${PREFIX}/bin/lua ${STAGEDIR}${PREFIX}/bin/lua50
	${MV} ${STAGEDIR}${PREFIX}/bin/luac ${STAGEDIR}${PREFIX}/bin/lua50c
	${CP} -r ${WRKSRC}/extra ${STAGEDIR}${PREFIX}/installer

.include <bsd.port.mk>

# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	bsdinstaller
PORTVERSION=	17.1
PORTREVISION=	1 # GH_TAGNAME
CATEGORIES=	sysutils

MAINTAINER=	franco@opnsense.org
COMMENT=	BSD Installer mega-package

LICENSE=	BSD3CLAUSE

RUN_DEPENDS=	cpdup:sysutils/cpdup

USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
GH_TAGNAME=	7bbfe1a

post-install:
	${MV} ${STAGEDIR}${PREFIX}/bin/lua ${STAGEDIR}${PREFIX}/bin/lua50
	${MV} ${STAGEDIR}${PREFIX}/bin/luac ${STAGEDIR}${PREFIX}/bin/lua50c
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libdfui.so
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/liblua50.so
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/liblualib50.so
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/dfuife_curses
	${RM} ${STAGEDIR}${PREFIX}/lib/*.a
	${RM} ${STAGEDIR}/lib/libaura.*

.include <bsd.port.mk>

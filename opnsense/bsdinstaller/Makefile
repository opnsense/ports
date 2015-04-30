# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	bsdinstaller
PORTVERSION=	2.2
PORTREVISION=	0
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	BSD Installer mega-package

MAKE_JOBS_UNSAFE=yes

DFUIBE_LUA_DIR=	${PREFIX}/share/dfuibe_lua
CFLAGS+=        -fPIC

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

do-install:
	${INSTALL_LIB} ${WRKSRC}/lib/libdfui/libdfui.so.4 ${STAGEDIR}${PREFIX}/lib
	${LN} -sf ${PREFIX}/lib/libdfui.so.4 ${STAGEDIR}${PREFIX}/lib/libdfui.so
	${INSTALL_PROGRAM} ${WRKSRC}/frontends/ncurses/dfuife_curses ${STAGEDIR}${PREFIX}/sbin
	${INSTALL_LIB} ${WRKSRC}/platform/lua/lib/liblua50.so ${STAGEDIR}${PREFIX}/lib
	${INSTALL_LIB} ${WRKSRC}/platform/lua/lib/liblualib50.so ${STAGEDIR}${PREFIX}/lib
	${INSTALL_PROGRAM} ${WRKSRC}/platform/lua/bin/lua ${STAGEDIR}${PREFIX}/bin/lua50
	${INSTALL_PROGRAM} ${WRKSRC}/platform/lua/bin/luac ${STAGEDIR}${PREFIX}/bin/lua50c
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/lua/5.0
	${MKDIR} ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/compat-5.1/compat-5.1.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_SCRIPT} ${WRKSRC}/lib/lua/compat-5.1/lua50c51.sh ${STAGEDIR}${PREFIX}/bin/lua50c51
	${INSTALL_LIB} ${WRKSRC}/lib/lua/posix/lposix.so ${STAGEDIR}${PREFIX}/lib/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/posix/posix.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_LIB} ${WRKSRC}/lib/lua/pty/lpty.so ${STAGEDIR}${PREFIX}/lib/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/pty/pty.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/filename/filename.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/app/app.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_LIB} ${WRKSRC}/lib/lua/dfui/ldfui.so ${STAGEDIR}${PREFIX}/lib/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/dfui/dfui.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_LIB} ${WRKSRC}/lib/lua/luasocket/lsocket.so ${STAGEDIR}${PREFIX}/lib/lua/5.0
	${INSTALL_LIB} ${WRKSRC}/lib/lua/luasocket/lmime.so ${STAGEDIR}${PREFIX}/lib/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/luasocket/lua/*.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/transceiver/transceiver.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_LIB} ${WRKSRC}/lib/lua/lcurses/lcurses.so ${STAGEDIR}${PREFIX}/lib/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/lcurses/curses.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${MKDIR} ${STAGEDIR}${DFUIBE_LUA_DIR}/lib
	${MKDIR} ${STAGEDIR}${DFUIBE_LUA_DIR}/conf
	${MKDIR} ${STAGEDIR}${DFUIBE_LUA_DIR}/easy_install
	${MKDIR} ${STAGEDIR}${DFUIBE_LUA_DIR}/pit
	${MKDIR} ${STAGEDIR}${DFUIBE_LUA_DIR}/install
	${MKDIR} ${STAGEDIR}${DFUIBE_LUA_DIR}/configure/menu
	${MKDIR} ${STAGEDIR}${DFUIBE_LUA_DIR}/upgrade
	${MKDIR} ${STAGEDIR}${DFUIBE_LUA_DIR}/netboot
	${INSTALL_DATA} ${WRKSRC}/backend/lua/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}
	${INSTALL_DATA} ${WRKSRC}/backend/lua/lib/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/lib
	${INSTALL_DATA} ${WRKSRC}/backend/lua/conf/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/conf
	${INSTALL_DATA} ${WRKSRC}/backend/lua/easy_install/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/easy_install
	${INSTALL_DATA} ${WRKSRC}/backend/lua/pit/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/pit
	${INSTALL_DATA} ${WRKSRC}/backend/lua/install/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/install
	${INSTALL_DATA} ${WRKSRC}/backend/lua/configure/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/configure
	${INSTALL_DATA} ${WRKSRC}/backend/lua/configure/menu/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/configure/menu
	${INSTALL_DATA} ${WRKSRC}/backend/lua/upgrade/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/upgrade
	${INSTALL_DATA} ${WRKSRC}/backend/lua/netboot/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/netboot
	${MKDIR} ${STAGEDIR}/usr/local/installer
	${INSTALL_SCRIPT} ${WRKSRC}/extra/* ${STAGEDIR}/usr/local/installer

.include <bsd.port.mk>

PORTNAME=	bsdinstaller
PORTVERSION=	2.0
PORTREVISION=	1
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@lastsummer.de
COMMENT=	BSD Installer mega-package

MAKE_JOBS_UNSAFE=yes

OPTIONS_SUB=	yes

OPTIONS_DEFINE=	CGI CURSES C_BACKEND LUA_BACKEND
OPTIONS_DEFAULT=CGI CURSES LUA_BACKEND

DFUIBE_LUA_DIR=	${PREFIX}/share/dfuibe_lua
CFLAGS+=        -fPIC

PLIST_SUB=	DISTNAME="${DISTNAME}"

do-extract:
	cp -r ${FILESDIR} ${WRKSRC}

do-install:
	${MKDIR} -p ${STAGEDIR}${PREFIX}/include/aura
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libaura/libaura.a ${STAGEDIR}${PREFIX}/lib/
	${INSTALL_PROGRAM} -o root -g wheel -m 444 ${WRKSRC}/lib/libaura/libaura.so.3 ${STAGEDIR}${PREFIX}/lib/
	${LN} -sf ${STAGEDIR}${PREFIX}/lib/libaura.so.3 ${STAGEDIR}${PREFIX}/lib/libaura.so
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libaura/buffer.h ${STAGEDIR}${PREFIX}/include/aura/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libaura/dict.h ${STAGEDIR}${PREFIX}/include/aura/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libaura/popen.h ${STAGEDIR}${PREFIX}/include/aura/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libaura/fspred.h ${STAGEDIR}${PREFIX}/include/aura/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libaura/mem.h ${STAGEDIR}${PREFIX}/include/aura/
	${MKDIR} -p ${STAGEDIR}${PREFIX}/include/dfui
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libdfui/libdfui.a ${STAGEDIR}${PREFIX}/lib/
	${INSTALL_PROGRAM} -o root -g wheel -m 444 ${WRKSRC}/lib/libdfui/libdfui.so.4 ${STAGEDIR}${PREFIX}/lib/
	${LN} -sf ${PREFIX}/lib/libdfui.so.4 ${STAGEDIR}${PREFIX}/lib/libdfui.so
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libdfui/dfui.h ${STAGEDIR}${PREFIX}/include/dfui/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libdfui/dump.h ${STAGEDIR}${PREFIX}/include/dfui/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libdfui/lang.h ${STAGEDIR}${PREFIX}/include/dfui/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libdfui/system.h ${STAGEDIR}${PREFIX}/include/dfui/
	${MKDIR} -p ${STAGEDIR}${PREFIX}/include/installer
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libinstaller/libinstaller.a ${STAGEDIR}${PREFIX}/lib/
	${INSTALL_PROGRAM} -o root -g wheel -m 444 ${WRKSRC}/lib/libinstaller/libinstaller.so.5 ${STAGEDIR}${PREFIX}/lib/
	${LN} -sf ${PREFIX}/lib/libinstaller.so.5 ${STAGEDIR}${PREFIX}/lib/libinstaller.so
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libinstaller/commands.h ${STAGEDIR}${PREFIX}/include/installer/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libinstaller/confed.h ${STAGEDIR}${PREFIX}/include/installer/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libinstaller/diskutil.h ${STAGEDIR}${PREFIX}/include/installer/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libinstaller/functions.h ${STAGEDIR}${PREFIX}/include/installer/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libinstaller/package.h ${STAGEDIR}${PREFIX}/include/installer/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/libinstaller/uiutil.h ${STAGEDIR}${PREFIX}/include/installer/
	${MKDIR} -p ${STAGEDIR}${PREFIX}/share/dfuife_curses
	${INSTALL_PROGRAM} -o root -g wheel ${WRKSRC}/frontends/ncurses/dfuife_curses ${STAGEDIR}${PREFIX}/sbin/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/frontends/ncurses/fred.txt ${STAGEDIR}${PREFIX}/share/dfuife_curses/
	${INSTALL_PROGRAM} -s -o root -g wheel -m 555 ${WRKSRC}/backend/installer/dfuibe_installer ${STAGEDIR}${PREFIX}/sbin
	${MKDIR} -p ${PREFIX}/share/dfuibe_installer
	${INSTALL_DATA} -o root -g wheel -m 555 ${WRKSRC}/backend/installer/conf/cmdnames.conf ${STAGEDIR}${PREFIX}/share/dfuibe_installer
	${INSTALL_PROGRAM} -o root -g wheel -m 444 ${WRKSRC}/platform/lua/lib/liblua50.so ${STAGEDIR}${PREFIX}/lib/
	${INSTALL_PROGRAM} -o root -g wheel -m 444 ${WRKSRC}/platform/lua/lib/liblualib50.so ${STAGEDIR}${PREFIX}/lib/
	${INSTALL_PROGRAM} -o root -g wheel -m 555 ${WRKSRC}/platform/lua/bin/lua ${STAGEDIR}${PREFIX}/bin/lua50
	${INSTALL_PROGRAM} -o root -g wheel -m 555 ${WRKSRC}/platform/lua/bin/luac ${STAGEDIR}${PREFIX}/bin/lua50c
	${MKDIR} -p ${STAGEDIR}${PREFIX}/lib/lua/5.0
	${MKDIR} -p ${STAGEDIR}${PREFIX}/lib/lua/${DISTNAME}
	${MKDIR} -p ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/compat-5.1/compat-5.1.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/compat-5.1/compat-5.1.c ${STAGEDIR}${PREFIX}/lib/lua/${DISTNAME}
	${INSTALL_DATA} ${WRKSRC}/lib/lua/compat-5.1/compat-5.1.h ${STAGEDIR}${PREFIX}/lib/lua/${DISTNAME}
	${INSTALL_SCRIPT} ${WRKSRC}/lib/lua/compat-5.1/lua50c51.sh ${STAGEDIR}${PREFIX}/bin/lua50c51
	${INSTALL_DATA} ${WRKSRC}/lib/lua/posix/lposix.so ${STAGEDIR}${PREFIX}/lib/lua/5.0/
	${INSTALL_DATA} ${WRKSRC}/lib/lua/posix/posix.lua ${STAGEDIR}${PREFIX}/share/lua/5.0/
	${INSTALL_DATA} ${WRKSRC}/lib/lua/pty/lpty.so ${STAGEDIR}${PREFIX}/lib/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/pty/pty.lua ${STAGEDIR}${PREFIX}/share/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/filename/filename.lua ${STAGEDIR}${PREFIX}/share/lua/5.0/filename.lua
	${INSTALL_DATA} ${WRKSRC}/lib/lua/app/app.lua ${STAGEDIR}${PREFIX}/share/lua/5.0/app.lua
	${INSTALL_PROGRAM} -o root -g wheel -m 444 ${WRKSRC}/lib/lua/dfui/ldfui.so ${STAGEDIR}${PREFIX}/lib/lua/5.0/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/lib/lua/dfui/dfui.lua ${STAGEDIR}${PREFIX}/share/lua/5.0/
	${INSTALL_PROGRAM} ${WRKSRC}/lib/lua/luasocket/lsocket.so ${STAGEDIR}${PREFIX}/lib/lua/5.0/
	${INSTALL_PROGRAM} ${WRKSRC}/lib/lua/luasocket/lmime.so ${STAGEDIR}${PREFIX}/lib/lua/5.0/
	${INSTALL_DATA} ${WRKSRC}/lib/lua/luasocket/lua/*.lua ${STAGEDIR}${PREFIX}/share/lua/5.0/
	${INSTALL_DATA} ${WRKSRC}/lib/lua/transceiver/transceiver.lua ${STAGEDIR}${PREFIX}/share/lua/5.0/
	${INSTALL_PROGRAM} ${WRKSRC}/lib/lua/lcurses/lcurses.so ${STAGEDIR}${PREFIX}/lib/lua/5.0
	${INSTALL_DATA} ${WRKSRC}/lib/lua/lcurses/curses.lua ${STAGEDIR}${PREFIX}/share/lua/5.0/
	${MKDIR} -p ${STAGEDIR}${DFUIBE_LUA_DIR}
	${MKDIR} -p ${STAGEDIR}${DFUIBE_LUA_DIR}/lib
	${MKDIR} -p ${STAGEDIR}${DFUIBE_LUA_DIR}/conf
	${MKDIR} -p ${STAGEDIR}${DFUIBE_LUA_DIR}/easy_install
	${MKDIR} -p ${STAGEDIR}${DFUIBE_LUA_DIR}/pit
	${MKDIR} -p ${STAGEDIR}${DFUIBE_LUA_DIR}/install
	${MKDIR} -p ${STAGEDIR}${DFUIBE_LUA_DIR}/configure
	${MKDIR} -p ${STAGEDIR}${DFUIBE_LUA_DIR}/configure/menu
	${MKDIR} -p ${STAGEDIR}${DFUIBE_LUA_DIR}/upgrade
	${MKDIR} -p ${STAGEDIR}${DFUIBE_LUA_DIR}/netboot
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/backend/lua/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/backend/lua/lib/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/lib/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/backend/lua/conf/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/conf/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/backend/lua/easy_install/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/easy_install/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/backend/lua/pit/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/pit/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/backend/lua/install/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/install/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/backend/lua/configure/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/configure/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/backend/lua/configure/menu/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/configure/menu/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/backend/lua/upgrade/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/upgrade/
	${INSTALL_DATA} -o root -g wheel -m 444 ${WRKSRC}/backend/lua/netboot/*.lua ${STAGEDIR}${DFUIBE_LUA_DIR}/netboot/
	echo ${DISTNAME}

.include <bsd.port.mk>

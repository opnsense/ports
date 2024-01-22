PORTNAME=	netmap-bridge
SRCVERSION=	yes
CATEGORIES=	sysutils
DISTFILES=

MAINTAINER=	stephan.de.wit@deciso.com
COMMENT=	Bridge two network interfaces in netmap mode

LICENSE=	BSD

ALL_TARGET=	bridge
MANDIRS=	${PREFIX}/man/man8

.include <bsd.port.options.mk>

pre-extract:
.if !exists(${SRC_BASE}/tools/tools/netmap/Makefile)
IGNORE=	requires kernel source files in ${SRC_BASE}
.endif

do-extract:
	${MKDIR} ${WRKSRC}
	${CP} ${SRC_BASE}/tools/tools/netmap/Makefile ${WRKSRC}
	${CP} ${SRC_BASE}/tools/tools/netmap/bridge.8 ${WRKSRC}
	${CP} ${SRC_BASE}/tools/tools/netmap/bridge.c ${WRKSRC}

pre-install:
	${CP} ${WRKSRC}/bridge.8 ${STAGEDIR}${PREFIX}/share/man/man8/netmap-bridge.8
	${MV} ${WRKSRC}/bridge ${WRKSRC}/netmap-bridge

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/sbin/

.include <bsd.port.mk>

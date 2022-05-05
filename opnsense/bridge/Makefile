PORTNAME=	bridge
PORTVERSION=	1.0
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
	${CP} ${SRC_BASE}/tools/tools/netmap/Makefile ${FILESDIR}
	${CP} ${SRC_BASE}/tools/tools/netmap/bridge.8 ${FILESDIR}
	${CP} ${SRC_BASE}/tools/tools/netmap/bridge.c ${FILESDIR}
	${CP} -r ${FILESDIR} ${WRKSRC}

pre-install:
	${CP} ${WRKSRC}/bridge.8 ${STAGEDIR}${PREFIX}/man/man8/

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/sbin/

.include <bsd.port.mk>

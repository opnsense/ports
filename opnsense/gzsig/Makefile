PORTNAME=	gzsig
PORTVERSION=	0.0.2
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER?=	geekgod@geekgod.com
COMMENT?=	reinits ata channel 0

WHERE=		sbin
PLIST_FILES=    ${WHERE}/${PORTNAME}

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	make -C ${FILESDIR}

do-install:
	${INSTALL_PROGRAM} ${FILESDIR}/${PORTNAME} ${STAGEDIR}${PREFIX}/${WHERE}

do-clean:
	make -C ${FILESDIR} clean
	rm -rf ${WRKDIR}

.include <bsd.port.mk>

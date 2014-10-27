PORTNAME=	filterdns
PORTVERSION=	0.1
CATEGORIES?=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER?=	eri@pfsense.org
COMMENT?=	filterdns

WHERE=		sbin
PLIST_FILES=    ${WHERE}/${PORTNAME}

do-clean:
	make -C ${FILESDIR} clean
	rm -rf ${WRKDIR}

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	make -C ${FILESDIR}

do-install:
	${INSTALL_PROGRAM} files/${PORTNAME} ${STAGEDIR}${PREFIX}/${WHERE}/

.include <bsd.port.mk>

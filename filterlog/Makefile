PORTNAME=	filterlog
PORTVERSION=	0.1
CATEGORIES?=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER?=	eri@pfsense.org
COMMENT?=	filterlog

WHERE=		sbin
PLIST_FILES=    ${WHERE}/${PORTNAME}

pre-clean:
	cd files && make clean

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	cd files && make

do-install:
	${INSTALL_PROGRAM} files/${PORTNAME} ${STAGEDIR}${PREFIX}/${WHERE}/

.include <bsd.port.mk>

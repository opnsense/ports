PORTNAME=	cpustats
PORTVERSION=	0.1
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	Gather system statistics

USE_HARDENING=	safestack

WHERE=		sbin
PLIST_FILES=    ${WHERE}/${PORTNAME}

.include <bsd.port.pre.mk>

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${LDFLAGS} ${CFLAGS} -o ${WRKSRC}/${PORTNAME} ${FILESDIR}/${PORTNAME}.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/${WHERE}/

.include <bsd.port.post.mk>

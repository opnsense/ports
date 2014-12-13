PORTNAME=	3gstat
PORTVERSION=	20091215
PORTREVISION=	1
CATEGORIES=	comms
MASTER_SITES=	# none
DISTFILES=	# none

MAINTAINER=	franco@opnsense.org
COMMENT=	3G status

NO_WRKSUBDIR=	yes
PLIST_FILES=	bin/3gstat

do-fetch:

do-extract:
	${MKDIR} ${WRKDIR}
	${LN} -sf ${FILESDIR}/${PORTNAME}.c ${FILESDIR}/Makefile ${WRKDIR}

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/bin

.include <bsd.port.mk>

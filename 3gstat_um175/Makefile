# Ports collection makefile for:  3gstat
# Date created:			  Tue Dec 15, 2009
# Whom:				  Andrew Thompson <thompsa@freebsd.org>
#
# $FreeBSD$
#

PORTNAME=	3gstat
PORTVERSION=	20091215
CATEGORIES=	comms
MASTER_SITES=	# none
DISTFILES=	# none

MAINTAINER=	thompsa@FreeBSD.org
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

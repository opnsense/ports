# New ports collection makefile for:	voucher
# Date created:				Tue Feb 18 11:17:13 CET 2003
# Whom:					eri@pfsense.org
#

PORTNAME=	voucher
PORTVERSION=	0.1
PORTREVISION?=	0
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty
#NO_STAGE=	yes

MAINTAINER?=	eri@pfsense.org
COMMENT?=	voucher support

WHERE=		bin
PLIST_FILES=    ${WHERE}/${PORTNAME}

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -o ${WRKSRC}/${PORTNAME} -l ssl  -l crypto  ${FILESDIR}/${PORTNAME}.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/${WHERE}/

        

.include <bsd.port.mk>

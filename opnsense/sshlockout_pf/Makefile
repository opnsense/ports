PORTNAME=	sshlockout_pf
PORTVERSION=	0.0.2
PORTREVISION=	2
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@lastsummer.de
COMMENT=	Automatically block IPs with failed SSH logins using pf(4)

PLIST_FILES=    sbin/sshlockout_pf

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -Wall -lpthread -o ${WRKSRC}/${PORTNAME} \
	    ${FILESDIR}/sshlockout_pf.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} \
		${STAGEDIR}${PREFIX}/sbin/

.include <bsd.port.mk>

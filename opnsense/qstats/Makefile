PORTNAME=	qstats
PORTVERSION=	0.1
PORTREVISION=	1
CATEGORIES?=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER?=	franco@lastsummer.de
COMMENT?=	read dhpcd.lease file and add it to hosts file

CFLAGS+=	-lsbuf
PLIST_FILES=    sbin/qstats

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -o ${WRKSRC}/${PORTNAME} ${FILESDIR}/qstats.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/sbin/

.include <bsd.port.mk>

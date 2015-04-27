PORTNAME=	dhcpleases
PORTVERSION=	0.2
PORTREVISION=	0
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	read dhpcd.lease file and add it to hosts file

CONFLICTS=	dhcpleases6-*

WHERE=		sbin

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -o ${WRKSRC}/dhcpleases ${FILESDIR}/dhcpleases.c
	${CC} ${CFLAGS} -o ${WRKSRC}/dhcpleases6 ${FILESDIR}/dhcpleases6.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/dhcpleases ${STAGEDIR}${PREFIX}/sbin
	${INSTALL_PROGRAM} ${WRKSRC}/dhcpleases6 ${STAGEDIR}${PREFIX}/sbin

.include <bsd.port.mk>

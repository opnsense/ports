PORTNAME=	dhcpleases
PORTVERSION=	0.2
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	Read dhpcd.lease file and add it to hosts file

LICENSE=	BSD2CLAUSE

USE_HARDENING=	safestack

.include <bsd.port.pre.mk>

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${LDFLAGS} ${CFLAGS} -o ${WRKSRC}/dhcpleases ${FILESDIR}/dhcpleases.c
	${CC} ${LDFLAGS} ${CFLAGS} -o ${WRKSRC}/dhcpleases6 ${FILESDIR}/dhcpleases6.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/dhcpleases ${STAGEDIR}${PREFIX}/sbin
	${INSTALL_PROGRAM} ${WRKSRC}/dhcpleases6 ${STAGEDIR}${PREFIX}/sbin

.include <bsd.port.post.mk>

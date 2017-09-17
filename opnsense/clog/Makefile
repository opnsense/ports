PORTNAME=	clog
PORTVERSION=	1.0.1
PORTREVISION=	3
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	Circular log support for FreeBSD syslogd

LICENSE=	BSD2CLAUSE

USE_HARDENING=	safestack

# -O2 is dangerous for clog! It breaks on i386 -O works.
CFLAGS+=	-O

.include <bsd.port.pre.mk>

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${LDFLAGS} ${CFLAGS} -o ${WRKSRC}/clog ${FILESDIR}/clog.c
	cp ${FILESDIR}/clog.8 ${WRKSRC}/clog.8
	gzip ${WRKSRC}/clog.8

do-install:
	${INSTALL_MAN} ${WRKSRC}/clog.8.gz ${STAGEDIR}${PREFIX}/man/man8
	${INSTALL_DATA} ${FILESDIR}/clog.h ${STAGEDIR}${PREFIX}/include
	${INSTALL_PROGRAM} ${WRKSRC}/clog ${STAGEDIR}${PREFIX}/sbin

.include <bsd.port.post.mk>

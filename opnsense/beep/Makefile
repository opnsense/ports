PORTNAME=	beep
PORTVERSION=	1.0
PORTREVISION=	1
CATEGORIES=	audio
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	Beeps a certain duration and pitch out of the PC Speaker

LICENSE=	BSD4CLAUSE

ONLY_FOR_ARCHS=	i386 amd64 pc98

USE_HARDENING=	pie relro safestack

PLIST_FILES=	bin/beep man/man1/beep.1.gz

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -o ${WRKSRC}/beep ${FILESDIR}/beep.c
	cp ${FILESDIR}/beep.1 ${WRKSRC}
	gzip ${WRKSRC}/beep.1

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/beep ${STAGEDIR}${PREFIX}/bin/
	${INSTALL_MAN} ${WRKSRC}/beep.1.gz ${STAGEDIR}${PREFIX}/man/man1

.include <bsd.port.mk>

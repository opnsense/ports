# $FreeBSD$

PORTNAME=	bsdinstall
PORTVERSION=	11.2
CATEGORIES=	sysutils
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense version of FreeBSD bsdinstall

LICENSE=	BSD3CLAUSE

USE_HARDENING=	safestack

MAKE_ENV=	SRCTOP=${WRKSRC} LIBEXECDIR=${PREFIX}/libexec \
		MANDIR=${PREFIX}/man/man BINDIR=${PREFIX}/sbin
LDFLAGS=	-larchive -ldpv -lfetch -lfigpar -lgeom \
		-lncursesw -ldialog -lm -lutil

do-extract:
	${CP} -r ${FILESDIR}/src ${WRKSRC}
	@${REINPLACE_CMD} "s,/usr/sbin/sade,${PREFIX}/sbin/sade,g" \
	    ${WRKSRC}/usr.sbin/bsdinstall/partedit/Makefile

pre-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/libexec/bsdinstall

.include <bsd.port.mk>

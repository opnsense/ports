PORTNAME=	ifinfo
PORTVERSION=	13.0
PORTREVISION=	1
CATEGORIES=	sysutils
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	Interface statistics reader

LICENSE=	MIT

MAKE_ENV=	BINDIR=${PREFIX}/sbin

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

.include <bsd.port.mk>

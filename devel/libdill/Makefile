PORTNAME=	libdill
DISTVERSION=	2.14
PORTREVISION=	1
CATEGORIES=	devel

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Structured concurrency library in C
WWW=		https://github.com/sustrik/libdill

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYING

BROKEN_i386=	error: this directive must appear between .cfi_startproc and .cfi_endproc directives

USES=		autoreconf gmake libtool
GNU_CONFIGURE=	yes
GNU_CONFIGURE_MANPREFIX=	${PREFIX}/share
CONFIGURE_ARGS=	--disable-static
USE_GITHUB=	yes
GH_ACCOUNT=	sustrik
USE_LDCONFIG=	yes

.include <bsd.port.mk>

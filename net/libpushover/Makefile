# $FreeBSD$

PORTNAME=	libpushover
DISTVERSION=	g2020061601
CATEGORIES=	net

MAINTAINER=	shawn.webb@hardenedbsd.org
COMMENT=	Native C API for libpushover

USES=		uidfix

LIB_DEPENDS=	libcurl.so:ftp/curl

WRKSRC=	${WRKDIR}/libpushover

USE_GITLAB=	gitea
GL_SITE=	https://git-01.md.hardenedbsd.org
GL_ACCOUNT=	HardenedBSD
GL_PROJECT=	libpushover
GL_COMMIT=	7041b121ddd8c774a72e944ab68c97a04dfc68a1

.include <bsd.port.mk>


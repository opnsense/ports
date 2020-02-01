# $FreeBSD$

PORTNAME=	iichid-kmod
MAINTAINER=	shawn.webb@hardenedbsd.org
DISTVERSION=	g2020020300

CATEGORIES=	sysutils
COMMENT=	i2c HID driver

USES=		kmod uidfix
USE_GITLAB=	gitea
GL_SITE=	https://git-01.md.hardenedbsd.org
GL_ACCOUNT=	shawn.webb
GL_PROJECT=	iichid
GL_COMMIT=	79299fac1a2816eb21cac71d504a2d79665d015b

WRKSRC=		${WRKDIR}/iichid

pre-build:
	(cd ${WRKSRC}; make depend)

.include <bsd.port.mk>

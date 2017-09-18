# $FreeBSD$

PORTREVISION=	1

PKGNAMESUFFIX=	-kmod
MASTERDIR=	${.CURDIR}/../secadm

COMMENT=	HardenedBSD Security Administration - Kernel module

USES=		kmod
KMOD=		yes

USE_HARDENING=	pie:off relro:off

pre-build:
	(cd ${WRKSRC}; make depend)

PLIST=	${.CURDIR}/pkg-plist

.include "${MASTERDIR}/Makefile"

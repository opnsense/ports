# Created by: Alex Dupre <ale@FreeBSD.org>
# $FreeBSD$

CATEGORIES=	graphics
PORTREVISION=	1

MASTERDIR=	${.CURDIR}/../../lang/php70

PKGNAMESUFFIX=	-gd

USE_HARDENING=	pie:off

TEST_TARGET=	test

.include "${MASTERDIR}/Makefile"

LIB_DEPENDS+=	libgd.so:graphics/gd

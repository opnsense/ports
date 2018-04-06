# Created by: Alonso Cardenas <acm@FreeBSD.org>
# $FreeBSD: head/sysutils/bareos-client-static/Makefile 445197 2017-07-07 02:19:21Z acm $

PORTNAME=	bareos
PORTREVISION=	0
PKGNAMESUFFIX=	-client-static

COMMENT=	Backup archiving recovery open sourced (static client)

PLIST=		${.CURDIR}/pkg-plist
MASTERDIR=	${.CURDIR}/../bareos-server

PLIST_FILES=	sbin/bareos-fd-static \
		sbin/bconsole-static

OPTIONS_DEFINE=	NLS LMDB
LMDB_DESC=	Enable build of LMDB support

CONFIGURE_ARGS+=	--enable-client-only \
			--enable-static-fd \
			--enable-static-cons \
			--disable-libtool \
			--disable-build-dird \
			--disable-build-stored \
			--with-jansson=${LOCALBASE}

BROKEN_aarch64=	Fails to link: missing sbrk

.include "${MASTERDIR}/Makefile"

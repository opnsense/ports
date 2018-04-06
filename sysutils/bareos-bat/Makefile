# Created by: Alonso Cardenas Marquez <acm@FreeBSD.org>
# $FreeBSD: head/sysutils/bareos-bat/Makefile 426215 2016-11-16 07:11:54Z acm $

PORTNAME=	bareos
PKGNAMESUFFIX=	-bat
PORTREVISION=	0

COMMENT=	Backup archiving recovery open sourced (GUI)

LIB_DEPENDS+=	libqwt.so:x11-toolkits/qwt5 \
		libbareos.so:sysutils/bareos-client

CONFLICTS=	bacula*-bat-*

USES=		pkgconfig desktop-file-utils
USE_QT4=	qmake_build uic_build moc_build rcc_build
WITH_BAT=	yes

PLIST=		${.CURDIR}/pkg-plist
MAKE_ENV+=	MAKEOBJDIRPREFIX=/

MASTERDIR=	${.CURDIR}/../bareos-server

CONFIGURE_ARGS+=	--enable-bat \
			--with-qwt=${LOCALBASE}/lib \
			--disable-build-dird \
			--disable-build-stored \
			--enable-client-only

.include "${MASTERDIR}/Makefile"

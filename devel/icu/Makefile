PORTNAME=	icu
DISTVERSION=	76_1
PORTREVISION?=	0 # keep for icu-lx
PORTEPOCH?=	1
CATEGORIES?=	devel
MASTER_SITES=	https://github.com/unicode-org/${PORTNAME}/releases/download/release-${DISTVERSION:S/rc/-&/:S/_/-/g}/
DISTNAME=	icu4c-${DISTVERSION}-src

MAINTAINER=	office@FreeBSD.org
COMMENT?=	International Components for Unicode (from IBM)
WWW=		https://icu.unicode.org/ \
		https://github.com/unicode-org/icu

LICENSE=	ICU
LICENSE_NAME=	ICU license
LICENSE_FILE=	${WRKSRC}/../LICENSE
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

USES+=		compiler:c++11-lib cpe gmake pathfix python:build tar:tgz

GNU_CONFIGURE=	yes
CONFIGURE_ARGS?=--disable-layoutex
CONFIGURE_ARGS+=--with-data-packaging=archive \
		--disable-renaming \
		--disable-samples \
		--enable-static
CPPFLAGS+=	-DICU_NO_USER_DATA_OVERRIDE
MAKE_ARGS=	VERBOSE=1
TEST_TARGET=	check
CPE_VENDOR=	${PORTNAME}-project
CPE_PRODUCT=	international_components_for_unicode
USE_LDCONFIG=	yes
WRKSRC=		${WRKDIR}/icu/source

ICUMAJOR=	${PORTVERSION:C/\..*//}
PLIST_SUB+=	ICUMAJOR=${ICUMAJOR} ICUVER=${PORTVERSION:C/r.?/1/}

.if !defined(PKGNAMESUFFIX)
post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/g* \
		${STAGEDIR}${PREFIX}/bin/*conv \
		${STAGEDIR}${PREFIX}/bin/icuexportdata \
		${STAGEDIR}${PREFIX}/bin/icuinfo \
		${STAGEDIR}${PREFIX}/bin/derb \
		${STAGEDIR}${PREFIX}/bin/pkgdata
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/*
# Filename varies by endianness: icudt<major>b.dat vs. icudt<major>l.dat
	@(cd ${STAGEDIR}${PREFIX} && ${ECHO_CMD} \
		${DATADIR_REL}/${PORTVERSION:C/r.?/1/}/icudt*.dat >>${TMPPLIST})
.endif # !defined(PKGNAMESUFFIX)

.include <bsd.port.mk>

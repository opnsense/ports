# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	em
PORTVERSION=	7.6.2
CATEGORIES=	net
MASTER_SITES=	https://downloadmirror.intel.com/${MASTER_SITE_SUBDIR}/ \
		http://downloadmirror.intel.com/${MASTER_SITE_SUBDIR}/
MASTER_SITE_SUBDIR=	17509/eng
PKGNAMEPREFIX=	intel-
PKGNAMESUFFIX=	-kmod

MAINTAINER=	franco@opnsense.org
COMMENT=	Gigabit FreeBSD Base Drivers for Intel(R) Ethernet

LICENSE=	BSD2CLAUSE

OPTIONS_DEFINE=	NETMAP

USES=		kmod
WRKSRC_SUBDIR=	src

SUB_FILES=	pkg-message
SUB_LIST=	PORTNAME=${PORTNAME}
MANPAGENAME?=	${PORTNAME}
PLIST_FILES=	${KMODDIR}/if_${PORTNAME}_updated.ko \
		man/man4/${MANPAGENAME}.4.gz

NETMAP_DESC=	Native netmap(4) build (use with care)
NETMAP_CFLAGS=	-DDEV_NETMAP=1 -Dem_rxbuffer=em_buffer -Dem_txbuffer=em_buffer
NETMAP_EXTRA_PATCHES=    ${PATCHDIR}/extra-native-netmap.patch

do-install:
	${INSTALL_KLD} ${WRKSRC}/if_${PORTNAME}.ko ${STAGEDIR}${KMODDIR}/if_${PORTNAME}_updated.ko
	${INSTALL_MAN} ${WRKSRC}/${PORTNAME}.4 ${STAGEDIR}${MAN4PREFIX}/man/man4/

.include <bsd.port.mk>

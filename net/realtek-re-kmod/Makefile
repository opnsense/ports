# Created by: Alex Dupre <ale@FreeBSD.org>

PORTNAME=	re
DISTVERSIONPREFIX=	v
PORTVERSION=	196.04
CATEGORIES=	net
MASTER_SITES=	LOCAL/ale
PKGNAMEPREFIX=	realtek-
PKGNAMESUFFIX=	-kmod
DISTNAME=	rtl_bsd_drv_${DISTVERSIONPREFIX}${PORTVERSION}

MAINTAINER=	ale@FreeBSD.org
COMMENT=	Kernel driver for Realtek PCIe Ethernet Controllers

LICENSE=	BSD4CLAUSE

USES=		kmod tar:tgz uidfix

PLIST_FILES=	${KMODDIR}/if_re.ko

.include <bsd.port.mk>

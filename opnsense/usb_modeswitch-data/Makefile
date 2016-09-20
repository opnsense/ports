# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	usb_modeswitch-data
PORTVERSION=	20160803
CATEGORIES=	sysutils
MASTER_SITES=	http://www.draisberghof.de/usb_modeswitch/
DISTNAME=	${PORTNAME:S|_|-|}-${PORTVERSION}

MAINTAINER=	franco@opnsense.org
COMMENT=	Data files for Mode-Switching USB Devices

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		tar:bzip2
NO_BUILD=	yes

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/share/usb_modeswitch
	${INSTALL_DATA} ${WRKSRC}/usb_modeswitch.d/* \
	    ${STAGEDIR}${PREFIX}/share/usb_modeswitch

.include <bsd.port.mk>

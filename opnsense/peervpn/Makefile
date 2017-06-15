# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	peervpn
DISTVERSION=	0-044
CATEGORIES=	security net
MASTER_SITES=	https://peervpn.net/files/

MAINTAINER=	franco@opnsense.org
COMMENT?=	Peer-to-peer virtual ethernet network daemon

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/license.txt

USES=		ssl

USE_HARDENING=	pie relro safestack

.include <bsd.port.mk>

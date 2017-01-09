# Created by: asami
# $FreeBSD$

PORTNAME=	igmpproxy
PORTVERSION=	0.1
PORTREVISION=	2
PORTEPOCH=	1
CATEGORIES=	net
MASTER_SITES=	SF

MAINTAINER=	melifaro@ipfw.ru
COMMENT=	Multicast forwarding IGMP proxy

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/COPYING

USE_RC_SUBR=	igmpproxy
USES=		gmake
GNU_CONFIGURE=	yes

OPTIONS_DEFINE=	VLANFIX

VLANFIX_DESC=	Experimental support for VLAN-based upstream interfaces
VLANFIX_EXTRA_PATCHES=	${FILESDIR}/extra-patch-src_ifvc.c \
			${FILESDIR}/extra-patch-src_igmpproxy.c \
			${FILESDIR}/extra-patch-src_igmpproxy.h

.include <bsd.port.mk>

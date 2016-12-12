# Created by: asami
# $FreeBSD$

PORTNAME=	igmpproxy
PORTVERSION=	0.1.devel
CATEGORIES=	net
GH_TUPLE=       pali:igmpproxy:d595329bcb55e936b9f8a2b0a719d07086fd2c5f
USE_GITHUB=     yes
MASTER_SITES=   GH

MAINTAINER=	melifaro@ipfw.ru
COMMENT=	Multicast forwarding IGMP proxy

HOMEPAGE=	https://github.com/pali/igmpproxy

USE_RC_SUBR=	igmpproxy
USES=		gmake
USE_AUTOTOOLS=  aclocal autoconf autoheader automake
AUTOMAKE_ARGS=  --add-missing

.include <bsd.port.mk>

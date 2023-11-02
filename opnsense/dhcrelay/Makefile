PORTNAME=	dhcrelay
PORTVERSION=	0.1
CATEGORIES=	net

MAINTAINER=	franco@opnsense.org
COMMENT=	OpenBSD dhcrelay daemons
WWW=		https://opnsense.org/

LICENSE=	BSD3CLAUSE

CONFLICTS_INSTALL=	isc-dhcp44-relay

MAKE_ENV=	BINDIR=${PREFIX}/sbin MANDIR=${PREFIX}/man/man

USE_GITHUB=	yes
GH_ACCOUNT=	${CATEGORIES:[1]}
GH_TAGNAME=	329f032

.include <bsd.port.mk>

# $FreeBSD$

PORTNAME=	dhcp6c
PORTREVISION=	2 # GH_TAGNAME
DISTVERSION=	20190419
DISTVERSIONPREFIX=v
CATEGORIES=	net

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense WIDE-DHCPv6 client

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/COPYRIGHT

CONFLICTS_INSTALL=	dhcp6

USE_HARDENING=	safestack

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
GH_TAGNAME=	8bb244c

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--sysconfdir=${LOCALBASE}/etc \
		--with-localdbdir=/var/db
USE_RC_SUBR=	dhcp6c

post-install:
	${INSTALL_DATA} ${WRKSRC}/dhcp6c.conf.sample ${STAGEDIR}${PREFIX}/etc

.include <bsd.port.mk>

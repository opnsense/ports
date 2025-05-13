PORTNAME=	dhcp6c
DISTVERSIONPREFIX=v
DISTVERSION=	20250513
CATEGORIES=	net

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense WIDE-DHCPv6 client
WWW=		https://github.com/opnsense/dhcp6c

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/COPYRIGHT

CONFLICTS_INSTALL=	dhcp6

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense

PLIST_FILES=	etc/dhcp6c.conf.sample \
		sbin/dhcp6c \
		share/man/man5/dhcp6c.conf.5.gz \
		share/man/man8/dhcp6c.8.gz

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--sysconfdir=${LOCALBASE}/etc --with-localdbdir=/var/db

USE_RC_SUBR=	dhcp6c

post-install:
	${INSTALL_DATA} ${WRKSRC}/dhcp6c.conf.sample ${STAGEDIR}${PREFIX}/etc

.include <bsd.port.mk>

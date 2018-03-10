# Created by: asami
# $FreeBSD$

PORTNAME=	igmpproxy
PORTVERSION=	0.2.1
PORTEPOCH=	1
CATEGORIES=	net

MAINTAINER=	franco@opnsense.org
COMMENT=	Multicast forwarding IGMP proxy

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/COPYING

USE_GITHUB=	yes
GH_ACCOUNT=	pali

USE_HARDENING=	safestack

USE_RC_SUBR=	igmpproxy
USES=		autoreconf
GNU_CONFIGURE=	yes

post-install:
	${INSTALL_DATA} ${WRKSRC}/igmpproxy.conf \
	    ${STAGEDIR}${PREFIX}/etc/igmpproxy.conf.sample

.include <bsd.port.mk>

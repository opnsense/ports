# Created by: asami
# $FreeBSD$

PORTNAME=	igmpproxy
PORTVERSION=	0.1.g20171030
PORTEPOCH=	1
CATEGORIES=	net

MAINTAINER=	franco@opnsense.org
COMMENT=	Multicast forwarding IGMP proxy

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/COPYING

USE_HARDENING=	safestack

USE_GITHUB=	yes
GH_ACCOUNT=	pali
GH_TAGNAME=	2872012

USE_RC_SUBR=	igmpproxy
USES=		autoreconf
GNU_CONFIGURE=	yes

post-install:
	${INSTALL_DATA} ${WRKSRC}/igmpproxy.conf \
	    ${STAGEDIR}${PREFIX}/etc/igmpproxy.conf.sample

.include <bsd.port.mk>

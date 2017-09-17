# Created by: Michael L. Hostbaek (mich@freebsdcluster.org)
# $FreeBSD$

PORTNAME=	apinger
PORTVERSION=	0.7
CATEGORIES=	net ipv6

MAINTAINER=	franco@opnsense.org
COMMENT=	IP device monitoring tool

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

GNU_CONFIGURE=	yes
USE_RC_SUBR=	apinger

MAKE_JOBS_UNSAFE=yes

OPTIONS_DEFINE=	IPV6

USES=		autoreconf bison

USE_HARDENING=	safestack

IPV6_CONFIGURE_ENABLE=	ipv6

post-install:
	${INSTALL_DATA} ${WRKSRC}/src/apinger.conf ${STAGEDIR}${PREFIX}/etc/apinger.conf.sample

.include <bsd.port.mk>

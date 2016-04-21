# Created by: Michael L. Hostbaek (mich@freebsdcluster.org)
# $FreeBSD$

PORTNAME=	apinger
PORTVERSION=	0.6.1
PORTREVISION=	6
CATEGORIES=	net ipv6

MAINTAINER=	franco@opnsense.org
COMMENT=	IP device monitoring tool

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
GH_PROJECT=	apinger
GH_TAGNAME=	5bd970b

LICENSE=	GPLv2

GNU_CONFIGURE=	yes
USE_RC_SUBR=	apinger
PORTDOCS=	AUTHORS NEWS README

MAKE_JOBS_UNSAFE=yes

OPTIONS_DEFINE=	IPV6 DOCS

USES=		autoreconf bison

IPV6_CONFIGURE_ENABLE=	ipv6

post-install:
	${INSTALL_DATA} ${WRKSRC}/src/apinger.conf ${STAGEDIR}${PREFIX}/etc/apinger.conf.sample
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README ${STAGEDIR}${DOCSDIR}/README
	${INSTALL_DATA} ${WRKSRC}/NEWS ${STAGEDIR}${DOCSDIR}/NEWS
	${INSTALL_DATA} ${WRKSRC}/AUTHORS ${STAGEDIR}${DOCSDIR}/AUTHORS

.include <bsd.port.mk>

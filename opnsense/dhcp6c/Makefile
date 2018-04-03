# $FreeBSD$

PORTNAME=	dhcp6c
PORTVERSION=	20180403
CATEGORIES=	net ipv6

MAINTAINER=	franco@opnsense.org
COMMENT=	WIDE-DHCPv6 client

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/COPYRIGHT

CONFLICTS_INSTALL=	dhcp6

USE_HARDENING=	safestack

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
GH_TAGNAME=	fae5d4c

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--sysconfdir=${LOCALBASE}/etc \
		--with-localdbdir=/var/db
USE_RC_SUBR=	dhcp6c
PORTDOCS=	README

OPTIONS_DEFINE=	DOCS RAW

RAW_DESC=	Raw option support (experimental)

RAW_EXTRA_PATCHES=${PATCHDIR}/extra-patch-raw

post-install:
	${INSTALL_DATA} ${WRKSRC}/dhcp6c.conf.sample ${STAGEDIR}${PREFIX}/etc
	${RM} ${STAGEDIR}${PREFIX}/man/man5/dhcp6s.conf.5
	${RM} ${STAGEDIR}${PREFIX}/man/man8/dhcp6relay.8
	${RM} ${STAGEDIR}${PREFIX}/man/man8/dhcp6s.8
	${RM} ${STAGEDIR}${PREFIX}/sbin/dhcp6relay
	${RM} ${STAGEDIR}${PREFIX}/sbin/dhcp6s

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/${PORTDOCS} ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>

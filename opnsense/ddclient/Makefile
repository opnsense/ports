PORTNAME=	ddclient
PORTVERSION=	3.10.0
DISTVERSIONPREFIX=	v
PORTREVISION=	7
CATEGORIES=	dns
PKGNAMESUFFIX=	-devel

PATCH_SITES=	https://github.com/ddclient/ddclient/commit/
PATCHFILES=	fa6c95f.patch:-p1 \
		cca4291.patch:-p1 \
		11a5bd5.patch:-p1 \
		5596ee8.patch:-p1 \
		1c91a5a.patch:-p1 \
		d35d62f.patch:-p1 \
		d35d62f.patch:-p1 \
		f01110a.patch:-p1 \
		1a6e443.patch:-p1 \
		8d3a383.patch:-p1

MAINTAINER=	franco@opnsense.org
COMMENT=	Update dynamic DNS entries
WWW=		https://github.com/ddclient/ddclient

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/COPYING

RUN_DEPENDS=	p5-Data-Validate-IP>0:net-mgmt/p5-Data-Validate-IP

USES=		autoreconf gmake perl5 tar:bzip2
GNU_CONFIGURE=	yes
USE_GITHUB=	yes
USE_PERL5=	run
USE_RC_SUBR=	${PORTNAME}

NO_ARCH=	yes
SUB_FILES=	pkg-message ddclient_force

PORTDOCS=	COPYRIGHT ChangeLog README.cisco README.ssl README.md \
		sample-etc_cron.d_ddclient sample-etc_dhclient-exit-hooks \
		sample-etc_dhcpc_dhcpcd-eth0.exe sample-etc_ppp_ip-up.local

CONFLICTS_INSTALL=	ddclient

OPTIONS_DEFINE=	SSL DOCS
OPTIONS_DEFAULT=SSL

SSL_RUN_DEPENDS=ca_root_nss>0:security/ca_root_nss \
		p5-IO-Socket-SSL>0:security/p5-IO-Socket-SSL

post-patch:
	@${GREP} -lR '/usr' ${WRKSRC} | ${XARGS} ${REINPLACE_CMD} -e \
		's|/usr|${PREFIX}|g'
	@${REINPLACE_CMD} -e 's|%%ETCDIR%%|${PREFIX}/etc| ; \
		 s|%%LOCALBASE%%|${LOCALBASE}|' ${WRKSRC}/ddclient.in

do-install:
	(cd ${WRKSRC} && ${INSTALL_DATA} ddclient.conf \
		${STAGEDIR}${PREFIX}/etc/ddclient.conf.sample)
	(cd ${WRKSRC} && ${INSTALL_SCRIPT} ddclient \
		${STAGEDIR}${PREFIX}/sbin)
	@${MKDIR} ${STAGEDIR}${PREFIX}/etc/periodic/daily
	(cd ${WRKDIR} && ${INSTALL_SCRIPT} ddclient_force \
		${STAGEDIR}${PREFIX}/etc/periodic/daily/ddclient_force)
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
.for i in ${PORTDOCS}
	(cd ${WRKSRC} && ${INSTALL_DATA} ${i} ${STAGEDIR}${DOCSDIR})
.endfor

.include <bsd.port.mk>

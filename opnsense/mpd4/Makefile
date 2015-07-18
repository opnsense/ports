PORTNAME=	mpd
DISTVERSION=	4.4.1
PORTREVISION=	2
CATEGORIES=	net
MASTER_SITES=	SF/${PORTNAME}/Mpd4/Mpd-${PORTVERSION}
DIST_SUBDIR=	mpd4
PKGNAMESUFFIX=	4

MAINTAINER=	franco@opnsense.org
COMMENT=	Multi-link PPP daemon based on netgraph(4)

LIB_DEPENDS=	libpdel.so.0:${PORTSDIR}/devel/libpdel

OPTIONS_DEFINE=	NG_IPACCT
NG_IPACCT_DESC=	Use ng_ipacct kernel module from port

HAS_CONFIGURE=	YES
CONFIGURE_WRKSRC=	"${WRKSRC}/src"

USE_OPENSSL=	yes

.include <bsd.port.options.mk>

CONFIGURE_ARGS+= --enable-ipv6

.if ${PORT_OPTIONS:MNG_IPACCT}
BUILD_DEPENDS+=	${LOCALBASE}/include/netgraph/ng_ipacct.h:${PORTSDIR}/net-mgmt/ng_ipacct
.if exists(${KMODDIR}/ng_ipacct.ko)
RUN_DEPENDS+=	${KMODDIR}/ng_ipacct.ko:${PORTSDIR}/net-mgmt/ng_ipacct
.else
RUN_DEPENDS+=	/boot/modules/ng_ipacct.ko:${PORTSDIR}/net-mgmt/ng_ipacct
.endif
.endif

USE_RC_SUBR=	mpd4.sh
HTMLNUM!=	jot 67 1
CONFSUF=	conf links secret script
DOCSDIR=	${PREFIX}/share/doc/mpd4
PORTDOCS=	${HTMLNUM:S/^/mpd/:S/$/.html/} mpd.html mpd.ps README	\
		mpd_toc.html
PLIST_DIRS=	etc/mpd4
PLIST_FILES=	${CONFSUF:S/^/etc\/mpd4\/mpd./:S/$/.sample/} sbin/mpd4 man/man8/mpd4.8.gz

do-install:
	make -C${WRKSRC} install PREFIX=${STAGEDIR}/usr/local

.include <bsd.port.mk>

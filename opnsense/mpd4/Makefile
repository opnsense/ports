PORTNAME=	mpd4
DISTVERSION=	4.4.1
PORTREVISION=	3
CATEGORIES=	net

MAINTAINER=	franco@opnsense.org
COMMENT=	Multi-link PPP daemon based on netgraph(4)

USE_GITHUB=	yes
GH_ACCOUNT=	fichtner
GH_TAGNAME=	cf7a9277

LIB_DEPENDS=	libpdel.so:devel/libpdel

HAS_CONFIGURE=	YES
CONFIGURE_WRKSRC=	"${WRKSRC}/src"

USE_OPENSSL=	yes

CONFIGURE_ARGS+= --enable-ipv6

USE_RC_SUBR=	mpd4

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

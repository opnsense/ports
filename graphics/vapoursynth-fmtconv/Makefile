PORTNAME=	fmtconv
PORTVERSION=	r23
CATEGORIES=	graphics
PKGNAMEPREFIX=	vapoursynth-

MAINTAINER=	jbeich@FreeBSD.org
COMMENT=	Format conversion tools for Vapoursynth

LICENSE=	WTFPL

BROKEN_powerpc64=	fails to compile on powerpc64: \#error

BUILD_DEPENDS=	${LOCALBASE}/include/vapoursynth/VapourSynth.h:multimedia/vapoursynth

USE_GITHUB=	yes
GH_ACCOUNT=	EleonoreMizo

USES=		autoreconf compiler:c++11-lib gmake libtool pkgconfig
EXCLUDE=	VapourSynth.h *.txt
EXTRACT_AFTER_ARGS=	${EXCLUDE:S,^,--exclude ,}
WRKSRC_SUBDIR=	build/unix
PATCH_WRKSRC=	${WRKSRC:H:H}
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--libdir="${DATADIR}"
CPPFLAGS+=	`pkg-config vapoursynth --cflags`
INSTALL_TARGET=	install-strip
DATADIR=	${PREFIX}/lib/vapoursynth
DOCSDIR=	${PREFIX}/share/doc/${PKGBASE}
PORTDATA=	lib${PORTNAME}.so
PORTDOCS=	*

OPTIONS_DEFINE=	DOCS

post-patch:
	@${REINPLACE_CMD} -e 's/x86_64/&|amd64/' \
		${WRKSRC}/configure.ac

post-install:
	(cd ${PATCH_WRKSRC}/doc && ${COPYTREE_SHARE} \
		"${PORTDOCS}" ${STAGEDIR}${DOCSDIR})

.include <bsd.port.mk>

PORTNAME=	xpdf
PORTVERSION=	3.04
PORTREVISION=	14
CATEGORIES=	graphics print
MASTER_SITES=	https://xpdfreader-dl.s3.amazonaws.com/old/
.if !defined(MASTERDIR)
PKGNAMESUFFIX=	3
CONFLICTS_INSTALL=	xpdf4 xpdf
.else
CONFLICTS_INSTALL=	xpdf4 xpdf3
.endif

MAINTAINER=	cy@FreeBSD.org
COMMENT=	Display PDF files and convert them to other formats
WWW=		https://www.xpdfreader.com/

LICENSE=	GPLv2

LIB_DEPENDS=	libfreetype.so:print/freetype2 \
		libpng.so:graphics/png

GNU_CONFIGURE=	yes
GNU_CONFIGURE_MANPREFIX=	${PREFIX}/share/xpdf
USES=		gmake cpe localbase xorg
USE_XORG=	ice sm x11 xext xt

CPE_VENDOR=	glyphandcog
CPE_PRODUCT=	xpdfreader
CONFIGURE_ARGS=	--enable-opi \
		--with-freetype2-library="${LOCALBASE}/lib" \
		--with-freetype2-includes="${LOCALBASE}/include/freetype2" \
		--bindir="${PREFIX}/libexec/xpdf" \
		--mandir="${PREFIX}/share/xpdf/man"

MANDIRS=	${PREFIX}/share/xpdf/man

OPTIONS_DEFINE=	LIBPAPER TYPE1 X11 DOCS
LIBPAPER_DESC=	Enable libpaper
TYPE1_DESC=	Ghostscript type1 fonts
OPTIONS_DEFAULT=TYPE1 X11
OPTIONS_SUB=	yes

SUB_FILES=	xpdf-man.conf

TYPE1_RUN_DEPENDS=	${LOCALBASE}/share/ghostscript/fonts/n021003l.pfb:print/gsfonts

LIBPAPER_LIB_DEPENDS=	libpaper.so:print/libpaper
LIBPAPER_CONFIGURE_ON=	--with-libpaper-library="${LOCALBASE}/lib" \
			--with-libpaper-includes="${LOCALBASE}/include"
LIBPAPER_CONFIGURE_OFF=--without-libpaper-library

.if defined(A4)
CONFIGURE_ARGS+=	--enable-a4-paper
.endif

X11_CONFIGURE_WITH=	x
X11_USES=		desktop-file-utils motif
X11_PLIST_SUB=		DESKTOPDIR=${DESKTOPDIR}

post-patch:
	${REINPLACE_CMD} -e 's|undef USE_COMBO_BOX|define USE_COMBO_BOX 1|' \
		${WRKSRC}/xpdf/XPDFViewer.h

post-install:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
.for file in ANNOUNCE CHANGES README misc/hello.pdf
	${INSTALL_DATA} ${WRKSRC}/${file} ${STAGEDIR}${DOCSDIR}
.endfor
	@cd ${STAGEDIR}${PREFIX}; \
	${LN} -sf ../libexec/xpdf/xpdf bin/xpdf
	${INSTALL_DATA} ${WRKDIR}/xpdf-man.conf \
		${STAGEDIR}${PREFIX}/etc/man.d/xpdf.conf

post-install-X11-on:
	${INSTALL_DATA} ${FILESDIR}/xpdf.desktop ${STAGEDIR}${DESKTOPDIR}

.include <bsd.port.mk>

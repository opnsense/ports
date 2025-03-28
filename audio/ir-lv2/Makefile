PORTNAME=	ir
DISTVERSION=	1.3.4
PORTREVISION=	4
CATEGORIES=	audio
PKGNAMESUFFIX=	-lv2

PATCH_SITES=	https://github.com/${GH_ACCOUNT}/${GH_PROJECT}/commit/
PATCHFILES=	001904135bafa8931e4cf67402e0fa332feb857d.patch:-p1 # Fixing build for lv2 >= 1.18.0: https://github.com/tomszilagyi/ir.lv2/pull/20/

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	LV2 impulse response plugin for reverb and cabinet simulation
WWW=		https://github.com/tomszilagyi/ir.lv2

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	lv2>0:audio/lv2 \
		${LOCALBASE}/include/fftw3.h:math/fftw3
LIB_DEPENDS=	libfreetype.so:print/freetype2 \
		libsndfile.so:audio/libsndfile \
		libsamplerate.so:audio/libsamplerate \
		libzita-convolver.so:audio/zita-convolver \
		libfontconfig.so:x11-fonts/fontconfig

USES=		gmake gnome pkgconfig
USE_GITHUB=	yes
GH_ACCOUNT=	tomszilagyi
GH_PROJECT=	ir.lv2
USE_GNOME=	glib20 gtk20 gdkpixbuf cairo

MAKE_ENV=	INSTDIR=${STAGEDIR}${PREFIX}/lib/lv2

PLIST_FILES=	lib/lv2/ir.lv2/ir.so lib/lv2/ir.lv2/ir.ttl \
		lib/lv2/ir.lv2/ir_gui.so lib/lv2/ir.lv2/manifest.ttl

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/lv2/ir.lv2/ir*.so

.include <bsd.port.mk>

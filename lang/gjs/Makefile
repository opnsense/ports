PORTNAME=	gjs
PORTVERSION=	1.76.3
CATEGORIES=	lang gnome
MASTER_SITES=	GNOME
DIST_SUBDIR=	gnome

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	GNOME Javascript binding
WWW=		https://live.gnome.org/Gjs

LICENSE=	MPL11 LGPL20+ GPLv2+
LICENSE_COMB=	multi
LICENSE_FILE_MPL11=	${WRKSRC}/LICENSES/MPL-1.1.txt
LICENSE_FILE_LGPL20+ =	${WRKSRC}/LICENSES/LGPL-2.1-or-later.txt

BUILD_DEPENDS=	dbus-run-session:devel/dbus
LIB_DEPENDS=	libmozjs-102.so:lang/spidermonkey102 \
		libffi.so:devel/libffi

USES=		compiler:c++11-lib gettext gnome \
		localbase meson pkgconfig python:build readline tar:xz xorg
USE_GNOME=	cairo gtk40 introspection pango
USE_XORG=	x11 xext
MESON_ARGS=	-Dprofiler=disabled \
		-Dinstalled_tests=false
USE_LDCONFIG=	yes

CONFIGURE_ENV=	PYTHONDONTWRITEBYTECODE=1
MAKE_ENV=	PYTHONDONTWRITEBYTECODE=1

post-patch:
	${REINPLACE_CMD} -e "s|'--warn-error'|''|" ${WRKSRC}/meson.build

.include <bsd.port.mk>

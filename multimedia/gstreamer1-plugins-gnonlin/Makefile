PORTNAME=	gstreamer1-plugins-gnonlin
PORTVERSION=	1.4.0
PORTREVISION=	1
CATEGORIES=	multimedia
MASTER_SITES=	http://gstreamer.freedesktop.org/src/gnonlin/
DISTNAME=	gnonlin-${PORTVERSION}

MAINTAINER=	multimedia@FreeBSD.org
COMMENT=	GStreamer library for writing non-linear audio and video
WWW=		http://gstreamer.net

# References need removed from Mk/Uses/gstreamer.mk, as well.
DEPRECATED=		Deprecated upstream. Use the gstnle plugin from multimedia/gstreamer1-editing-services instead
EXPIRATION_DATE=	2024-10-22

USES=		gettext-runtime gnome gstreamer libtool pkgconfig python:build tar:xz
USE_GNOME=	glib20
GNU_CONFIGURE=	yes
USE_GSTREAMER=	good
INSTALL_TARGET=	install-strip

PLIST_FILES=	lib/gstreamer-1.0/libgnl.so

.include <bsd.port.mk>

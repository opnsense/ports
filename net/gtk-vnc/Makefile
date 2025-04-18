PORTNAME=	gtk-vnc
PORTVERSION=	1.3.1
PORTREVISION=	6
CATEGORIES=	net gnome
MASTER_SITES=	GNOME

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	VNC viewer widget for GTK
WWW=		http://live.gnome.org/gtk-vnc

LICENSE=	LGPL21
LICENSE_FILE=	${WRKSRC}/COPYING.LIB

LIB_DEPENDS=	libgnutls.so:security/gnutls \
		libgcrypt.so:security/libgcrypt \
		libgpg-error.so:security/libgpg-error \
		libsasl2.so:security/cyrus-sasl2

USES=		gettext gnome localbase meson perl5 pkgconfig python \
		tar:xz vala:build xorg
USE_GNOME=	cairo gdkpixbuf gtk30 introspection:build
USE_XORG=	x11
USE_LDCONFIG=	yes

OPTIONS_DEFINE=	PULSEAUDIO
OPTIONS_DEFAULT=PULSEAUDIO
OPTIONS_SUB=	yes

PULSEAUDIO_DESC=	use PulseAudio for audio playback
PULSEAUDIO_MESON_ENABLED=	pulseaudio
PULSEAUDIO_LIB_DEPENDS=	libpulse.so:audio/pulseaudio

BINARY_ALIAS=	python3=${PYTHON_VERSION}

.include <bsd.port.mk>

PORTNAME=	sbxkb
PORTVERSION=	0.7.6
PORTREVISION=	3
CATEGORIES=	x11
MASTER_SITES=	SF/staybox

MAINTAINER=	ports@FreeBSD.org
COMMENT=	XKB keyboard layout indicator and switcher
WWW=		https://sourceforge.net/projects/staybox/

LICENSE=	GPLv3

GNU_CONFIGURE=	yes
LIBS+=		-L${LOCALBASE}/lib -lX11
USES=		gnome pkgconfig xorg
USE_GNOME=	gdkpixbuf gdkpixbuf2xlib gtk20
USE_XORG=	x11

post-patch:
# Remove debug flag (-g) from CFLAGS
	@${REINPLACE_CMD} -e 's,-g$$,,' ${WRKSRC}/Makefile.in

.include <bsd.port.mk>

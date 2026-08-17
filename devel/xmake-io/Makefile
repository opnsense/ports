PORTNAME=	xmake-io
DISTVERSION=	3.0.9
CATEGORIES=	devel
MASTER_SITES=	https://github.com/${PORTNAME}/xmake/releases/download/v${DISTVERSION}/
DISTNAME=	xmake-v${DISTVERSION}

MAINTAINER=	pericycle.cc@gmail.com
COMMENT=	Cross-platform build utility based on Lua
WWW=		https://xmake.io/

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE.md

LIB_DEPENDS=	liblz4.so:archivers/liblz4 \
		libsv.so:devel/sv \
		libtbox.so:devel/tbox

USES=		gmake lua:54 luajit pkgconfig readline

HAS_CONFIGURE=	yes
CONFIGURE_ARGS=	--external=yes
LDFLAGS+=	-lexecinfo

WRKSRC=		${WRKDIR}/xmake-${DISTVERSION}

.include <bsd.port.mk>

PORTNAME=	mod_proxy_msrpc
PORTVERSION=	0.6
DISTVERSIONPREFIX=${PORTNAME}-
CATEGORIES=	www

MAINTAINER=	franco@opnsense.org
COMMENT=	Apache module for reverse proxy Outlook Anywhere support

LICENSE=	APACHE20

LIB_DEPENDS=	libinotify.so:devel/libinotify \
		libuuid.so:misc/e2fsprogs-libuuid

AP_EXTRAS=	-L ${PREFIX}/lib -linotify -luuid

USES=		apache autoreconf
USE_GITHUB=	yes
GH_ACCOUNT=	bombadil
AP_FAST_BUILD=	yes

AUTORECONF_WRKSRC=	${WRKSRC}/..
WRKSRC_SUBDIR=		src

.include <bsd.port.mk>

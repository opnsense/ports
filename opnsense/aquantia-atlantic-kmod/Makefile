PORTNAME=	aquantia-atlantic-kmod
PORTVERSION=	0.0.5
PORTREVISION=	4
CATEGORIES=	net

MAINTAINER=	franco@opnsense.org
COMMENT=	Aquantia AQtion (Atlantic) Network Driver (Development Preview)
WWW=		https://github.com/albb0920/aqtion-freebsd-aq2

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		kmod uidfix
USE_GITHUB=	yes

GH_ACCOUNT=	albb0920
GH_PROJECT=	aqtion-freebsd-aq2
GH_TAGNAME=	6f338e6

PLIST_FILES=	${KMODDIR}/if_atlantic.ko

.include <bsd.port.mk>

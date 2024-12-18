PORTNAME=	mdns-repeater
PORTVERSION=	1.11
PORTREVISION=	2
CATEGORIES=	net dns

MAINTAINER=	ehaupt@FreeBSD.org
COMMENT=	Multicast DNS repeater to re-broadcast mDNS packets across interfaces
WWW=		https://github.com/kennylevinsen/mdns-repeater/

LICENSE=	GPLv2

USE_GITHUB=	yes
GH_ACCOUNT=	Alphix
GH_TAGNAME=	75966e2

USE_RC_SUBR=	mdns-repeater

CFLAGS+=	-DHGVERSION="\"${PORTVERSION}\"" \
		-DIPV6_ADD_MEMBERSHIP=IPV6_JOIN_GROUP

PLIST_FILES=	bin/mdns-repeater

do-build:
	${CC} ${CFLAGS} -o ${WRKSRC}/${PORTNAME} ${WRKSRC}/${PORTNAME}.c

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/bin

.include <bsd.port.mk>

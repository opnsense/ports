PORTNAME=	netbird
DISTVERSION=	0.36.5
DISTVERSIONPREFIX=	v
PORTREVISION=   1
CATEGORIES=	net security net-vpn

WRKSRC=		${WRKDIR}/netbird-${PORTVERSION}

MAINTAINER=	opn-netbird@sun-ri.se
COMMENT=	Mesh VPN
WWW=		https://netbird.io/

LICENSE=        BSD3CLAUSE
LICENSE_FILE=   ${WRKSRC}/LICENSE

USES=		go:1.23,modules

GO_MODULE=	github.com/netbirdio/netbird

USE_RC_SUBR=	netbird

GO_TARGET=	./client:netbird
GO_BUILDFLAGS=	-tags freebsd -o ${PORTNAME} -ldflags "\
		 -s -w -X github.com/netbirdio/netbird/version.version=${PORTVERSION}"

PLIST_FILES=	bin/netbird


.include <bsd.port.mk>

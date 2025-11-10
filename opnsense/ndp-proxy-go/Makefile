PORTNAME=	ndp-proxy-go
DISTVERSIONPREFIX=	v
DISTVERSION=	0.1.5
CATEGORIES=	net
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	cedrik@pischem.com
COMMENT=	IPv6 Neighbor Discovery Protocol (NDP) Proxy
WWW=		https://github.com/Monviech/ndp-proxy-go

LICENSE=	BSD2CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		cpe go:modules
CPE_VENDOR=	monviech

USE_RC_SUBR=	ndp-proxy-go

GO_MODULE=	github.com/Monviech/ndp-proxy-go
GO_BUILDFLAGS+=	-ldflags="-X main.version=${DISTVERSIONFULL}"
GO_TARGET=	.:${PREFIX}/sbin/${PORTNAME}

PLIST_FILES=	sbin/${PORTNAME} \
		share/man/man8/${PORTNAME}.8.gz

post-install:
	${INSTALL_MAN} ${FILESDIR}/${PORTNAME}.8 \
		${STAGEDIR}${PREFIX}/share/man/man8/

.include <bsd.port.mk>

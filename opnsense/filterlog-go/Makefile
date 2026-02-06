PORTNAME=   opnsense-filterlog
DISTVERSIONPREFIX=  v
DISTVERSION=    0.8.0
CATEGORIES= sysutils

MAINTAINER= me@allddd.onl
COMMENT=    TUI for viewing and analysing OPNsense firewall logs
WWW=    https://gitlab.com/allddd/opnsense-filterlog

LICENSE=    BSD2CLAUSE
LICENSE_FILE=   ${WRKSRC}/LICENSE

USES=   go:1.25,modules
CGO_ENABLED=    0
GO_MODULE=	gitlab.com/allddd/opnsense-filterlog
GO_TARGET=	.:${PREFIX}/sbin/${PORTNAME}
GO_BUILDFLAGS+=	-ldflags="-s -w -X ${GO_MODULE}/internal/meta.Version=${DISTVERSIONFULL}"

PLIST_FILES=    sbin/${PORTNAME} share/man/man8/${PORTNAME}.8.gz

post-install:
	${INSTALL_MAN} ${WRKSRC}/docs/${PORTNAME}.8 ${STAGEDIR}${PREFIX}/share/man/man8/

.include <bsd.port.mk>

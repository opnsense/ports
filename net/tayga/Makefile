PORTNAME=	tayga
DISTVERSION=	0.9.5
CATEGORIES=	net

PATCH_SITES=	https://github.com/${GH_ACCOUNT}/${PORTNAME}/commit/
PATCHFILES=	49f64b0.patch:-p1 32cd0a7.patch:-p1 b62e33f.patch:-p1

MAINTAINER=	franco@opnsense.org
COMMENT=	Userland stateless NAT64 daemon
WWW=		http://www.litech.org/tayga/

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		gmake
MAKE_ARGS=	CFLAGS="${CFLAGS} -DTAYGA_CONF_PATH=\"/usr/local/etc/tayga.conf\""

USE_GITHUB=	yes
GH_ACCOUNT=	apalrd

MAKE_ENV=	RELEASE=${DISTVERSION}

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/tayga
	${INSTALL_DATA} ${WRKSRC}/tayga.conf.example ${STAGEDIR}${PREFIX}/etc

.include <bsd.port.mk>

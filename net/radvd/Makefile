PORTNAME=	radvd
PORTVERSION=	2.20.d
CATEGORIES=	net
MASTER_SITES=	http://www.litech.org/radvd/dist/

MAINTAINER=	farrokhi@FreeBSD.org
COMMENT=	Linux/BSD IPv6 router advertisement daemon
WWW=		http://www.litech.org/radvd/

LICENSE=	RADVD
LICENSE_NAME=	RADVD License
LICENSE_FILE=	${WRKSRC}/COPYRIGHT
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

GNU_CONFIGURE=	yes
USES=		autoreconf gmake pkgconfig
CONFIGURE_ARGS=	--program-transform-name=
USE_RC_SUBR=	radvd

USE_GITHUB=	yes
GH_ACCOUNT=	radvd-project
GH_TAGNAME=	1cab839

PORTDOCS=	CHANGES COPYRIGHT INTRO.html README TODO

OPTIONS_DEFINE=	DOCS

post-install:
	${INSTALL_DATA} ${WRKSRC}/radvd.conf.example ${STAGEDIR}${PREFIX}/etc/radvd.conf.sample
	${INSTALL} -d ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${PORTDOCS:S.^.${WRKSRC}/.} ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>

PORTNAME=	epm
PORTVERSION=	4.5.1
PORTREVISION=	1
CATEGORIES=	devel
MASTER_SITES=	https://github.com/michaelrsweet/epm/releases/download/v${PORTVERSION}/

MAINTAINER=	office@FreeBSD.org
COMMENT=	Free UNIX software/file packaging program
WWW=		https://www.msweet.org/epm/

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/COPYING

GNU_CONFIGURE=	yes
MAKE_JOBS_UNSAFE=	yes

OPTIONS_DEFINE=	DOCS

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/epm
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/epminstall
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/mkepmlist

.include <bsd.port.mk>

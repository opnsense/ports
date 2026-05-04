PORTNAME=	canna
PORTVERSION=	3.7p5
CATEGORIES=	japanese
MASTER_SITES=	https://github.com/canna-input/canna/releases/download/release-${PORTVERSION}/
PKGNAMESUFFIX=	-server
DISTNAME=	Canna${PORTVERSION:S/.//g}

MAINTAINER=	mce@FreeBSD.org
COMMENT=	Kana-to-Kanji conversion system, binary part
WWW=		https://canna-input.github.io/

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYRIGHT

LIB_DEPENDS=	libcanna.so:japanese/canna-lib

USES=		imake tar:bzip2
USE_RC_SUBR=	canna

MAKE_JOBS_UNSAFE=	yes
INSTALL_TARGET=	instserver instclient

PORTDOCS=	CHANGES.jp ChangeLog README.jp RKCCONF.jp

OPTIONS_DEFINE=	DOCS

post-install:
	@cd ${INSTALL_WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE} ${MAKE_FLAGS} \
	    ${MAKEFILE} ${MAKE_ARGS} install.man
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	cd ${WRKSRC} && ${INSTALL_DATA} ${PORTDOCS} ${STAGEDIR}${DOCSDIR}
	@cd ${STAGEDIR}${PREFIX}/sbin && ${RM} cannakill && \
		${RLN} ../bin/catdic cannakill

.include <bsd.port.mk>

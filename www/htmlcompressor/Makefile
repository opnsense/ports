PORTNAME=	htmlcompressor
PORTVERSION=	1.5.3
PORTREVISION=	3
CATEGORIES=	www java
MASTER_SITES=	https://github.com/serg472/htmlcompressor/releases/download/${PORTVERSION}/
EXTRACT_SUFX=	.jar
EXTRACT_ONLY=	# empty

MAINTAINER=	ports@FreeBSD.org
COMMENT=	HTML/XML Compressor
WWW=		https://github.com/serg472/htmlcompressor

LICENSE=	APACHE20

USES=		java

NO_WRKSUBDIR=	yes
NO_BUILD=	yes
NO_ARCH=	yes

PLIST_FILES=	bin/htmlcompressor %%JAVAJARDIR%%/htmlcompressor.jar
SUB_FILES=	htmlcompressor

do-install:
	@${MKDIR} ${STAGEDIR}${JAVAJARDIR}
	${INSTALL_DATA} ${DISTDIR}/${DISTNAME}.jar ${STAGEDIR}${JAVAJARDIR}/htmlcompressor.jar
	${INSTALL_SCRIPT} ${WRKDIR}/htmlcompressor ${STAGEDIR}${PREFIX}/bin

.include <bsd.port.mk>

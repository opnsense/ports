PORTNAME=	denominator
PORTVERSION=	4.7.1
CATEGORIES=	dns java
MASTER_SITES=	https://bintray.com/artifact/download/netflixoss/maven/com/netflix/${PORTNAME}/${PORTNAME}-cli/${PORTVERSION}/
DISTNAME=	${PORTNAME}-cli-${PORTVERSION}-fat.jar
EXTRACT_SUFX=

MAINTAINER=	bofh@FreeBSD.org
COMMENT=	Portably control DNS clouds
WWW=		https://github.com/Netflix/denominator

USES=		java

NO_BUILD=	yes
STRIP=		# none
PLIST_FILES=	bin/${PORTNAME}

do-extract:
	@${MKDIR} ${WRKDIR}/${DISTNAME}
	@${CP} ${DISTDIR}/${DISTNAME} ${WRKDIR}/${DISTNAME}

do-install:
	${INSTALL_PROGRAM} ${WRKDIR}/${DISTNAME}/${DISTNAME} ${STAGEDIR}${PREFIX}/bin/${PORTNAME}

.include <bsd.port.mk>

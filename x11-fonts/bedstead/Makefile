PORTNAME=	bedstead
DISTVERSION=	3.261
CATEGORIES=	x11-fonts
MASTER_SITES=	https://bjh21.me.uk/bedstead/

MAINTAINER=	olgeni@FreeBSD.org
COMMENT=	Outline font based on the Mullard SAA5050 teletext character generator
WWW=		https://bjh21.me.uk/bedstead/

LICENSE=	CC0-1.0
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		fonts zip

NO_ARCH=	yes
NO_BUILD=	yes

PLIST_FILES=	${OTFFILES:S,^,${FONTSDIR:S,^${PREFIX}/,,}/,}

OTFFILES=	bedstead.otf \
		bedstead-bold.otf \
		bedstead-boldcondensed.otf \
		bedstead-boldextended.otf \
		bedstead-boldextracondensed.otf \
		bedstead-boldsemicondensed.otf \
		bedstead-boldultracondensed.otf \
		bedstead-condensed.otf \
		bedstead-extended.otf \
		bedstead-extracondensed.otf \
		bedstead-semicondensed.otf \
		bedstead-ultracondensed.otf

do-install:
	@${MKDIR} ${STAGEDIR}${FONTSDIR}
.for f in ${OTFFILES}
	${INSTALL_DATA} ${WRKSRC}/${f} ${STAGEDIR}${FONTSDIR}
.endfor

.include <bsd.port.mk>

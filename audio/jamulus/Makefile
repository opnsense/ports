PORTNAME=	jamulus
DISTVERSIONPREFIX=	r
DISTVERSION=	3_11_0
CATEGORIES=	audio

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Internet jam session software
WWW=		https://jamulus.io \
		https://github.com/jamulussoftware/jamulus

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS=	libjack.so:audio/jack

FLAVORS=	desktop server
FLAVOR?=	${FLAVORS:[1]}
server_PKGNAMESUFFIX=	-server

USES=		compiler:c++11-lang gl pkgconfig qmake qt:5
USE_QT=		concurrent core multimedia network xml buildtools:build linguisttools:build
USE_GL=		gl

USE_GITHUB=	yes
GH_ACCOUNT=	jamulussoftware

.if ${FLAVOR:U} == desktop
USES+=		desktop-file-utils
USE_QT+=	gui widgets
PLIST_FILES=	bin/${PORTNAME} \
		share/applications/${PORTNAME}.desktop \
		share/applications/${PORTNAME}-server.desktop \
		share/icons/hicolor/512x512/apps/io.${PORTNAME}.${PORTNAME}.png \
		share/icons/hicolor/scalable/apps/io.${PORTNAME}.${PORTNAME}.svg \
		share/icons/hicolor/scalable/apps/io.${PORTNAME}.${PORTNAME}server.svg \
		share/man/man1/Jamulus.1.gz \
		share/pixmaps/${PORTNAME}.png \
		share/pixmaps/${PORTNAME}-server.png
.endif

.if ${FLAVOR:U} == server
COMMENT+=	(headless server)
QMAKE_ARGS=	CONFIG+="headless nosound"
USER=		nobody
SUB_LIST=	USER=${USER}
USE_RC_SUBR=	${PORTNAME}-server
PLIST_FILES=	bin/${PORTNAME}-server
.endif

QMAKE_ARGS+=	CONFIG+="noupcasename"

PORTSCOUT=	limit:^r\d+_ # prevent malformatted tags, like 'latest'

.if ${FLAVOR:U} == desktop
post-install:
	# workaround for https://gitlab.xfce.org/xfce/xfdesktop/-/issues/131
	${RLN} ${STAGEDIR}${PREFIX}/share/icons/hicolor/512x512/apps/io.jamulus.jamulus.png ${STAGEDIR}${PREFIX}/share/pixmaps/jamulus.png
	# add Jamulus Server menu item which is simply 'jamulus -s' with a special icon
	${CP} ${STAGEDIR}${PREFIX}/share/applications/${PORTNAME}.desktop ${STAGEDIR}${PREFIX}/share/applications/${PORTNAME}-server.desktop
	${REINPLACE_CMD} -i '' ' \
		s|Name=Jamulus|Name=Jamulus Server| ; \
		s|Comment=Jam Session|Comment=Jam Session Server| ; \
		s|Exec=jamulus|Exec=jamulus -s| ; \
		s|Icon=jamulus|Icon=jamulus-server| ; \
		' ${STAGEDIR}${PREFIX}/share/applications/${PORTNAME}-server.desktop
	${INSTALL_DATA} ${WRKSRC}/src/res/fronticonserver.png ${STAGEDIR}${PREFIX}/share/pixmaps/${PORTNAME}-server.png
.endif

.if ${FLAVOR:U} == server
post-install:
	${MV} ${STAGEDIR}${PREFIX}/bin/${PORTNAME} ${STAGEDIR}${PREFIX}/bin/${PORTNAME}-server
.endif

.include <bsd.port.mk>

PORTNAME=	pulseaudio
PORTVERSION=	10.0
DISTVERSIONSUFFIX=	-6.el7_9
PORTREVISION=	3
CATEGORIES=	audio linux
PKGNAMESUFFIX=	-libs

MAINTAINER=	emulation@FreeBSD.org
COMMENT=	Libraries for PulseAudio clients (Linux CentOS ${LINUX_DIST_VER})
WWW=		https://pulseaudio.org/

USES=		cpe linux:c7
USE_LDCONFIG=	yes
USE_LINUX=	dbuslibs libasyncns libsndfile systemd-libs tcp_wrappers-libs \
		xorglibs
USE_LINUX_RPM=	yes

# located by rpath
NO_SHLIB_REQUIRES_GLOB=	libpulsecommon-*.so* libpulsedsp.so*

LIB_DISTNAMES=	${PORTNAME}${PKGNAMESUFFIX}-${DISTVERSIONFULL} \
		${PORTNAME}${PKGNAMESUFFIX}-glib2-${DISTVERSIONFULL}

CONFLICTS=	linux-c6-${PORTNAME}${PKGNAMESUFFIX}
DESCR=		${.CURDIR}/../${PORTNAME}/pkg-descr
DOCSDIR=	${PREFIX}/usr/share/doc/${PORTNAME}${PKGNAMESUFFIX}-${PORTVERSION}

OPTIONS_DEFINE=	DOCS NLS
OPTIONS_SUB=	yes

post-patch:
	@${RM} ${WRKSRC}/etc/pulse/client.conf.orig

.include <bsd.port.mk>

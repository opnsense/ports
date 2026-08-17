PORTNAME=	sdformat
DISTVERSION=	16.0.0
CATEGORIES=	misc
MASTER_SITES=	https://osrf-distributions.s3.amazonaws.com/sdformat/releases/

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Simulation Description Format (SDF) parser and description files
WWW=		https://bitbucket.org/osrf/sdformat/src/default/

LICENSE=	APACHE20

BUILD_DEPENDS=	cli11>0:devel/cli11 \
		ignition-cmake>0:devel/ignition-cmake \
		ignition-tools>0:devel/ignition-tools \
		rubygem-rexml>0:textproc/rubygem-rexml
LIB_DEPENDS=	libgz-math.so:math/ignition-math \
		libgz-utils.so:devel/ignition-utils \
		libconsole_bridge.so:devel/ros-console_bridge \
		libtinyxml2.so:textproc/tinyxml2 \
		liburdfdom_world.so:devel/ros-urdfdom
RUN_DEPENDS=	ignition-tools>0:devel/ignition-tools

USES=		cmake compiler:c++17-lang pkgconfig ruby:build tar:bz2
USE_LDCONFIG=	yes

CMAKE_OFF=	BUILD_TESTING

#WRKSRC=		${WRKDIR}/${BB_ACCOUNT}-${BB_PROJECT}-${BB_COMMIT}

PLIST_SUB+=	INCSUBDIR=${PORTNAME}-${DISTVERSION:R}

do-test:
	@cd ${BUILD_WRKSRC} && \
		${SETENV} ${CONFIGURE_ENV} ${CMAKE_BIN} ${CMAKE_ARGS} -DBUILD_TESTING:BOOL=ON ${CMAKE_SOURCE_PATH} && \
		${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${MAKE_ARGS} ${ALL_TARGET} && \
		${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${MAKE_ARGS} test

.include <bsd.port.mk>

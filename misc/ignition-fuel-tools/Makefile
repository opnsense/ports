PORTNAME=	ignition-fuel-tools
DISTVERSIONPREFIX=	gz-fuel-tools11_
DISTVERSION=	11.0.0
CATEGORIES=	misc

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Classes and tools for interacting with Ignition Fuel
WWW=		https://ignitionrobotics.org/home \
		https://gazebosim.org/libs/fuel_tools/ \
		https://github.com/gazebosim/gz-fuel-tools

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	ignition-cmake>=5:devel/ignition-cmake
LIB_DEPENDS=	libcurl.so:ftp/curl \
		libgz-common.so:devel/ignition-common \
		libgz-math.so:math/ignition-math \
		libgz-msgs.so:devel/ignition-msgs \
		libjsoncpp.so:devel/jsoncpp \
		libprotobuf.so:devel/protobuf \
		libtinyxml2.so:textproc/tinyxml2 \
		libuuid.so:misc/libuuid \
		libyaml.so:textproc/libyaml \
		libzip.so:archivers/libzip

USES=		cmake compiler:c++17-lang pkgconfig

LDFLAGS+=	-Wl,--as-needed
USE_LDCONFIG=	yes

CMAKE_OFF=	BUILD_TESTING

USE_GITHUB=	yes
GH_ACCOUNT=	gazebosim
GH_PROJECT=	gz-fuel-tools

PLIST_SUB+=	FUEL_TOOLS_IGN_VER=fuel_tools${DISTVERSION:R:R}

TESTING_UNSAFE=	4 tests are known to fail: https://bitbucket.org/ignitionrobotics/ign-fuel-tools/issues/48/4-unit-tests-fail-unit_fuelclient_test

do-test:
	@cd ${BUILD_WRKSRC} && \
		${SETENV} ${CONFIGURE_ENV} ${CMAKE_BIN} ${CMAKE_ARGS} -DBUILD_TESTING=ON ${CMAKE_SOURCE_PATH} && \
		${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${MAKE_ARGS} ${ALL_TARGET} && \
		${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${MAKE_ARGS} test

.include <bsd.port.mk>

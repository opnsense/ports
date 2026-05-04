PORTNAME=	ncrystal
DISTVERSIONPREFIX=	v
DISTVERSION=	4.3.4
CATEGORIES=	science # physics

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Library for thermal neutron transport in crystals and other materials
WWW=		https://github.com/mctools/ncrystal

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		cmake:testing python:build,test shebangfix
USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	mctools

SHEBANG_FILES=	tests/scripts/*

CMAKE_TESTING_ON=	NCRYSTAL_ENABLE_TESTING \
			NCRYSTAL_ENABLE_CORE_TEST

# tests as of 4.3.4: 100% tests passed, 0 tests failed out of 124

.include <bsd.port.mk>

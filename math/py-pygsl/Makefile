PORTNAME=	pygsl
PORTVERSION=	2.6.4
PORTREVISION=	2
CATEGORIES=	math python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Python interface to GNU Scientific Library
WWW=		https://github.com/pygsl/pygsl

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}meson-python>=0:devel/meson-python@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numpy1>=0:math/py-numpy1@${PY_FLAVOR} \
		swig:devel/swig
LIB_DEPENDS=	libgsl.so:math/gsl
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}numpy1>=0:math/py-numpy1@${PY_FLAVOR}

USES=		pkgconfig python
USE_PYTHON=	autoplist concurrent pep517

post-install:
	${FIND} ${STAGEDIR}${PYTHON_SITELIBDIR} -name '*.so' -exec ${STRIP_CMD} {} +

.include <bsd.port.mk>

PORTNAME=	pytensor
DISTVERSION=	2.34.0 # last tag not requiring numpy-2.x
PORTREVISION=	1
CATEGORIES=	math python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Optimizing compiler for evaluating mathematical expressions
WWW=		https://pytensor.readthedocs.io/en/latest/ \
		https://github.com/pymc-devs/pytensor

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/doc/LICENSE.txt

BUILD_DEPENDS=	${PY_SETUPTOOLS} \
		${PYTHON_PKGNAMEPREFIX}numpy1>=1.16:math/py-numpy1@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}versioneer>=0.29:devel/py-versioneer@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}wheel>0:devel/py-wheel@${PY_FLAVOR} \
		${PY_DEPENDS}
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}cons>0:devel/py-cons@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}etuples>0:devel/py-etuples@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}filelock>=3.15:sysutils/py-filelock@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}logical-unification>0:math/py-logical-unification@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}miniKanren>0:devel/py-miniKanren@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numba>=0.57:devel/py-numba@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numpy1>=1.16:math/py-numpy1@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}scipy>=1:science/py-scipy@${PY_FLAVOR}

USES=		python
USE_PYTHON=	pep517 cython autoplist pytest # tests fail to run, see https://github.com/pymc-devs/pytensor/issues/355

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PYTHON_SITELIBDIR}/pytensor/scan/scan_perform${PYTHON_TAG}.so

# BUG: installs the file /usr/local/lib/python3.9/site-packages/bin/__init__.py, see https://github.com/pymc-devs/pytensor/issues/356

# tests as of : 5 failed, 3 passed, 232 errors in 292.68s (0:04:52), see https://github.com/pymc-devs/pytensor/issues/2027

.include <bsd.port.mk>

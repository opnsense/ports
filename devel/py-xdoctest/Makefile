PORTNAME=	xdoctest
DISTVERSION=	1.3.2
CATEGORIES=	devel python
MASTER_SITES=	PYPI # has no tests
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Python package for executing tests in documentation strings
WWW=		https://github.com/Erotemic/xdoctest

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PY_SETUPTOOLS} \
		${PYTHON_PKGNAMEPREFIX}wheel>0:devel/py-wheel@${PY_FLAVOR}

USES=		python
USE_PYTHON=	pep517 concurrent autoplist

NO_ARCH=	yes

TEST_ENV=	${MAKE_ENV} PYTHONPATH=${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}

do-test:
	@cd ${WRKSRC} && ${SETENV} ${TEST_ENV} ${STAGEDIR}${PREFIX}/bin/xdoctest -m xdoctest

# tests as of 1.3.2: 125 passed, 13 skipped, 1 warning in 9.29 seconds

.include <bsd.port.mk>

PORTNAME=	falcon
DISTVERSION=	3.1.3
PORTREVISION=	1
CATEGORIES=	www python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	lichray@gmail.com
COMMENT=	High-performance Python framework for building cloud APIs
WWW=		https://falconframework.org/

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}python-mimeparse>=1.5.2:devel/py-python-mimeparse@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}six>=1.4.0:devel/py-six@${PY_FLAVOR}
TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}jsonschema>=0:devel/py-jsonschema@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}msgpack>=0:devel/py-msgpack@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pecan>=0:www/py-pecan@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pytest>=0:devel/py-pytest@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyyaml>=0:devel/py-pyyaml@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}requests>=0:www/py-requests@${PY_FLAVOR}

USES=		python
USE_PYTHON=	autoplist cython distutils

post-install:
	@${FIND} ${STAGEDIR}${PYTHON_SITELIBDIR}/falcon/ -name '*.so' -exec ${STRIP_CMD} {} +

do-test:
		@cd ${WRKSRC} && ${SETENV} ${TEST_ENV} ${PYTHON_CMD} -m pytest --ignore=freenit/project/ -v -rs -o addopts= \
			--ignore-glob='*test_media_handlers*' \
			--ignore-glob='*test_functional*' \
			--ignore-glob='*test_cmd_print_api*' \
			--ignore-glob='*test_cython*'

.include <bsd.port.mk>

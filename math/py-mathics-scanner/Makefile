PORTNAME=	mathics_scanner
PORTVERSION=	1.4.1
PORTREVISION=	1
CATEGORIES=	math python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	thierry@FreeBSD.org
COMMENT=	Tokeniser, char tables, & conversion routines for the Wolfram Language
WWW=		https://mathics.org/

LICENSE=	GPLv3

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}ujson>0:devel/py-ujson@${PY_FLAVOR}	\
		${PYTHON_PKGNAMEPREFIX}click>0:devel/py-click@${PY_FLAVOR}	\
		${PYTHON_PKGNAMEPREFIX}pyyaml>0:devel/py-pyyaml@${PY_FLAVOR}	\
		${PYTHON_PKGNAMEPREFIX}chardet>0:textproc/py-chardet@${PY_FLAVOR}
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}ujson>0:devel/py-ujson@${PY_FLAVOR}	\
		${PYTHON_PKGNAMEPREFIX}click>0:devel/py-click@${PY_FLAVOR}	\
		${PYTHON_PKGNAMEPREFIX}chardet>0:textproc/py-chardet@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyyaml>0:devel/py-pyyaml@${PY_FLAVOR}	\
		${PYTHON_PKGNAMEPREFIX}types-ujson>0:devel/py-types-ujson@${PY_FLAVOR}	\
		${PYTHON_PKGNAMEPREFIX}types-PyYAML>0:devel/py-types-PyYAML@${PY_FLAVOR}
TEST_DEPENDS=	gmake:devel/gmake	\
		${PYTHON_PKGNAMEPREFIX}pytest>0:devel/py-pytest@${PY_FLAVOR}

#USE_GITHUB=	yes
#GH_ACCOUNT=	Mathics3

USES=		python shebangfix
USE_PYTHON=	distutils noflavors

NO_ARCH=	yes
MAKE_ENV+=	PYTHON=${PYTHON_CMD}
PLIST_SUB+=	VER=${PORTVERSION}
TEST_TARGET=	check
TEST_ENV=	${MAKE_ENV}

do-test: install
	(cd ${TEST_WRKSRC} &&	\
	${SETENV} ${TEST_ENV} ${GMAKE} ${MAKE_FLAGS} ${MAKEFILE} ${TEST_TARGET})

.include <bsd.port.mk>

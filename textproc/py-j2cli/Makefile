PORTNAME=		j2cli
DISTVERSIONPREFIX=	v
DISTVERSION=		0.3.12b
PORTREVISION=	2
CATEGORIES=		textproc python
PKGNAMEPREFIX=		${PYTHON_PKGNAMEPREFIX}

MAINTAINER=		vendion@gmail.com
COMMENT=		Jinja2 Command-Line Tool, reworked
WWW=		https://github.com/kolypto/j2cli

LICENSE=		BSD2CLAUSE
LICENSE_FILE=		${WRKSRC}/LICENSE

RUN_DEPENDS=		${PYTHON_PKGNAMEPREFIX}Jinja2>0:devel/py-Jinja2@${PY_FLAVOR}

TEST_DEPENDS=		${PYTHON_PKGNAMEPREFIX}tox>0:devel/py-tox@${PY_FLAVOR}

USES=			python

OPTIONS_DEFINE=		TEST YAML
OPTIONS_DEFAULT=	TEST YAML

YAML_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}pyyaml>=0:devel/py-pyyaml@${PY_FLAVOR}

.include <bsd.port.options.mk>

USE_PYTHON=		autoplist concurrent distutils
USE_GITHUB=		yes
GH_ACCOUNT=		kolypto
.if ${PORT_OPTIONS:MTEST}
TEST_TARGET=		test
.endif

NO_ARCH=		yes

TEST_ENV=		TMPDIR=${WKRDIR}

do-test:
	@cd ${WRKSRC} && \
	${SETENV} ${TEST_ENV} ${LOCALBASE}/bin/tox-${PYTHON_VER} -v

.include <bsd.port.mk>

PORTNAME=	colibri
DISTVERSION=	g20260717
CATEGORIES=	misc # machine-learning
PKGNAMESUFFIX=	-ai

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Run GLM-5.2 (744B MoE) on a 25GB-RAM consumer machine
WWW=		https://github.com/JustVugg/colibri

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}huggingface-hub>0:misc/py-huggingface-hub@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}safetensors>0:misc/py-safetensors@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numpy>0:math/py-numpy@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}psutil>0:sysutils/py-psutil@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pytorch>0:misc/py-pytorch@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}datasets>0:misc/py-datasets@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}tokenizers>0:textproc/py-tokenizers@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}transformers>0:misc/py-transformers@${PY_FLAVOR}


USES=		gmake python shebangfix
USE_RC_SUBR=	${PORTNAME}

USE_GITHUB=	yes
GH_ACCOUNT=	JustVugg
GH_TAGNAME=	8a1dcca # dev branch with hot fixes

SHEBANG_FILES=	c/coli
SHEBANG_GLOB=	*.py

CFLAGS_EX=	${CFLAGS:S/O2/O3/} # colibri needs all CPU performance it can get, so we override the default optimization level. native build (CPUTYPE?=native in /etc/rc.config) is also recommended.

CFLAGS+=	-pthread -fopenmp # -fopenmp is for tests
LDFLAGS+=	-pthread -lm
MAKE_ARGS=	CC=${CC} \
		CFLAGS="${CFLAGS_EX}" \
		LDFLAGS="${LDFLAGS}"

TEST_TARGET=	test

# tests as of 2026-07-14:
# Ran 62 tests in 3.629s
# OK

.include <bsd.port.mk>

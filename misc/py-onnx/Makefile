PORTNAME=	onnx
DISTVERSION=	1.22.0
CATEGORIES=	misc # machine-learning
MASTER_SITES=	PYPI \
		https://github.com/abseil/abseil-cpp/archive/refs/tags/:abseil \
		https://github.com/protocolbuffers/protobuf/releases/download/v22.3/:protobuf # use downloaded protobuf-22.3
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTFILES=	${PORTNAME}-${DISTVERSION}${EXTRACT_SUFX} \
		20230125.3.tar.gz:abseil \
		protobuf-22.3.tar.gz:protobuf # use downloaded protobuf-22.3
DIST_SUBDIR=	onnx
EXTRACT_ONLY=	${PORTNAME}-${DISTVERSION}${EXTRACT_SUFX}

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Open Neural Network eXchange
WWW=		https://onnx.ai \
		https://github.com/onnx/onnx

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	bash:shells/bash \
		cmake:devel/cmake-core \
		protoc-gen-mypy:devel/py-mypy-protobuf@${PY_FLAVOR} \
		protoc:devel/protobuf \
		${PYTHON_PKGNAMEPREFIX}nanobind>0:devel/py-nanobind@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}scikit-build-core>0:devel/py-scikit-build-core@${PY_FLAVOR}
LIB_DEPENDS=	libprotobuf-lite.so:devel/protobuf
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}google-re2>0:devel/py-google-re2@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numpy>=1.16:math/py-numpy@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pillow>0:graphics/py-pillow@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}protobuf>=3.20.2:devel/py-protobuf@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}typing-extensions>=3.6.2.1:devel/py-typing-extensions@${PY_FLAVOR}
TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}parameterized>0:devel/py-parameterized@${PY_FLAVOR}

USES=		compiler:c++17-lang python shebangfix
USE_PYTHON=	pep517 concurrent autoplist pytest

CXXFLAGS+=	-Dstat64=stat
CMAKE_ARGS=	-DProtobuf_PROTOC_EXECUTABLE=${LOCALBASE}/bin/protoc

SHEBANG_FILES=	onnx/gen_proto.py

#CONFLICTS_BUILD=	protobuf # use downloaded protobuf-22.3

TEST_ENV=	${MAKE_ENV} PYTHONPATH=${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}
TEST_WRKSRC=	${WRKSRC}/onnx/test

BINARY_ALIAS=	python=${PYTHON_CMD}

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/onnx/onnx_cpp2py_export*.so

# tests as of 1.22.0: 1 failed, 6020 passed, 3970 skipped, 12 warnings in 16.90s

.include <bsd.port.mk>

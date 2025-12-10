PORTNAME=	numpy
PORTVERSION=	1.26.4
PORTREVISION=	11
PORTEPOCH=	1
CATEGORIES=	math python
MASTER_SITES=	PYPI \
		https://numpy.org/doc/1.26/:doc
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTFILES=	numpy-${PORTVERSION}${EXTRACT_SUFX} \
		numpy-html.zip:doc
DIST_SUBDIR=	numpy-${PORTVERSION:R}
EXTRACT_ONLY=	${DISTNAME}${EXTRACT_SUFX}

MAINTAINER=	python@FreeBSD.org
COMMENT=	The New Numeric Extension to Python
WWW=		https://www.numpy.org/

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	${PY_SETUPTOOLS} \
		${PYTHON_PKGNAMEPREFIX}meson-python>=0:devel/meson-python@${PY_FLAVOR}
TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}hypothesis>=6.24.1:devel/py-hypothesis@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pytest>=6.2.5:devel/py-pytest@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}typing-extensions>=4.2.0:devel/py-typing-extensions@${PY_FLAVOR}

USES=		compiler:c11 cpe pkgconfig python shebangfix
USE_PYTHON=	autoplist concurrent cython pep517

GCCLIBDIR_CMDS=	${FC} -print-file-name=libgfortran.so | ${SED} -e \
		s/libgfortran.so//
PYDISTUTILS_CONFIGUREARGS=	${PYFARGS}
PYDISTUTILS_BUILDARGS=	${PYFARGS}

LDFLAGS+=	-s
PIE_UNSAFE=	yes

PORTSCOUT=	limit:^1\.

PORTDOCS=	*

OPTIONS_DEFINE=		DOCS FORTRAN SUITESPARSE
OPTIONS_DEFAULT=	FORTRAN OPENBLAS SUITESPARSE
OPTIONS_SINGLE=		BLASLIB
OPTIONS_SINGLE_BLASLIB=	ATLAS NETLIB NOBLAS OPENBLAS
NOBLAS_DESC=		Internal NumPy fallback BLAS routines (slow!)
SUITESPARSE_DESC=	Use AMD and UMFPACK in SuiteSparse

ATLAS_IMPLIES=			FORTRAN
ATLAS_USES=			blaslapack:atlas
ATLAS_VARS=			BLASLIBS="ptf77blas, ptcblas" \
				BLASNAME=atlas \
				LAPACKLIBS=alapack \
				LIBRARIES=atlas_libs
FORTRAN_USES=			fortran
FORTRAN_VARS=			PYFARGS=--fcompiler=gnu95
NETLIB_IMPLIES=			FORTRAN
NETLIB_LIB_DEPENDS=		libcblas.so:math/cblas
NETLIB_USES=			blaslapack:netlib
NETLIB_VARS=			BLASLIBS="blas, cblas" \
				BLASNAME=atlas \
				LAPACKLIBS=lapack \
				LIBRARIES=atlas_libs
NOBLAS_MAKE_ENV=		NPY_LAPACK_ORDER= \
				PY_BLAS_ORDER=
OPENBLAS_IMPLIES=		FORTRAN
OPENBLAS_USES=			blaslapack:openblas
OPENBLAS_VARS=			BLASLIBS="openblas, gfortran" \
				BLASNAME=openblas \
				LAPACKLIBS="openblas, gfortran" \
				LIBRARIES=libraries
SUITESPARSE_IMPLIES=		FORTRAN
SUITESPARSE_LIB_DEPENDS=	libumfpack.so:math/suitesparse-umfpack

SHEBANG_FILES=	numpy/f2py/crackfortran.py numpy/f2py/f2py2e.py \
		numpy/f2py/rules.py numpy/testing/print_coercion_tables.py \
		numpy/testing/setup.py

post-extract:
	@${TOUCH} ${WRKSRC}/numpy/f2py/tests/src/temp
	@${TOUCH} ${WRKSRC}/numpy/random/_examples/temp
	@${TOUCH} ${WRKSRC}/numpy/core/tests/examples/temp

pre-configure:
	@${REINPLACE_CMD} -e 's|%%FC%%|${FC}|' ${WRKSRC}/numpy/distutils/fcompiler/gnu.py
	@${CP} ${FILESDIR}/site.cfg ${WRKSRC}/site.cfg

pre-configure-FORTRAN-on:
	@${REINPLACE_CMD} -e "s|%%GCCLIBDIR%%|$$(${GCCLIBDIR_CMDS})|" ${WRKSRC}/site.cfg ${WRKSRC}/numpy/distutils/system_info.py

pre-configure-NOBLAS-off:
	${REINPLACE_CMD} -e 's|%%LOCALBASE%%|${LOCALBASE}|g' \
		-e 's|%%BLASLIBS%%|${BLASLIBS}|; s|%%BLASNAME%%|${BLASNAME}|' \
		-e 's|%%LAPACKLIBS%%|${LAPACKLIBS}|; s|%%LIBRARIES%%|${LIBRARIES}|' \
			${WRKSRC}/site.cfg

pre-configure-SUITESPARSE-off:
	@${REINPLACE_CMD} -e 's|:%%LOCALBASE%%/include/suitesparse||' ${WRKSRC}/site.cfg

do-configure:

post-install:
	${FIND} ${STAGEDIR}${PYTHON_SITELIBDIR} -name '*.so' | ${XARGS} ${STRIP_CMD}

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${UNZIP_NATIVE_CMD} -qo ${DISTDIR}/${DIST_SUBDIR}/numpy-html.zip -d ${STAGEDIR}${DOCSDIR}
	@${RM} ${STAGEDIR}${DOCSDIR}/.buildinfo

do-test:
	@cd ${WRKSRC} && ${PYTHON_CMD} runtests.py

.include <bsd.port.mk>

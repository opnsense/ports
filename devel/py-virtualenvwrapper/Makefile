PORTNAME=	virtualenvwrapper
PORTVERSION=	6.1.1
CATEGORIES=	devel python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	nivit@FreeBSD.org
COMMENT=	Enhancements to virtualenv
WWW=		https://virtualenvwrapper.readthedocs.io/

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}setuptools>0:devel/py-setuptools@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}setuptools-scm>=6.2:devel/py-setuptools-scm@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}sphinx>=0,1:textproc/py-sphinx@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}wheel>0:devel/py-wheel@${PY_FLAVOR}
RUN_DEPENDS=	${LOCALBASE}/bin/bash:shells/bash \
		${PYTHON_PKGNAMEPREFIX}stevedore>0:devel/py-stevedore@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}virtualenv>0:devel/py-virtualenv@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}virtualenv-clone>0:devel/py-virtualenv-clone@${PY_FLAVOR}

# Actually 3.8-3.12
USES=		python
USE_PYTHON=	autoplist concurrent pep517

OPTIONS_DEFINE=	DOCS


DOCS_MAKE_ENV=	PYTHONPATH=${WRKSRC}
PLIST_FILES=	share/man/man1/virtualenvwrapper.1.gz
PORTDOCS=	*

NO_ARCH=	yes

post-patch:
	${REINPLACE_CMD} -e 's|%%LOCALBASE%%|${LOCALBASE}|' \
		${WRKSRC}/tox.ini

post-build:
	cd ${WRKSRC}/docs && ${SETENVI} ${MAKE_ENV} \
		${BSDMAKE} SPHINX_BUILD=${LOCALBASE}/bin/sphinx-build${UNIQUE_SUFFIX} man

post-build-DOCS-on:
	cd ${WRKSRC}/docs && ${SETENVI} ${MAKE_ENV} \
		${BSDMAKE} SPHINX_BUILD=${LOCALBASE}/bin/sphinx-build${UNIQUE_SUFFIX} html

post-install:
	${INSTALL_MAN} ${WRKSRC}/docs/build/man/virtualenvwrapper.1 \
		${STAGEDIR}${PREFIX}/share/man/man1

post-install-DOCS-on:
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	@cd ${WRKSRC}/docs/build/html && \
		${COPYTREE_SHARE} . ${STAGEDIR}${DOCSDIR} \
		"-not ( -name .buildinfo )"

.include <bsd.port.mk>

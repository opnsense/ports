PORTNAME=	click-threading
DISTVERSION=	0.5.0
PORTREVISION=	1
CATEGORIES=	devel python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Multithreaded Click apps made easy
WWW=		https://github.com/click-contrib/click-threading

LICENSE=	MIT

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}click>0:devel/py-click@${PY_FLAVOR}
TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}pytest>0:devel/py-pytest@${PY_FLAVOR} \
		${RUN_DEPENDS}

USES=		python
USE_PYTHON=	autoplist distutils
NO_ARCH=	yes

do-test:
	@cd ${WRKSRC} && ${PYTHON_CMD} -m pytest -rs -v

.include <bsd.port.mk>

PORTNAME=	quadprog
DISTVERSION=	0.1.13
PORTREVISION=	2
CATEGORIES=	math python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	stephen@FreeBSD.org
COMMENT=	Quadratic programming package
WWW=		https://pypi.org/project/quadprog/

LICENSE=	GPLv2+

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}numpy1>=1.2:math/py-numpy1@${PY_FLAVOR}

USES=		python
USE_PYTHON=	distutils autoplist cython

.include <bsd.port.mk>

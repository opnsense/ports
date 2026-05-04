PORTNAME=	pyModbusTCP
DISTVERSION=	0.3.0
PORTREVISION=	2
CATEGORIES=	comms python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	kiwi@FreeBSD.org
COMMENT=	Simple Modbus/TCP client library for Python
WWW=		https://github.com/sourceperl/pyModbusTCP

LICENSE=	MIT

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}numpy1>=1.16.0:math/py-numpy1@${PY_FLAVOR}

USES=		python
USE_PYTHON=	distutils autoplist

DOCSDIR=	${PREFIX}/share/doc/${PKGNAMEPREFIX}${PORTNAME}

NO_ARCH=	yes

PORTDOCS=	*

.include <bsd.port.mk>

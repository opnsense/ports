PORTNAME=	rednose
DISTVERSION=	1.3.0
PORTREVISION=	2
CATEGORIES=	devel python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	bofh@FreeBSD.org
COMMENT=	Coloured output for nosetests
WWW=		https://github.com/JBKahn/rednose

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENCE

DEPRECATED=		Depends on unmaintained nosetests
EXPIRATION_DATE=	2026-05-07

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}colorama>0:devel/py-colorama@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}termstyle>0:devel/py-termstyle@${PY_FLAVOR}

USES=		python
USE_PYTHON=	distutils autoplist

.include <bsd.port.mk>

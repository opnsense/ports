PORTNAME=	lightscope
DISTVERSION=	1.0
CATEGORIES=	security python
MASTER_SITES=	https://github.com/Thelightscope/lightscope/releases/download/v${DISTVERSION}/

MAINTAINER=	e@alumni.usc.edu
COMMENT=	Network security telescope and honeypot for cybersecurity research
WWW=		https://thelightscope.com

LICENSE=	BSD2CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}dpkt>=0:net/py-dpkt@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}requests>=0:www/py-requests@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}psutil>=0:sysutils/py-psutil@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pcapy-ng>=0:net/py-pcapy-ng@${PY_FLAVOR}

USES=		python shebangfix
SHEBANG_FILES=	*.py
NO_BUILD=	yes
NO_ARCH=	yes

SUB_FILES=	lightscope
SUB_LIST=	PYTHON_CMD=${PYTHON_CMD}

do-install:
	${MKDIR} ${STAGEDIR}${DATADIR}
	${INSTALL_SCRIPT} ${WRKSRC}/*.py ${STAGEDIR}${DATADIR}/
	${INSTALL_DATA} ${WRKSRC}/lightscope.conf.sample ${STAGEDIR}${PREFIX}/etc/
	${INSTALL_SCRIPT} ${WRKDIR}/lightscope ${STAGEDIR}${PREFIX}/bin/

.include <bsd.port.mk>

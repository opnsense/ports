PORTNAME=	tailor
DISTVERSION=	0.9.37
PORTREVISION=	2
CATEGORIES=	devel python

MAINTAINER=	portmaster@BSDforge.com
COMMENT=	Migrates changesets between version control systems
WWW=		https://gitlab.com/ports1/tailor/

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}future>0:devel/py-future@${PY_FLAVOR}
RUN_DEPENDS=	${LOCALBASE}/bin/rsync:net/rsync \
		${PYTHON_PKGNAMEPREFIX}future>0:devel/py-future@${PY_FLAVOR}

USES=		python
USE_PYTHON=	autoplist distutils
NO_ARCH=	yes

USE_GITLAB=	yes
GL_ACCOUNT=	ports1
GL_PROJECT=	tailor
GL_TAGNAME=	06d9068d84a4e78f30579fbdc46ed22ec9d953c7

OPTIONS_DEFINE=	DOCS

PORTDOCS=	README README.* DOC.*

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README* ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/DOC* ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>

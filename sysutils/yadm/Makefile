PORTNAME=	yadm
PORTVERSION=	3.3.0
CATEGORIES=	sysutils

MAINTAINER=	vendion@gmail.com
COMMENT=	Yet Another Dotfiles Manager
WWW=		https://yadm.io/

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	bash:shells/bash \
		git:devel/git

USES=		cpe
CPE_VENDOR=	${PORTNAME}_project
USE_GITHUB=	yes
GH_ACCOUNT=	yadm-dev

PLIST_FILES=	bin/yadm \
		share/man/man1/yadm.1.gz

OPTIONS_DEFINE=	J2CTL

J2CTL_DESC=		Enable Jinja2 powered template files
J2CTL_RUN_DEPENDS=	j2:textproc/py-j2cli@${PY_FLAVOR}
J2CTL_USES=		python

.include <bsd.port.options.mk>

do-install:
	@${MKDIR} ${STAGEDIR}
	${INSTALL_MAN} ${WRKSRC}/yadm.1 \
		${STAGEDIR}${PREFIX}/share/man/man1/
	${INSTALL_SCRIPT} ${WRKSRC}/yadm \
		${STAGEDIR}${PREFIX}/bin/

.include <bsd.port.mk>

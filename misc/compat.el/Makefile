PORTNAME=	compat.el
DISTVERSION=	30.1.0.1
PORTREVISION=	2
CATEGORIES=	misc elisp

MAINTAINER=	jrm@FreeBSD.org
COMMENT=	Compatibility library for Emacs Lisp
WWW=		https://github.com/emacs-compat/compat

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		emacs:build gmake makeinfo
USE_GITHUB=	yes
GH_ACCOUNT=	emacs-compat
GH_PROJECT=	compat

ALL_TARGET=	all compat.info

CONFLICTS_INSTALL=	compat.el-emacs_*

NO_ARCH=	yes
INFO=		compat
PORTDOCS=	NEWS.org README.md

OPTIONS_DEFINE=	DOCS

ELISP_FILES=	compat-25.el compat-26.el compat-27.el compat-28.el \
		compat-29.el compat-30.el compat-macs.el compat.el

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/${EMACS_SITE_LISPDIR}/compat
	${INSTALL_DATA}  ${ELISP_FILES:C/^/${WRKSRC}\//} \
		${STAGEDIR}${PREFIX}/${EMACS_SITE_LISPDIR}/compat
	${INSTALL_DATA} ${WRKSRC}/*.info ${STAGEDIR}${PREFIX}/${INFO_PATH}

do-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${PORTDOCS:C/^/${WRKSRC}\//} ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>

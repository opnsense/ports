PORTNAME=	transient
DISTVERSIONPREFIX=	v
DISTVERSION=	0.12.0
PORTREVISION=	1
CATEGORIES=	devel elisp

MAINTAINER=	freebsd@dev.thsi.be
COMMENT=	Emacs key and popup interface for complex keybindings
WWW=		https://github.com/magit/transient

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/LICENSE

_BR_DEPENDS=	compat.el>=30.1.0.0:misc/compat.el \
		cond-let>=0.2:devel/cond-let
BUILD_DEPENDS=	${_BR_DEPENDS}
RUN_DEPENDS=	${_BR_DEPENDS}

USES=		emacs:build gmake
USE_GITHUB=	yes
GH_ACCOUNT=	magit

MAKE_ENV=	LOAD_PATH="-L ${PREFIX}/${EMACS_SITE_LISPDIR}/compat \
			   -L ${PREFIX}/${EMACS_SITE_LISPDIR}"
MAKE_JOBS_UNSAFE=	yes
ALL_TARGET=	lisp

CONFLICTS_INSTALL=	transient-emacs_*

NO_ARCH=	yes

PLIST_FILES=	${EMACS_SITE_LISPDIR}/transient-autoloads.el \
		${EMACS_SITE_LISPDIR}/transient.el
PORTDOCS=	CHANGELOG README.org transient.html

OPTIONS_DEFINE=		DOCS INFO PDF
OPTIONS_DEFAULT=	INFO

PDF_DESC=	Build and install PDF document

DOCS_BUILD_DEPENDS=	gsed:textproc/gsed
DOCS_USES=		makeinfo
DOCS_ALL_TARGET=	html
DOCS_BINARY_ALIAS=	sed=gsed

INFO_BUILD_DEPENDS=	gsed:textproc/gsed
INFO_ALL_TARGET=	info
INFO_BINARY_ALIAS=	sed=gsed
INFO_INFO=		transient

PDF_BUILD_DEPENDS=	gsed:textproc/gsed \
			texi2pdf:print/texinfo
PDF_USES=		tex
PDF_USE=		TEX=dvipdfmx:build
PDF_ALL_TARGET=		pdf
PDF_BINARY_ALIAS=	sed=gsed
PDF_PLIST_FILES=	${DOCSDIR}/transient.pdf

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/${EMACS_SITE_LISPDIR}
	${INSTALL_DATA} ${WRKSRC}/lisp/*.el \
		${STAGEDIR}${PREFIX}/${EMACS_SITE_LISPDIR}

do-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README.org ${WRKSRC}/CHANGELOG \
		${WRKSRC}/docs/transient.html ${STAGEDIR}${DOCSDIR}

do-install-INFO-on:
	${INSTALL_DATA} ${WRKSRC}/docs/*.info \
		${STAGEDIR}${PREFIX}/${INFO_PATH}

do-install-PDF-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/docs/transient.pdf ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>

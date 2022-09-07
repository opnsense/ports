PORTNAME=	flowd
PORTVERSION=	0.9.1
PORTREVISION=	3
CATEGORIES=	net-mgmt
MASTER_SITES=	https://pkg.opnsense.org/distfiles

MAINTAINER=	franco@opnsense.org
COMMENT=	Small, fast, and secure NetFlow collector
WWW=		https://www.mindrot.org/projects/flowd/

LICENSE=	MIT BSD2CLAUSE BSD3CLAUSE
LICENSE_COMB=	multi
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		gmake shebangfix
SHEBANG_FILES=	tools/*.pl
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--localstatedir=/var
USE_RC_SUBR=	flowd
PORTDOCS=	README INSTALL

FLOWD_USER=	_flowd

USERS=		${FLOWD_USER}
GROUPS=		${FLOWD_USER}

OPTIONS_DEFINE=	DOCS EXAMPLES
OPTIONS_SUB=	yes

post-patch:
	@${REINPLACE_CMD} -e "s;%%FLOWD_USER%%;${FLOWD_USER};g" \
		${WRKSRC}/flowd.h

pre-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${PORTDOCS:S|^|${WRKSRC}/|} ${STAGEDIR}${DOCSDIR}

pre-install-EXAMPLES-on:
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	( cd ${WRKSRC}/tools && ${COPYTREE_SHARE} . ${STAGEDIR}${EXAMPLESDIR} )

.include <bsd.port.mk>

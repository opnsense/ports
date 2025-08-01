PORTNAME=	sqlite
PORTVERSION=	2.8.17
PORTREVISION=	5
CATEGORIES=	databases
MASTER_SITES=	http://www.sqlite.org/

MAINTAINER=	ports@FreeBSD.org
COMMENT=	SQL database engine in a C library
WWW=		https://www.sqlite.org/

GNU_CONFIGURE=	yes
USES=		cpe gmake libtool pkgconfig readline
USE_LDCONFIG=	yes

CONFIGURE_ARGS=	--with-hints=freebsd.hints

DOCSDIR=	${PREFIX}/share/doc/sqlite2
EXAMPLESDIR=	${PREFIX}/share/examples/sqlite2

EXTRACT_AFTER_ARGS=	--exclude CVS

OPTIONS_DEFINE=	TCL THREADS DOCS EXAMPLES

.if !exists(/usr/lib/libreadline.so)
MAKE_ARGS=	READLINE_FLAGS="-DHAVE_READLINE=1 -I${LOCALBASE}/include -L${LOCALBASE}/lib"
.endif

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MTCL}
USES+=		tcl
.else
.if ${PORT_OPTIONS:MDOCS}
USES+=		tcl:build
.endif
.endif

.if ${PORT_OPTIONS:MTCL}
CATEGORIES+=	lang tcl
COMMENT+=	with TCL wrapper
MAKE_ARGS+=	TCLSH=${TCLSH}
MAKE_ENV+=	TCL_VER=${TCL_VER}
PLIST_SUB+=	WITH_TCLWRAPPER=""
.else
PLIST_SUB+=	WITH_TCLWRAPPER="@comment "
.endif

.if ${PORT_OPTIONS:MDOCS}
ALL_TARGET=	all doc
PORTDOCS=	*
MAKE_ARGS+=	TCLSH=${TCLSH}
MAKE_ENV+=	TCL_VER=${TCL_VER}
.endif

post-patch:
	@${REINPLACE_CMD} -e "s/tclsh \$$(TOP)/\$$(TCLSH) \$$(TOP)/g" \
		${WRKSRC}/Makefile.in
.if ${PORT_OPTIONS:MTCL} || !empty(PORT_OPTIONS:MDOCS)
	@${ECHO} "config_TARGET_TCL_INC=\"-I${TCL_INCLUDEDIR}\"" \
		> ${WRKSRC}/freebsd.hints
	@${ECHO} "config_TARGET_TCL_LIBS=\"-L${PREFIX}/lib -ltcl${TCL_VER:S/.//}\"" \
		>> ${WRKSRC}/freebsd.hints
.else
	@${ECHO} "" > ${WRKSRC}/freebsd.hints
.endif

post-patch-THREADS-on:
	@${ECHO} "config_TARGET_CFLAGS=\"-DTHREADSAFE=1\"" \
		>> ${WRKSRC}/freebsd.hints
	@${ECHO} "config_TARGET_LIBS=\"-lpthread\"" \
		>> ${WRKSRC}/freebsd.hints

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/sqlite
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libsqlite.so

post-install-TCL-on:
	@(cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${MAKE_ARGS} install-tcl)
	${INSTALL_DATA} ${FILESDIR}/pkgIndex.tcl ${STAGEDIR}${PREFIX}/lib/sqlite

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/* ${STAGEDIR}${DOCSDIR}

post-install-EXAMPLES-on:
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	${INSTALL_DATA} ${FILESDIR}/example.tcl ${STAGEDIR}${EXAMPLESDIR}

.include <bsd.port.mk>

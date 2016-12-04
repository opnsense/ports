# Created by: Li-Wen Hsu <lwhsu@FreeBSD.org>
# $FreeBSD$

PORTNAME=	webgrind
DISTVERSION=	1.4.s${SNAPSHOT}
CATEGORIES=	www

MAINTAINER=	lwhsu@FreeBSD.org
COMMENT=	Xdebug Profiling Web Frontend in PHP

LICENSE=	BSD3CLAUSE

OPTIONS_DEFINE=	CALLGRAPH

USE_GITHUB=	yes
GH_ACCOUNT=	jokkedk
GH_TAGNAME=	9052998

SNAPSHOT=	20160723

USES=		php

NO_BUILD=	yes
NO_ARCH=	yes

PLIST_SUB=	WWWOWN="${WWWOWN}" WWWGRP="${WWWGRP}"

CALLGRAPH_USES=		python
CALLGRAPH_RUN_DEPENDS=	dot:graphics/graphviz

post-patch-CALLGRAPH-on:
	@${REINPLACE_CMD} -e 's,/usr/bin/python,${PYTHON_CMD},' ${WRKSRC}/config.php
	@${REINPLACE_CMD} -e 's,/usr/bin/dot,/usr/local/bin/dot,' ${WRKSRC}/config.php

do-install:
	@${MKDIR} ${STAGEDIR}${WWWDIR}
	(cd ${WRKSRC}/ && ${COPYTREE_SHARE} "*" ${STAGEDIR}${WWWDIR} "! -name *.bak")

.include <bsd.port.mk>

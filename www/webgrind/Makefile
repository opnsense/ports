# Created by: Li-Wen Hsu <lwhsu@FreeBSD.org>
# $FreeBSD$

PORTNAME=	webgrind
PORTVERSION=	1.4.0
DISTVERSIONPREFIX=v
CATEGORIES=	www

MAINTAINER=	lwhsu@FreeBSD.org
COMMENT=	Xdebug Profiling Web Frontend in PHP

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/license.txt

OPTIONS_DEFINE=	CALLGRAPH

USE_GITHUB=	yes
GH_ACCOUNT=	jokkedk

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

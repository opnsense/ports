PORTNAME=	ipfw-classifyd
PORTVERSION=	0.1
PORTREVISION=	1
CATEGORIES=	net
MASTER_SITES=	#
DISTFILES=	#

MAINTAINER=	franco@opnsense.org
COMMENT=	application classifier

extract:
	${MKDIR} -p ${WRKSRC}
	${CP} -r ${FILESDIR}/* ${WRKSRC}

post-stage:
	${CP} -r ${WRKSRC}/protocols ${STAGEDIR}${PREFIX}/share/

.include <bsd.port.mk>

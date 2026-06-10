PORTNAME=	filterlog
PORTVERSION=	0.8
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	Parse pflog(4) output

LICENSE=	BSD3CLAUSE

LIB_DEPENDS=	libpfctl.so:net/libpfctl

USES=		localbase

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

.include <bsd.port.mk>

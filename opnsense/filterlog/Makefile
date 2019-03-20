# $FreeBSD$

PORTNAME=	filterlog
PORTVERSION=	0.2
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	Parse pflog(4) output

LICENSE=	BSD3CLAUSE

USE_HARDENING=	safestack

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

.include <bsd.port.mk>

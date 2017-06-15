PORTNAME=	filterdns
PORTVERSION=	0.2
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	filterdns

LICENSE=	BSD2CLAUSE

USE_HARDENING=	pie relro safestack

PLIST_FILES=    sbin/filterdns

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

.include <bsd.port.mk>

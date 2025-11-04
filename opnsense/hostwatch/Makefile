PORTNAME=	hostwatch
PORTVERSION=	1.0.2
PORTREVISION=	1
CATEGORIES=	security
DISTFILES=

MAINTAINER=	ad@opnsense.org
COMMENT=	Host discovery daemon

LICENSE=	BSD2CLAUSE

USES=		cargo

PLIST_FILES=	bin/hostwatch

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
GH_TAGNAME=	1.0.2

USE_RC_SUBR=	${PORTNAME}

# use hostd as this user/group already has a port registration for another service we don't uses
USERS= 		hostd
GROUPS=		hostd


.include <bsd.port.mk>

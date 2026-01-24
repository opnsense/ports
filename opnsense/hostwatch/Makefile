PORTNAME=	hostwatch
PORTVERSION=	1.0.9
CATEGORIES=	security
DISTFILES=

MAINTAINER=	ad@opnsense.org
COMMENT=	Host discovery daemon

LICENSE=	BSD2CLAUSE

USES=		cargo

PLIST_FILES=	bin/hostwatch

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense

USE_RC_SUBR=	${PORTNAME}

# use this user/group as it already has a port registration
USERS=		hostd
GROUPS=		hostd

.include <bsd.port.mk>

PORTNAME=	pam
PORTVERSION=	24.1
CATEGORIES=	sysutils
PKGNAMESUFFIX=	_${GH_ACCOUNT}

MAINTAINER=	ad@opnsense.org
COMMENT=	OPNsense shared authentication system using PAM

LICENSE=	BSD2CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense

post-stage:
	${RM} ${STAGEDIR}${PREFIX}/lib/*.a

.include <bsd.port.mk>

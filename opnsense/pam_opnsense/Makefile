PORTNAME=	pam_opnsense
PORTVERSION=	19.1.3
CATEGORIES=	sysutils

PATCH_SITES=	https://github.com/${GH_ACCOUNT}/${PORTNAME}/commit/
PATCHFILES=	0eff045.patch:-p1 19d56c1.patch:-p1

MAINTAINER=	ad@opnsense.org
COMMENT=	OPNsense shared authentication system using PAM

LICENSE=	BSD2CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense

post-stage:
	${RM} ${STAGEDIR}${PREFIX}/lib/*.a

.include <bsd.port.mk>

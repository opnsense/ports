# Created by: Ad Schellevis <ad@opnsense.org>
# $FreeBSD$

PORTNAME=	pam_opnsense
PORTVERSION=	17.1
PORTREVISION=	1 # GH_TAGNAME
CATEGORIES=	sysutils

MAINTAINER=	ad@opnsense.org
COMMENT=	OPNsense shared authentication system using PAM

LICENSE=	BSD2CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense
GH_TAGNAME=	8ca6abd

post-stage:
	${RM} ${STAGEDIR}${PREFIX}/lib/*.a

.include <bsd.port.mk>

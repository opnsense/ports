PORTNAME=	update
PORTVERSION=	22.1.9
CATEGORIES=	sysutils
PKGNAMEPREFIX=	${GH_ACCOUNT}-

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense update utilities

LICENSE=	BSD2CLAUSE

LIB_DEPENDS+=	libucl.so:textproc/libucl

USES=		ssl

MAKE_ENV=	UPDATE_RELEASE=${PORTVERSION}

USE_GITHUB=	yes
GH_ACCOUNT=	${CATEGORIES:[1]}
GH_TAGNAME=	7f6e385

.include <bsd.port.mk>

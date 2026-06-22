PORTNAME=	installer
.if "${PRODUCT_ABI}" == "26.7"
PORTVERSION=	26.7.d
.else
PORTVERSION=	25.1
PORTREVISION=	2
.endif
CATEGORIES=	sysutils
PKGNAMEPREFIX=	${GH_ACCOUNT}-

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense installer scripts
WWW=		https://github.com/opnsense/installer

LICENSE=	BSD2CLAUSE

RUN_DEPENDS=	cpdup:sysutils/cpdup
PREFIX=		/usr

NO_ARCH=	yes
NO_BUILD=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	${CATEGORIES:[1]}
.if "${PRODUCT_ABI}" == "26.7"
GH_TAGNAME=	e3b3e5f
.else
GH_TAGNAME=	9061457
.endif

.include <bsd.port.mk>

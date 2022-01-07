PORTNAME=	installer
.if "${PRODUCT_ABI}" == 22.1
PORTVERSION=	22.1.d
.else
PORTVERSION=	21.7.1
.endif
CATEGORIES=	sysutils
PKGNAMEPREFIX=	${GH_ACCOUNT}-

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense installer scripts

LICENSE=	BSD2CLAUSE

RUN_DEPENDS=	cpdup:sysutils/cpdup
PREFIX=		/usr

NO_ARCH=	yes
NO_BUILD=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	${CATEGORIES:[1]}
.if "${PRODUCT_ABI}" == 22.1
GH_TAGNAME=	8d01b88
.endif

.include <bsd.port.mk>

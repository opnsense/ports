PORTNAME=	bzip3
DISTVERSION=	1.5.2
CATEGORIES=	archivers
MASTER_SITES=	https://github.com/kspalaiologos/${PORTNAME}/releases/download/${DISTVERSION}/

MAINTAINER=	ehaupt@FreeBSD.org
COMMENT=	Better and stronger spiritual successor to BZip2
WWW=		https://github.com/kspalaiologos/bzip3

LICENSE=	APACHE20 BSD2CLAUSE LGPL3+
LICENSE_COMB=	multi
LICENSE_FILE_APACHE20=	${WRKSRC}/3rdparty/libsais-LICENSE
LICENSE_FILE_LGPL3+ =	${WRKSRC}/LICENSE

USES=		cmake cpe tar:xz
CPE_VENDOR=	bzip3_project
USE_LDCONFIG=	yes

.include <bsd.port.mk>

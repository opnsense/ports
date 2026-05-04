PORTNAME=	rubygems-generate_index
PORTVERSION=	1.1.3
CATEGORIES=	devel rubygems
MASTER_SITES=	RG

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Generate the index files for a gem server directory
WWW=		https://github.com/rubygems/rubygems-generate_index

LICENSE=	MIT RUBY
LICENSE_COMB=	dual
LICENSE_FILE_MIT=	${WRKSRC}/MIT.txt
LICENSE_FILE_RUBY=	${WRKSRC}/LICENSE.txt

RUN_DEPENDS=	rubygem-compact_index>=0.15.0<0.16:devel/rubygem-compact_index

USES=		gem

NO_ARCH=	yes

.include <bsd.port.mk>

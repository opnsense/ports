PORTNAME=	railties
PORTVERSION=	7.0.8.7
CATEGORIES=	www rubygems
MASTER_SITES=	RG
PKGNAMESUFFIX=	70

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Rails internals: application bootup, plugins, generators, and rake tasks
WWW=		https://github.com/rails/rails/tree/master/railties \
		https://rubyonrails.org/

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/MIT-LICENSE

RUN_DEPENDS=	rubygem-actionpack70>=${PORTVERSION}<${PORTVERSION}_99:www/rubygem-actionpack70 \
		rubygem-activesupport70>=${PORTVERSION}<${PORTVERSION}_99:devel/rubygem-activesupport70 \
		rubygem-method_source>=0:devel/rubygem-method_source \
		rubygem-rake>=12.2:devel/rubygem-rake \
		rubygem-thor>=1.0<2:devel/rubygem-thor \
		rubygem-zeitwerk>=2.5<3:devel/rubygem-zeitwerk

USES=		gem

NO_ARCH=	yes

PLIST_FILES=	bin/rails

CONFLICTS_INSTALL=	rubygem-railties[0-9] rubygem-railties[0-9][0-9]

PORTSCOUT=	limit:^7\.0\.

.include <bsd.port.mk>

PORTNAME=	Chart-Clicker
PORTVERSION=	2.90
PORTREVISION=	2
CATEGORIES=	graphics perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	perl@FreeBSD.org
COMMENT=	Powerful, extensible charting
WWW=		https://metacpan.org/release/Chart-Clicker

LICENSE=	ART10 GPLv1+
LICENSE_COMB=	dual
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Color-Scheme>=0:graphics/p5-Color-Scheme \
		p5-Moose>=0:devel/p5-Moose \
		p5-DateTime>=0:devel/p5-DateTime \
		p5-DateTime-Set>=0:devel/p5-DateTime-Set \
		p5-Geometry-Primitive>=0:graphics/p5-Geometry-Primitive \
		p5-Graphics-Color>=0:graphics/p5-Graphics-Color \
		p5-Graphics-Primitive>=0:graphics/p5-Graphics-Primitive \
		p5-Graphics-Primitive-Driver-Cairo>=0:graphics/p5-Graphics-Primitive-Driver-Cairo \
		p5-Layout-Manager>=0:graphics/p5-Layout-Manager
TEST_DEPENDS=	p5-Test-Exception>=0:devel/p5-Test-Exception \
		p5-Test-Fatal>=0:devel/p5-Test-Fatal \
		p5-Test-Pod>=1:devel/p5-Test-Pod

NO_ARCH=	yes
USES=		perl5
USE_PERL5=	configure

.include <bsd.port.mk>

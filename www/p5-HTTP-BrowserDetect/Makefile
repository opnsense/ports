PORTNAME=	HTTP-BrowserDetect
PORTVERSION=	3.41
CATEGORIES=	www perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	perl@FreeBSD.org
COMMENT=	Determine the Web browser, version, OS from an HTTP user agent string
WWW=		https://metacpan.org/release/HTTP-BrowserDetect

LICENSE=	ART10 GPLv1+
LICENSE_COMB=	dual
LICENSE_FILE_GPLv1+ =	${WRKSRC}/LICENSE

TEST_DEPENDS=	p5-Path-Tiny>=0:devel/p5-Path-Tiny \
		p5-Test-Differences>=0:devel/p5-Test-Differences \
		p5-Test-NoWarnings>=0:devel/p5-Test-NoWarnings \
		p5-Test-Warnings>=0:devel/p5-Test-Warnings

USES=		perl5
USE_PERL5=	configure

NO_ARCH=	yes

.include <bsd.port.mk>

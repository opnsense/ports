PORTNAME=	libwww
PORTVERSION=	6.79
DISTVERSIONPREFIX=	perl-
CATEGORIES=	www devel perl5
MASTER_SITES=	CPAN
MASTER_SITE_SUBDIR=	CPAN:OALDERS
PKGNAMEPREFIX=	p5-

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Perl5 library for WWW access
WWW=		https://metacpan.org/release/libwww-perl

LICENSE=	ART10 GPLv1+
LICENSE_COMB=	dual
LICENSE_FILE_GPLv1+ =	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Authen-NTLM>=1.02:security/p5-Authen-NTLM \
		p5-Encode-Locale>=0:converters/p5-Encode-Locale \
		p5-File-Listing>=6:sysutils/p5-File-Listing \
		p5-HTML-Parser>=3.71:www/p5-HTML-Parser \
		p5-HTTP-Cookies>=6:www/p5-HTTP-Cookies \
		p5-HTTP-Date>=6:www/p5-HTTP-Date \
		p5-HTTP-Message>=6.18:www/p5-HTTP-Message \
		p5-HTTP-Negotiate>=6:www/p5-HTTP-Negotiate \
		p5-LWP-MediaTypes>=6:www/p5-LWP-MediaTypes \
		p5-Net-HTTP>=6.18:net/p5-Net-HTTP \
		p5-Try-Tiny>=0:lang/p5-Try-Tiny \
		p5-URI>=1.10:net/p5-URI \
		p5-WWW-RobotRules>=6:www/p5-WWW-RobotRules
TEST_DEPENDS=	p5-HTTP-CookieJar>=0:www/p5-HTTP-CookieJar \
		p5-HTTP-Daemon>=6.12:www/p5-HTTP-Daemon \
		p5-Test-Fatal>=0:devel/p5-Test-Fatal \
		p5-Test-Needs>=0:devel/p5-Test-Needs \
		p5-Test-RequiresInternet>=0:devel/p5-Test-RequiresInternet

USES=		perl5
USE_PERL5=	configure

CONFIGURE_ARGS=	--aliases
NO_ARCH=	yes

.include <bsd.port.mk>

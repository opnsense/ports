PORTNAME=	Shell-Guess
PORTVERSION=	0.10
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	perl@FreeBSD.org
COMMENT=	Make an educated guess about the shell in use
WWW=		https://metacpan.org/pod/Shell::Guess

LICENSE=	ART10 GPLv1+
LICENSE_COMB=	dual
LICENSE_FILE_GPLv1+ =	${WRKSRC}/LICENSE

USES=		perl5
USE_PERL5=	configure

NO_ARCH=	yes

PLIST_FILES=	${SITE_PERL_REL}/Shell/Guess.pm \
		${SITE_MAN3_REL}/Shell::Guess.3.gz

.include <bsd.port.mk>

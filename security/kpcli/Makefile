PORTNAME=	kpcli
PORTVERSION=	3.1
PORTREVISION=	2
CATEGORIES=	security
MASTER_SITES=	SF/kpcli/
EXTRACT_SUFX=	.pl

MAINTAINER=	alexander.4mail@gmail.com
COMMENT=	Command line interface to KeePassX and KeePass database files
WWW=		http://kpcli.sourceforge.net/

LICENSE=	ART10 GPLv1+
LICENSE_COMB=	dual

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Crypt-Rijndael>=1.08:security/p5-Crypt-Rijndael \
		p5-Term-ReadKey>=2.30:devel/p5-Term-ReadKey \
		p5-Sort-Naturally>=1.02:textproc/p5-Sort-Naturally \
		p5-File-KeePass>=2.03:security/p5-File-KeePass \
		p5-Term-ShellUI>=0.9:shells/p5-Term-ShellUI \
		p5-Term-ReadLine-Gnu>=1.19:devel/p5-Term-ReadLine-Gnu \
		p5-Data-Password>=0:security/p5-Data-Password \
		p5-Clone>=0.31:devel/p5-Clone \
		p5-Capture-Tiny>=0:devel/p5-Capture-Tiny \
		p5-Clipboard>=0:x11/p5-Clipboard \
		p5-Math-Random-ISAAC>=1.0.1:math/p5-Math-Random-ISAAC

USES=		perl5 shebangfix
SHEBANG_FILES=	kpcli
PLIST_FILES=	bin/kpcli share/man/man1/${PORTNAME}.1.gz
NO_ARCH=	yes

OPTIONS_DEFINE=		PWSAFE3
PWSAFE3_DESC=		Password Safe V3 file importing
PWSAFE3_BUILD_DEPENDS+=	p5-Crypt-PWSafe3>=1.21:security/p5-Crypt-PWSafe3
PWSAFE3_RUN_DEPENDS+=	p5-Crypt-PWSafe3>=1.21:security/p5-Crypt-PWSafe3

do-extract:
	@${MKDIR} ${WRKSRC}
	${CP} ${DISTDIR}/${PORTNAME}-${PORTVERSION}.pl ${WRKSRC}/${PORTNAME}

do-build:
	${LOCALBASE}/bin/pod2man ${WRKSRC}/${PORTNAME} ${WRKSRC}/${PORTNAME}.1

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/${PORTNAME}.1 ${STAGEDIR}${PREFIX}/share/man/man1

.include <bsd.port.mk>

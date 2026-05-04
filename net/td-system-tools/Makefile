PORTNAME=	td-system-tools
DISTVERSION=	2.4.2
CATEGORIES=	net
MASTER_SITES=	https://www.nntb.no/~dreibh/system-tools/download/

MAINTAINER=	thomas.dreibholz@gmail.com
COMMENT=	Printing basic system information and system maintenance
WWW=		https://www.nntb.no/~dreibh/system-tools/

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

RUN_DEPENDS=	bash:shells/bash \
		figlet:misc/figlet \
		getopt>=0:misc/getopt \
		mbuffer:misc/mbuffer

USES=		cmake gettext python shebangfix ssl:run tar:xz

SHEBANG_FILES=	src/X509/generate-test-certificates

CMAKE_ARGS=	-DCMAKE_INSTALL_MANDIR=${PREFIX}/share/man

.include <bsd.port.mk>

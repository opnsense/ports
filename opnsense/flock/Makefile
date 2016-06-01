# Created by: netch@netch.kiev.ua
# $FreeBSD$

PORTNAME=	flock
PORTVERSION=	2.28
CATEGORIES=	sysutils
MASTER_SITES=	KERNEL_ORG/linux/utils/util-linux/v${PORTVERSION}/
DISTNAME=	util-linux-${PORTVERSION}

MAINTAINER=	franco@opnsense.org
COMMENT=	Manage locks from shell scripts

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

GNU_CONFIGURE=	yes
USES=		autoreconf

PLIST_FILES=	bin/flock man/man1/flock.1.gz

do-build:
	# skip building unneeded utils
	${MAKE} -C ${WRKSRC} flock

do-install:
	${INSTALL} ${WRKSRC}/flock ${STAGEDIR}${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/sys-utils/flock.1 \
	    ${STAGEDIR}${MANPREFIX}/man/man1

.include <bsd.port.mk>

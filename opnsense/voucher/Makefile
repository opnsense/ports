# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	voucher
PORTVERSION=	0.1
PORTREVISION=	4
CATEGORIES=	sysutils
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	voucher support

USE_OPENSSL=	yes
CFLAGS+=	-I${OPENSSLINC}
LDFLAGS+=	-L${OPENSSLLIB}

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

.include <bsd.port.mk>

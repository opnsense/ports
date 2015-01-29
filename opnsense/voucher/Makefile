PORTNAME=	voucher
PORTVERSION=	0.1
PORTREVISION=	4
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER?=	franco@opnsense.org
COMMENT?=	voucher support

USE_OPENSSL=	yes

do-extract:
	mkdir -p ${WRKSRC}

CFLAGS+=	-I${OPENSSLINC}
LDFLAGS+=	-L${OPENSSLLIB}

do-build:
	${CC} ${CFLAGS} -o ${WRKSRC}/${PORTNAME} \
	     ${LDFLAGS} -lcrypto ${FILESDIR}/voucher.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/voucher ${STAGEDIR}${PREFIX}/bin/

.include <bsd.port.mk>

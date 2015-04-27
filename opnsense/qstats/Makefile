PORTNAME=	qstats
PORTVERSION=	0.2
PORTREVISION=	0
CATEGORIES?=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER?=	franco@opnsense.org
COMMENT?=	read QoS data

CFLAGS+=	-lsbuf
PLIST_FILES=    sbin/qstats

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -o ${WRKSRC}/qstats ${FILESDIR}/pfctl_qstats.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/qstats ${STAGEDIR}${PREFIX}/sbin

.include <bsd.port.mk>

PORTNAME=	sshlockout_pf
PORTVERSION=	0.0.2
PORTREVISION=	2
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	Automatically block IPs with failed SSH logins using pf(4)

OPTIONS_DEFINE= WEBCF
OPTIONS_DEFAULT= WEBCF

WEBCF_DESC=     Enable webConfigurator support

WEBCF_CFLAGS=           -DWEBCF

PLIST_FILES=    sbin/sshlockout_pf

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -Wall -lpthread -o ${WRKSRC}/${PORTNAME} \
	    ${FILESDIR}/sshlockout_pf.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} \
		${STAGEDIR}${PREFIX}/sbin/

.include <bsd.port.mk>

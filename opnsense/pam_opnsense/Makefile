PORTNAME=	pam_opnsense
PORTVERSION=	16.7.b
PORTREVISION=	1
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	ad@opnsense.org
COMMENT=	OPNsense shared authentication system using PAM

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -Wall -lpam -o ${WRKSRC}/opnsense-auth-test \
	    ${WRKSRC}/opnsense-auth-test.c
	${CC} ${CFLAGS} -Wall -fPIC -o ${WRKSRC}/pam_opnsense.o \
	    -c ${WRKSRC}/pam_opnsense.c
	${LD} -x --shared -o ${WRKSRC}/pam_opnsense.so \
	    ${WRKSRC}/pam_opnsense.o

do-install:
	${INSTALL_DATA} ${WRKSRC}/opnsense-auth-test \
	    ${STAGEDIR}${PREFIX}/etc/pam.d
	${INSTALL_PROGRAM} ${WRKSRC}/opnsense-auth-test \
	    ${STAGEDIR}${PREFIX}/sbin
	${INSTALL_LIB} ${WRKSRC}/pam_opnsense.so \
	    ${STAGEDIR}${PREFIX}/lib

.include <bsd.port.mk>

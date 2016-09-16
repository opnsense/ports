PORTNAME=	pam_opnsense
PORTVERSION=	16.7.b
PORTREVISION=	3
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	ad@opnsense.org
COMMENT=	OPNsense shared authentication system using PAM

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -Wall -lpam -o ${WRKSRC}/bin/opnsense-auth-test \
	    ${WRKSRC}/bin/opnsense-auth-test.c
	${CC} ${CFLAGS} -Wall -fPIC -o ${WRKSRC}/lib/pam_opnsense.o \
	    -c ${WRKSRC}/lib/pam_opnsense.c
	${LD} -x --shared -o ${WRKSRC}/lib/pam_opnsense.so \
	    ${WRKSRC}/lib/pam_opnsense.o

do-install:
	${INSTALL_DATA} ${WRKSRC}/etc/opnsense-auth-test \
	    ${STAGEDIR}${PREFIX}/etc/pam.d
	${INSTALL_PROGRAM} ${WRKSRC}/bin/opnsense-auth-test \
	    ${STAGEDIR}${PREFIX}/sbin
	${INSTALL_LIB} ${WRKSRC}/lib/pam_opnsense.so \
	    ${STAGEDIR}${PREFIX}/lib

.include <bsd.port.mk>

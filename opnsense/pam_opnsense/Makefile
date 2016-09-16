PORTNAME=	pam_opnsense
PORTVERSION=	16.7.b
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	ad@opnsense.org
COMMENT=	OPNsense shared authentication system using PAM

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	mkdir -p ${WRKSRC}/sbin
	mkdir -p ${WRKSRC}/lib
	${CC} ${CFLAGS} -Wall -lpam -o ${WRKSRC}/opnsense-pam-auth-test \
	    ${MASTERDIR}/opnsense-pam-auth-test.c
	
	${CC} ${CFLAGS} -Wall -fPIC -o ${WRKSRC}/opnsense-pam-auth.o -c ${MASTERDIR}/opnsense-pam-auth.c
	${LD} -x --shared -o ${WRKSRC}/opnsense-pam-auth.so ${WRKSRC}/opnsense-pam-auth.o
	cp ${MASTERDIR}/opnsense-pam-service-test  ${WRKSRC}/opnsense-pam-service-test

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/opnsense-pam-auth-test ${STAGEDIR}${PREFIX}/sbin/
	${INSTALL_PROGRAM} ${WRKSRC}/opnsense-pam-auth.so ${STAGEDIR}${PREFIX}/lib/
	${INSTALL_DATA} ${WRKSRC}/opnsense-pam-service-test ${STAGEDIR}${PREFIX}/etc/pam.d/

.include <bsd.port.mk>

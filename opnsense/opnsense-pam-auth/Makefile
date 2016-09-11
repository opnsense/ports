PORTNAME=	opnsense-pam-auth
PORTVERSION=	0.0.1
PORTREVISION=	1
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	ad@opnsense.org
COMMENT=	Wrapper to support the opnsense shared authentication system using PAM

PLIST_FILES=    sbin/opnsense-pam-auth-test lib/opnsense-pam-auth.so sbin/opnsense-auth etc/pam.d/opnsense-pam-service-test

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	mkdir -p ${WRKSRC}/sbin
	mkdir -p ${WRKSRC}/lib
	${CC} ${CFLAGS} -Wall -lpam -o ${WRKSRC}/opnsense-pam-auth-test \
	    ${MASTERDIR}/opnsense-pam-auth-test.c
	
	${CC} ${CFLAGS} -Wall -fPIC -o ${WRKSRC}/opnsense-pam-auth.o -c ${MASTERDIR}/opnsense-pam-auth.c
	${LD} -x --shared -o ${WRKSRC}/opnsense-pam-auth.so ${WRKSRC}/opnsense-pam-auth.o
	cp ${MASTERDIR}/opnsense-auth ${WRKSRC}/opnsense-auth
	chmod 700 ${WRKSRC}/opnsense-auth
	cp ${MASTERDIR}/opnsense-pam-service-test  ${WRKSRC}/opnsense-pam-service-test

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/opnsense-pam-auth-test ${STAGEDIR}${PREFIX}/sbin/
	${INSTALL_PROGRAM} ${WRKSRC}/opnsense-pam-auth.so ${STAGEDIR}${PREFIX}/lib/
	${INSTALL_SCRIPT} ${WRKSRC}/opnsense-auth ${STAGEDIR}${PREFIX}/sbin/
	${INSTALL_DATA} ${WRKSRC}/opnsense-pam-service-test ${STAGEDIR}${PREFIX}/etc/pam.d/

.include <bsd.port.mk>

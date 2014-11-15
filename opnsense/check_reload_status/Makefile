PORTNAME=	check_reload_status
PORTVERSION=	0.0.3
PORTREVISION?=	1
CATEGORIES?=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER?=	franco@lastsummer.de
COMMENT?=	run various pfSense scripts on event.

PLIST_FILES=    sbin/check_reload_status sbin/pfSctl sbin/fcgicli
CFLAGS+=	-I/usr/local/include -L/usr/local/lib 

CFLAGS+=	-Wsystem-headers -Werror -Wall -Wno-format-y2k -W \
                -Wno-unused-parameter -Wstrict-prototypes \
                -Wmissing-prototypes -Wpointer-arith -Wreturn-type \
                -Wcast-qual -Wwrite-strings -Wswitch -Wshadow \
                -Wunused-parameter -Wchar-subscripts -Winline \
                -Wnested-externs -Wredundant-decls -Wno-pointer-sign

LIB_DEPENDS=	libevent.so:${PORTSDIR}/devel/libevent2

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -lsbuf -levent -o ${WRKSRC}/${PORTNAME} ${FILESDIR}/check_reload_status.c
	${CC} ${CFLAGS} -o ${WRKSRC}/pfSctl ${FILESDIR}/pfSctl.c
	${CC} ${CFLAGS} -lsbuf -o ${WRKSRC}/fcgicli ${FILESDIR}/fcgicli.c
	

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/check_reload_status ${STAGEDIR}${PREFIX}/sbin/
	${INSTALL_PROGRAM} ${WRKSRC}/pfSctl ${STAGEDIR}${PREFIX}/sbin/
	${INSTALL_PROGRAM} ${WRKSRC}/fcgicli ${STAGEDIR}${PREFIX}/sbin/

.include <bsd.port.mk>

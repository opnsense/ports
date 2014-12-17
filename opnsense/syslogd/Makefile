PORTNAME=	syslogd
PORTVERSION=	10.0
PORTREVISION=	1
CATEGORIES=	sysutils
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	FreeBSD syslogd with clog and zmq additions

LIB_DEPENDS=	libczmq.so:${PORTSDIR}/net/czmq
CFLAGS+=	-DWITH_ZMQ -I/usr/local/include -DINET6
LDFLAGS+=	-lczmq -lzmq -lpthread -lstdc++
LDFLAGS+=	-L/usr/local/lib

RUN_DEPENDS=	clog:${PORTSDIR}/opnsense/clog

# apply in order
EXTRA_PATCHES+=	${PATCHDIR}/clog-support.diff
EXTRA_PATCHES+=	${PATCHDIR}/zmq-support.diff

do-extract:
	cp -r ${FILESDIR}/src ${WRKSRC}

.include <bsd.port.mk>

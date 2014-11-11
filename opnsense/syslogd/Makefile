PORTNAME=	syslogd
PORTVERSION=	222550
PORTREVISION=	4
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTNAME=	${PORTNAME}-r${PORTVERSION}

MAINTAINER=	franco@lastsummer.de
COMMENT=	FreeBSD syslogd with clog and zmq additions

LIB_DEPENDS=	czmq:${PORTSDIR}/net/czmq
RUN_DEPENDS=	clog:${PORTSDIR}/opnsense/clog

DISTDIR=	${FILESDIR}
PLIST_FILES=	sbin/syslogd

# apply in order
EXTRA_PATCHES+=	${PATCHDIR}/clog-support.diff
EXTRA_PATCHES+=	${PATCHDIR}/zmq-support.diff

do-fetch:

post-patch:
	@${SED} -i '' -e 's|%%PREFIX%%|${PREFIX}|g' \
		-e 's|%%LOCALBASE%%|${LOCALBASE}|g' ${WRKSRC}/Makefile

.include <bsd.port.mk>

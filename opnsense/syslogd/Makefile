# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	syslogd
PORTVERSION=	10.2
CATEGORIES=	sysutils
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	FreeBSD syslogd with additions

OPTIONS_DEFINE=	CLOG INET6
OPTIONS_DEFAULT=CLOG INET6

CLOG_DESC=	Enable clog(1) support
INET6_DESC=	Enable IPv6 support

CLOG_EXTRA_PATCHES=	${PATCHDIR}/extra-clog-support.diff
CLOG_BUILD_DEPENDS=	${LOCALBASE}/include/clog.h:opnsense/clog
CLOG_RUN_DEPENDS=	clog:opnsense/clog
CLOG_CFLAGS=		-I${LOCALBASE}/include

INET6_CFLAGS=		-DINET6

do-extract:
	${CP} -r ${FILESDIR}/src ${WRKSRC}

.include <bsd.port.mk>

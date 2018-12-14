# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	syslogd
PORTVERSION=	11.2
CATEGORIES=	sysutils
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	FreeBSD syslogd with additions

LICENSE=	BSD3CLAUSE

USE_HARDENING=	safestack

OPTIONS_DEFINE=	CLOG IPV6
OPTIONS_DEFAULT=CLOG

CLOG_DESC=	Enable clog(1) support

CLOG_EXTRA_PATCHES=	${PATCHDIR}/extra-clog-support.diff
CLOG_BUILD_DEPENDS=	${LOCALBASE}/include/clog.h:opnsense/clog
CLOG_RUN_DEPENDS=	clog:opnsense/clog
CLOG_USES=		localbase

IPV6_CFLAGS=		-DINET6

MAKE_ENV=		SRCTOP=${.CURDIR}/files/src \
			MK_INET6_SUPPORT=no

do-extract:
	${CP} -r ${FILESDIR}/src ${WRKSRC}

.include <bsd.port.mk>

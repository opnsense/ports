# $FreeBSD$

PORTNAME=	syslogd
PKGNAMESUFFIX=	-devel
PORTVERSION=	12.1.d
CATEGORIES=	sysutils
DISTFILES=

MAINTAINER=	franco@opnsense.org
COMMENT=	FreeBSD syslogd with additions

LICENSE=	BSD3CLAUSE

USE_HARDENING=	safestack

OPTIONS_DEFINE=	CLOG
OPTIONS_DEFAULT=CLOG

CLOG_DESC=	Enable clog(1) support

CLOG_EXTRA_PATCHES=	${PATCHDIR}/extra-clog-support.diff
CLOG_BUILD_DEPENDS=	${LOCALBASE}/include/clog.h:opnsense/clog
CLOG_RUN_DEPENDS=	clog:opnsense/clog
CLOG_USES=		localbase

MAKE_ENV=	SRCTOP=${WRKSRC} \
		MANDIR=${PREFIX}/man/man \
		BINDIR=${PREFIX}/sbin \
		MK_FTP=no MK_PPP=no MK_LPR=no \
		MK_INET_SUPPORT=yes \
		MK_INET6_SUPPORT=yes

do-extract:
	${CP} -r ${FILESDIR}/src ${WRKSRC}

.include <bsd.port.mk>

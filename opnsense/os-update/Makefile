# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	os-update
PORTVERSION=	15.7.8
PORTREVISION=	0
CATEGORIES=	sysutils
DISTFILES=	# none

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense update utility

LICENSE=	BSD2CLAUSE

SUB_FILES=	opnsense-update.sh
SUB_LIST+=	VERSION="${PORTVERSION}" MIRROR="http://pkg.opnsense.org" \
		MARKER="${LOCALBASE}/opnsense/version/opnsense-update" \
		ORIGIN="${LOCALBASE}/etc/pkg/repos/origin.conf"

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

pre-build: apply-slist
	${MV} ${WRKDIR}/opnsense-update.sh ${WRKSRC}

.include <bsd.port.mk>

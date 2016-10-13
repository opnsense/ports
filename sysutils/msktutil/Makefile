# Created by: Ryan Steinmetz <zi@FreeBSD.org>
# $FreeBSD$

PORTNAME=	msktutil
PORTVERSION=	0.5.1
PORTREVISION=	2
CATEGORIES=	sysutils
MASTER_SITES=	SF/${PORTNAME}

MAINTAINER=	zi@FreeBSD.org
COMMENT=	Utility to manage Active Directory interoperability

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		gmake ssl tar:bzip2
USE_OPENLDAP=	yes
GNU_CONFIGURE=	yes
WANT_OPENLDAP_SASL=	yes

CONFIGURE_ARGS+=--with-sasldir=${LOCALBASE}

OPTIONS_SINGLE=	GSSAPI
OPTIONS_SINGLE_GSSAPI=	GSSAPI_BASE GSSAPI_HEIMDAL GSSAPI_MIT

OPTIONS_DEFAULT=GSSAPI_BASE

GSSAPI_BASE_USES=	gssapi
GSSAPI_HEIMDAL_USES=	gssapi:heimdal
GSSAPI_MIT_USES=	gssapi:mit

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/msktutil

PLIST_FILES=	man/man1/msktutil.1.gz sbin/msktutil

.include <bsd.port.mk>

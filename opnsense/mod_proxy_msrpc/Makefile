PORTNAME=	mod_proxy_msrpc
PORTVERSION=	0.6
PORTREVISION=	1
DISTVERSIONPREFIX=${PORTNAME}-
PKGNAMEPREFIX=	${APACHE_PKGNAMEPREFIX}
CATEGORIES=	www

MAINTAINER=	franco@opnsense.org
COMMENT=	Apache module for reverse proxy Outlook Anywhere support

LICENSE=	APACHE20

BUILD_DEPENDS=	checkmk:devel/check
LIB_DEPENDS=	libinotify.so:devel/libinotify \
		libuuid.so:misc/libuuid

USES=		apache autoreconf localbase:ldflags pkgconfig
USE_GITHUB=	yes
GH_ACCOUNT=	bombadil

AUTORECONF_WRKSRC=	${WRKSRC}/..
WRKSRC_SUBDIR=		src

CONFIGURE_ENV=	CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}"

post-patch:
	${REINPLACE_CMD} -e 's|@APXS@|@APXS@ -DENODATA=EIO|g' \
	    -e 's|@APXS@|@APXS@ ${LDFLAGS:N-fstack-protector-strong} -linotify|g' \
	    ${WRKSRC}/Makefile.in

post-configure:
	(cd ${AUTORECONF_WRKSRC}; ${ENV} ${CONFIGURE_ENV} ./configure)

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/${APACHEMODDIR}
	${APXS} -S LIBEXECDIR=${STAGEDIR}${PREFIX}/${APACHEMODDIR} -i -n ${SHORTMODNAME} ${WRKSRC}/${MODULENAME}.la
	@[ -e ${STAGEDIR}${PREFIX}/${APACHEMODDIR}/${MODULENAME}.so ] && ${STRIP_CMD} ${STAGEDIR}${PREFIX}/${APACHEMODDIR}/${MODULENAME}.so

.include <bsd.port.mk>

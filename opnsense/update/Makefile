PORTNAME=	update
PORTVERSION=	26.7.10
PORTREVISION=	1
CATEGORIES=	sysutils
PKGNAMEPREFIX=	${GH_ACCOUNT}-

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense update utilities
WWW=		https://github.com/opnsense/update

LICENSE=	BSD2CLAUSE

LIB_DEPENDS+=	libucl.so:textproc/libucl

USES=		ssl

UPDATE_BASE?=	# PORTVERSION
UPDATE_KERNEL?=	# PORTVERSION

MAKE_ENV=	UPDATE_BASE=${UPDATE_BASE} \
		UPDATE_FREEBSD=${OSREL} \
		UPDATE_KERNEL=${UPDATE_KERNEL} \
		UPDATE_RELEASE=${PORTVERSION}

USE_GITHUB=	yes
GH_ACCOUNT=	${CATEGORIES:[1]}
GH_TAGNAME=	5fc3f63

.if !empty(UPDATE_BASE)
PKG_NOTES+=		product_base
PKG_NOTE_product_base=	${UPDATE_BASE}
.endif

.if !empty(UPDATE_KERNEL)
PKG_NOTES+=		product_kernel
PKG_NOTE_product_kernel=${UPDATE_KERNEL}
.endif

.include <bsd.port.mk>

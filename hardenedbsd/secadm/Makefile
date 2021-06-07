PORTNAME=	secadm
PORTVERSION=	0.5.1
DISTVERSIONPREFIX=	v
PORTREVISION?=	7
CATEGORIES=	hardenedbsd

MAINTAINER=	shawn.webb@hardenedbsd.org
COMMENT=	HardenedBSD Security Administration

LICENSE=	BSD2CLAUSE

USES+=		uidfix
USE_HARDENING?=	safestack

USE_GITLAB=	yes
GL_SITE=	https://git.hardenedbsd.org
GL_ACCOUNT=	hardenedbsd
GL_PROJECT=	secadm
GL_COMMIT=	9a874be20a69bd5772115b33655f822b0e1c49a5

.if !defined(KMOD)
LIBDIR?=	${PREFIX}/lib
MAKE_ENV+=	LIBDIR=${LIBDIR}
.endif

MAKE_JOBS_UNSAFE=	yes

.include <bsd.port.pre.mk>

.if defined(KMOD)
MAKE_ENV+=	WITHOUT_CLI=YES
.else
MAKE_ENV+=	WITHOUT_KMOD=YES

LIB_DEPENDS=	libucl.so:textproc/libucl
.if ${OPSYS} == FreeBSD && ${OSVERSION} < 1100000
LIB_DEPENDS+=	libxo.so:devel/libxo
.endif

.endif

.include <bsd.port.post.mk>

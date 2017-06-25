# Created by: Jin-Sih Lin <linpct@gmail.com>
# $FreeBSD$

PORTNAME=	phalcon
PORTVERSION=	3.2.0
DISTVERSIONPREFIX=	v
CATEGORIES=	www
PKGNAMESUFFIX=	71

MAINTAINER=	linpct@gmail.com
COMMENT=	Phalcon PHP Framework written in C-language

LICENSE=	BSD3CLAUSE

USES=		php:ext

CONFLICTS_INSTALL=phalcon phalcon[!7][!1]

BUILD_DEPENDS=	php${PKGNAMESUFFIX}>=0:lang/php${PKGNAMESUFFIX} \
		php${PKGNAMESUFFIX}-hash>=0:security/php${PKGNAMESUFFIX}-hash \
		php${PKGNAMESUFFIX}-json>=0:devel/php${PKGNAMESUFFIX}-json \
		php${PKGNAMESUFFIX}-pdo>=0:databases/php${PKGNAMESUFFIX}-pdo

RUN_DEPENDS=	php:lang/php${PKGNAMESUFFIX} \
		${PHPBASE}/lib/php/20160303/hash.so:security/php${PKGNAMESUFFIX}-hash \
		${PHPBASE}/lib/php/20160303/json.so:devel/php${PKGNAMESUFFIX}-json \
		${PHPBASE}/lib/php/20160303/pdo.so:databases/php${PKGNAMESUFFIX}-pdo

ONLY_FOR_ARCHS=	amd64 armv6 i386

USE_GITHUB=	yes
GH_ACCOUNT=	phalcon
GH_PROJECT=	c${PORTNAME}

CFLAGS+=	-I${LOCALBASE}/include
CONFIGURE_ARGS=	--enable-phalcon

.include <bsd.port.pre.mk>

PBITS=		${ARCH:S/amd64/64/:S/armv6/32/:S/i386/32/:S/x86_64/64/}
WRKSRC_SUBDIR=	build/php${PHP_VER:C/.$//}/${PBITS}bits

post-patch:
.if ${PHP_VER} >= 70 && ${PBITS} == 32
	@${REINPLACE_CMD} -e 's| ZEPHIR_FASTCALL | |' ${WRKSRC}/phalcon.zep.c
.endif

.include <bsd.port.post.mk>

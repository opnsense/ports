# Created by: Kuang-che Wu <kcwu@csie.org>
# $FreeBSD$

PORTNAME=	tsito
PORTVERSION=	0.8.4
CATEGORIES=	games
MASTER_SITES=	SF/xiangqi-engine/xiangqi-engine/${PORTNAME}-${PORTVERSION}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Chinese chess (Xiangqi) program

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYING

USE_HARDENING=	pie:off

GNU_CONFIGURE=	yes
LIBS+=		-lcompat

.include <bsd.port.mk>

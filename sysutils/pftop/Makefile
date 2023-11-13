PORTNAME=	pftop
PORTVERSION=	0.9
CATEGORIES=	sysutils net

MAINTAINER=	grembo@FreeBSD.org
COMMENT=	Utility for real-time display of statistics for pf
WWW=		https://github.com/grembo/pftop/

LICENSE=	BSD2CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	grembo

LDFLAGS+=	-lnv

OPTIONS_DEFINE=	ALTQ

ALTQ_DESC=	ALTQ support for queue statistics

.include <bsd.port.options.mk>

CFLAGS+=	-DHAVE_SNPRINTF=1 -DHAVE_VSNPRINTF=1 -I${SRC_BASE}/lib/libpfctl

.if ${PORT_OPTIONS:MALTQ}
CFLAGS+=	-DHAVE_ALTQ=1
.endif

MAKE_ARGS+=	SRC_BASE=${SRC_BASE}
MAKE_ENV+=	__MAKE_CONF=/dev/null

PLIST_FILES=	man/man8/pftop.8.gz \
		sbin/pftop

.include <bsd.port.mk>

PORTNAME=	libmba
PORTVERSION=	0.9.1
PORTREVISION=	2
CATEGORIES=	devel
MASTER_SITES=	http://www.ioplex.com/~miallen/libmba/dl/ \
		LOCAL/miwi

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Collection of C modules potentially useful to any project
WWW=		https://www.ioplex.com/~miallen/libmba/

MAKE_JOBS_UNSAFE=	yes
USE_LDCONFIG=	yes
MAKE_ARGS=	prefix="${STAGEDIR}${PREFIX}" \
		mandir="\$$(prefix)/share/man"
CFLAGS+=	-D_WANT_SEMUN

post-patch:
	@${REINPLACE_CMD} -e 's,-g,$$(CFLAGS),' \
		${WRKSRC}/Makefile
	@${REINPLACE_CMD} -Ee 's,"g?cc","${CC}",' \
		${WRKSRC}/mktool.c

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libmba.so

.include <bsd.port.mk>

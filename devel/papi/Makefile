PORTNAME=	papi
PORTVERSION=	5.4.3
PORTREVISION=	12
CATEGORIES=	devel
MASTER_SITES=	http://icl.cs.utk.edu/projects/papi/downloads/

MAINTAINER=	pizzamig@FreeBSD.org
COMMENT=	API to access the performance counter hw in the microprocessor
WWW=		https://code.google.com/p/papi-for-freebsd/

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKDIR}/${PORTNAME}-${PORTVERSION}/LICENSE.txt

BROKEN=		freebsd.c:361:92: error: too few arguments to function call, expected 6, have 5
DEPRECATED=	Marked BROKEN 6+ months ago and outdated  
EXPIRATION_DATE=2025-02-28

TEST_TARGET=	fulltest

ONLY_FOR_ARCHS=	i386 amd64
ONLY_FOR_ARCHS_REASON=	HWPMC kernel module is only available for I386 and \
			AMD64 machines
NO_PACKAGE=	Needs to be compiled for specific CPU

STRIP=		# empty
USE_LDCONFIG=	yes
LIB_DEPENDS+=	libopa.so:net/mpich
USES=		fortran gmake pathfix pkgconfig
PATHFIX_MAKEFILEIN=	Makefile.inc
GNU_CONFIGURE=	yes
GNU_CONFIGURE_MANPREFIX=${PREFIX}/share
WRKSRC=		${WRKDIR}/${PORTNAME}-${PORTVERSION}/src
WRKMAN=		${WRKDIR}/${PORTNAME}-${PORTVERSION}/man
INSTALL_TARGET=	install-all
CONFIGURE_ARGS+=	--with-tests=ctests

OPTIONS_DEFINE=	CORETEMP DEBUGINFO
CORETEMP_DESC=	Add Intel Core thermal sensor (need coretemp.ko)
DEBUGINFO_DESC=	Add debug information (increased verbosity)

CORETEMP_CONFIGURE_ON=	--with-components=coretemp_freebsd
DEBUGINFO_CONFIGURE_WITH=	debug

.include <bsd.port.options.mk>

HAS_HWPMC!=	${SYSCTL} kern.hwpmc.nsamples >/dev/null 2>&1 && ${ECHO_CMD} yes || ${ECHO_CMD}

.if ${HAS_HWPMC} != yes
IGNORE=		needs hwpmc module loaded or compiled into the kernel. \
		Please consult hwpmc(4) on how to do it (or read pkg-message)
.endif

post-patch:
	${REINPLACE_CMD} -e 's|<malloc.h>|<stdlib.h>|g' \
		${WRKSRC}/components/appio/tests/appio_test_pthreads.c \
		${WRKSRC}/components/appio/tests/iozone/iozone.c \
		${WRKSRC}/components/appio/tests/iozone/libasync.c \
		${WRKSRC}/components/perfctr_ppc/linux-ppc64.h \
		${WRKSRC}/ctests/omptough.c \
		${WRKSRC}/ctests/pernode.c \
		${WRKSRC}/ctests/zero_shmem.c \
		${WRKSRC}/libpfm-3.y/lib/pfmlib_sicortex.c \
		${WRKSRC}/libpfm4/lib/pfmlib_sicortex.c \
		${WRKSRC}/testlib/papi_test.h

.include <bsd.port.mk>

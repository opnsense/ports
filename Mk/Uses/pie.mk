# $FreeBSD$
#
# Compile a port with PIE flags
#
# Feature:      pie
# Usage:        USES=pie
#
# MAINTAINER:	shawn.webb@hardenedbsd.org

.if !defined(_INCLUDE_USES_PIE_MK)
_INCLUDE_USES_PIE_MK=    yes

.if !empty(pie_ARGS)
IGNORE=	USES=pie does not require args
.endif

.if "${PORTNAME}" == "suricata"
# Note: Suricata on HardenedBSD supports using thread-local
# storage. But for some reason, the linker on OPNsense doesn't like
# it. Disable thread-local storage on OPNsense. Thread-local storage
# is used for speed. Suricata's Victor Julien does not know
# performance of thread-local storage versus posix thread storage.
# OpenBSD doesn't support the __thread gnu-ism, so they use posix
# thread storage.
#
# Discussed with: Victor Julien
CONFIGURE_ARGS+=	--enable-pie --disable-threading-tls
.elif "${PORTNAME}" == "pkg"
CONFIGURE_ARGS+=	--enable-pie
.else
CFLAGS+=	-fPIC -fPIE
CXXFLAGS+=	-fPIC -fPIE
LDFLAGS+=	-pie
.endif

.endif

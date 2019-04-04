# $FreeBSD$
#
# Compile a port with Speculative Load Hardening
#
# Warning: this feature carries a large performance hit.
#
# Feature:	speculative_load_hardening
# Usage:	USES=speculative_load_hardening
#
# MAINTAINER:	shawn.webb@hardenedbsd.org

.if !defined(_INCLUDE_USES_SPECULATIVE_LOAD_HARDENING_MK)
_INCLUDE_USES_SPECULATIVE_LOAD_HARDENING_MK=    yes

CFLAGS+=	-mspeculative-load-hardening
CXXFLAGS+=	-mspeculative-load-hardening
LDFLAGS+=	-mspeculative-load-hardening

.endif

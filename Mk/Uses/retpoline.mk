# $FreeBSD$
#
# Compile a port with retpoline
#
# Feature:	retpoline
# Usage:	USES=retpoline
#
# MAINTAINER:	shawn.webb@hardenedbsd.org

.if !defined(_INCLUDE_USES_RETPOLINE_MK)
_INCLUDE_USES_RETPOLINE_MK=    yes

CFLAGS+=	-mretpoline
CXXFLAGS+=	-mretpoline
#LDFLAGS+=	-Wl,-z,retpolineplt

.endif

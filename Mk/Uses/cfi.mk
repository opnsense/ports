# $FreeBSD$
#
# Compile a port with CFI
#
# Feature:	cfi
# Usage:	USES=cfi
#
# MAINTAINER:	shawn.webb@hardenedbsd.org

.if !defined(_INCLUDE_USES_CFI_MK)
_INCLUDE_USES_CFI_MK=    yes

.if ${cfi_ARGS:Mconfigure}
CONFIGURE_ARGS+=	--enable-cfi
.else

CFI_OVERRIDE?=	# Intentionally blank

CFLAGS+=	-fsanitize=cfi -fvisibility=hidden -flto ${CFI_OVERRIDE}
CXXFLAGS+=	-fsanitize=cfi -fvisibility=hidden -flto ${CFI_OVERRIDE}
LDFLAGS+=	-fsanitize=cfi -fvisibility=hidden -flto ${CFI_OVERRIDE}
.endif

.endif

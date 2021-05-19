# Compile a port with stack zero-initialization
#
# Feature:	stack_autoinit
# Usage:	USES=stack_autoinit
#
# MAINTAINER:	shawn.webb@hardenedbsd.org

.if !defined(_INCLUDE_USES_STACK_AUTOINIT_MK)
_INCLUDE_USES_STACK_AUTOINIT_MK=    yes

CFLAGS+=        -ftrivial-auto-var-init=zero
CFLAGS+=        -enable-trivial-auto-var-init-zero-knowing-it-will-be-removed-from-clang
CXXFLAGS+=      -ftrivial-auto-var-init=zero
CXXFLAGS+=      -enable-trivial-auto-var-init-zero-knowing-it-will-be-removed-from-clang

.endif

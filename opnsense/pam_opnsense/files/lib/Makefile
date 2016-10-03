LIB=	pam_opnsense
SRCS=	${LIB}.c

SHLIB_NAME=${LIB}.so

WARNS=	3

LDADD+=	-lpam

PREFIX?=${LOCALBASE}
LIBDIR=	${PREFIX}/lib

.include <bsd.lib.mk>

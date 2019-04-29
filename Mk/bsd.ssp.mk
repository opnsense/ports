# $FreeBSD$
# SSP Support

SSP_Include_MAINTAINER=	portmgr@FreeBSD.org

.if !defined(SSP_UNSAFE) && \
    (${MACHINE} != "mips")
# Overridable as a user may want to use -fstack-protector
SSP_CFLAGS?=	-fstack-protector-all
CFLAGS+=	${SSP_CFLAGS}
.if ${SSP_CFLAGS:M-fstack-protector-all}
LDFLAGS+=	-fstack-protector
.else
LDFLAGS+=	${SSP_CFLAGS}
.endif
.endif

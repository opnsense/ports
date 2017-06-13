# $FreeBSD$
#
# HardenedBSD-related ports options

.if !defined(HARDENINGMKINCLUDED)
HARDENINGMKINCLUDED=	bsd.hardening.mk

# Can pass exceptions from global make.conf,
# either as individual portname_HARDENING
# or the global HARDENING_OFF flag per feature.

${PORTNAME}_HARDENING?=
HARDENING_OFF?=

.include "${PORTSDIR}/Mk/bsd.hardening.exceptions.mk"

# Can pass exceptions from port Makefile, too.

USE_HARDENING?=		pie relro ${${PORTNAME}_HARDENING}

.if defined(PORTNAME)
.if ${PORTNAME:Mlib*} && ${PORTNAME:Mlibre*} == ""
USE_HARDENING+=	lib
.endif
.if ${PORTNAME:M*kmod*}
USE_HARDENING+=	kmod
.endif
.endif

.if defined(PKGNAMEPREFIX)
.if ${PKGNAMEPREFIX:Mlib}
USE_HARDENING+=	lib
.endif
.endif

.if defined(PKGNAMESUFFIX)
.if ${PKGNAMESUFFIX:M-lib*}
USE_HARDENING+=	lib
.endif
.endif

.if defined(USES)
.if ${USES:Mkmod}
USE_HARDENING+=	kmod
.endif
.if ${USES:Mfortran}
USE_HARDENING+=	fortran
.endif
.endif

.if defined(CATEGORIES)
.if ${CATEGORIES:Mx11-drivers}
USE_HARDENING+=	x11
.endif
.if ${CATEGORIES:Mlinux}
USE_HARDENING+=	linux
.endif
.endif

.if defined(NO_BUILD) || defined(NO_ARCH)
USE_HARDENING+=	static
.endif

#################################################
### Option-less PIC enforcement for libraries ###
#################################################

.if ${USE_HARDENING:Mlib}
CFLAGS+=		-fPIC
CXXFLAGS+=		-fPIC
.endif

####################################################
### Position-Idependent Executable (PIE) support ###
####################################################

.if ${USE_HARDENING:Mlib} || ${USE_HARDENING:Mkmod} || ${USE_HARDENING:Mfortran} || defined(NO_BUILD) || defined(NO_ARCH)
USE_HARDENING+=		nopie
.endif

.if ${HARDENING_OFF:Mpie} == ""
.if ${USE_HARDENING:Mpie} && ${USE_HARDENING:Mnopie} == ""
PIE_DESC=		Build as PIE
PIE_USES=		pie
OPTIONS_DEFINE+=	PIE
OPTIONS_DEFAULT+=	PIE
.endif
.endif

################################
### RELRO + BIND_NOW support ###
################################

.if ${USE_HARDENING:Mlib} || ${USE_HARDENING:Mkmod} || ${USE_HARDENING:Mfortran} || ${USE_HARDENING:Mx11} || defined(NO_BUILD) || defined(NO_ARCH)
USE_HARDENING+=		norelro
.endif

.if ${HARDENING_OFF:Mrelro} == ""
.if ${USE_HARDENING:Mrelro} && ${USE_HARDENING:Mnorelro} == ""
RELRO_DESC=		Build with RELRO + BIND_NOW
RELRO_USES=		relro
OPTIONS_DEFINE+=	RELRO
OPTIONS_DEFAULT+=	RELRO
.endif
.endif

#########################
### SafeStack support ###
#########################

.if defined(NO_BUILD) || defined(NO_ARCH) || ${ARCH} != "amd64"
USE_HARDENING+=		nosafestack
.endif

.if ${HARDENING_OFF:Msafestack} == ""
.if ${USE_HARDENING:Msafestack} && ${USE_HARDENING:Mnosafestack} == ""
SAFESTACK_DESC=		Build with SafeStack
SAFESTACK_USES=		safestack
OPTIONS_DEFINE+=	SAFESTACK
OPTIONS_DEFAULT+=	SAFESTACK
.endif
.endif

.endif # !HARDENINGMKINCLUDED

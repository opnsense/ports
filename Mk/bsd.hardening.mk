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

USE_HARDENING?=		pie:default relro:default ${${PORTNAME}_HARDENING}
_USE_HARDENING=		# internal flags

.if defined(PORTNAME)
.if ${PORTNAME:Mlib*} && ${PORTNAME:Mlibre*} == ""
_USE_HARDENING+=	lib
.endif
.if ${PORTNAME:M*kmod*}
_USE_HARDENING+=	kmod
.endif
.endif

.if defined(PKGNAMEPREFIX)
.if ${PKGNAMEPREFIX:Mlib}
_USE_HARDENING+=	lib
.endif
.endif

.if defined(PKGNAMESUFFIX)
.if ${PKGNAMESUFFIX:M-lib*}
_USE_HARDENING+=	lib
.endif
.endif

.if defined(USES)
.if ${USES:Mkmod}
_USE_HARDENING+=	kmod
.endif
.if ${USES:Mfortran}
_USE_HARDENING+=	fortran
.endif
.endif

.if defined(CATEGORIES)
.if ${CATEGORIES:Mx11-drivers}
_USE_HARDENING+=	x11
.endif
.if ${CATEGORIES:Mlinux}
_USE_HARDENING+=	linux
.endif
.endif

.if defined(NO_BUILD) || defined(NO_ARCH)
_USE_HARDENING+=	static
.endif

.for h in ${USE_HARDENING}
_h:=		${h:C/\:.*//}
.if ${_h} == "pie" || ${_h} == "relro" || ${_h} == "safestack"
.if !defined(${_h}_ARGS)
USE_HARDENING:=	${USE_HARDENING:N${h}} ${_h}
${_h}_ARGS:=	${h:C/^[^\:]*(\:|\$)//:S/,/ /g}
.endif
.endif
.endfor

#################################################
### Option-less PIC enforcement for libraries ###
#################################################

.if ${_USE_HARDENING:Mlib}
CFLAGS+=		-fPIC
CXXFLAGS+=		-fPIC
.endif

####################################################
### Position-Idependent Executable (PIE) support ###
####################################################

pie_ARGS?=

.if ${pie_ARGS:Mdefault}
.if ${_USE_HARDENING:Mlib} || ${_USE_HARDENING:Mkmod} || ${_USE_HARDENING:Mfortran} || ${_USE_HARDENING:Mlinux} || ${_USE_HARDENING:Mstatic}
USE_HARDENING+=		nopie
.endif
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

relro_ARGS?=

.if ${relro_ARGS:Mdefault}
.if ${_USE_HARDENING:Mlib} || ${_USE_HARDENING:Mkmod} || ${_USE_HARDENING:Mfortran} || ${_USE_HARDENING:Mx11} || ${_USE_HARDENING:Mlinux} || ${_USE_HARDENING:Mstatic}
USE_HARDENING+=		norelro
.endif
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

.if ${OSVERSION} >= 1100122

safestack_ARGS?=

.if ${_USE_HARDENING:Mstatic} || ${ARCH} != "amd64"
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

.endif

###################
### CFI support ###
###################

.if ${OSVERSION} >= 1200020 && ${LLD_IS_LD} == "yes"

.if ${_USE_HARDENING:Mstatic} || ${ARCH} != "amd64"
USE_HARDENING+=		nocfi
.endif

.if ${HARDENING_OFF:Mcfi} == ""
.if ${USE_HARDENING:Mcfi} && ${USE_HARDENING:Mnocfi} == ""
CFIHARDEN_DESC=		Build with CFI (Requires lld 4.0.0 in base)
CFIHARDEN_USES=		cfi
OPTIONS_DEFINE+=	CFIHARDEN
OPTIONS_DEFAULT+=	CFIHARDEN
.endif
.endif

.endif

.endif # !HARDENINGMKINCLUDED

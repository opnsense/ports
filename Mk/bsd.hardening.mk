# $FreeBSD$
#
# HardenedBSD-related ports options
#
# Hardening for binary applications is done via several techniques, e.g.
# position indepdentent execution (PIE), relocation read-only (RELRO),
# SafeStack (SAFESTACK) or control flow integrity (CFI).
#
# The hardening framework comes with a twist in the port options: the USES
# variable is extended with the hardening request, but a port option is
# also added according to the state of the hardening feature and HARDENING_LOCK.
# Therefore it is possible to revoke / extend hardening with a port update.
#
# These variables are used in global makefiles to operate general
# hardening behaviour.
#
# HARDENING_ALL		- List of available hardening features
# HARDENING_OFF		- List of features this frameworks accepts
# 			  to disable individual features represented
# 			  through HARDENING_ALL
# HARDENING_LOCK	- Define to lock hardening features for batch
# 			  and package builds, which also removes disabled
# 			  hardening features from the port options.
#
# These variables are used in port makefiles to define the options for a port.
#
# USE_HARDENING		- List of to be used hardening features
#
# All hardening feature can support multiple arguments, either as a list of
# aruments separated by comma or by multiple invokes of the feature:
#
# USE_HARDENING=	pie:auto pie:configure,java pie safestack
#
# The argments supported are based on the needs of individual features, yet
# follow the following rationale:
#
# auto			- Automatic application of a feature based on numerous
# 			  parsing rules and safeguards, but can be overwritten
# 			  by explicit mentions of either "feature:off" or
# 			  "feature" (defaults: pie, relro)
# (empty)		- Explicit request of a feature, overrides auto and
# 			  adds the relevant compiler flags to the port
# off			- Explicit removal of a feature, overwrites (empty)
# configure		- Pass enable flags during configure stage, required
# 			  by a number of ports (if applicable)
# java			- Special handling for java ports (if applicable)

.if !defined(HARDENINGMKINCLUDED)
HARDENINGMKINCLUDED=	bsd.hardening.mk

HARDENING_ALL=		cfi pie relro safestack
HARDENING_OFF?=		# all features are on by default

USE_HARDENING?=		# implicit auto-defaults may apply
_USE_HARDENING=		# internal flags for auto mode

OPTIONS_GROUP+=		HARDENING

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
.if ${PKGNAMESUFFIX:M*-static}
_USE_HARDENING+=	static
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

.if (defined(PACKAGE_BUILDING) || defined(BATCH)) && defined(HARDENING_LOCK)
# The lock prevents unused hardening options
# from being embedded into the package when
# building in batches and/or package building.
_USE_HARDENING+=	lock
.endif

.for h in ${USE_HARDENING}
_h:=		${h:C/\:.*//}
.if ${HARDENING_ALL:M${_h}} != ""
USE_HARDENING:=	${_h} ${USE_HARDENING:N${h}:N${_h}}
${_h}_ARGS:=	${h:C/^[^\:]*(\:|\$)//:S/,/ /g} ${${_h}_ARGS}
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

.if ${HARDENING_OFF:Mpie} == ""
.if ${OSVERSION} > 1100000

pie_ARGS?=		auto

.if ${pie_ARGS:Mauto}
.if ${_USE_HARDENING:Mlib} || ${_USE_HARDENING:Mkmod} || ${_USE_HARDENING:Mfortran} || ${_USE_HARDENING:Mlinux} || ${_USE_HARDENING:Mstatic}
# Do not enable PIE for libraries or kernel module ports.
pie_ARGS+=		off
.else
USE_HARDENING:=		pie ${USE_HARDENING:Npie}
.endif
.endif

PIE_DESC=		Build as PIE
PIE_USES=		pie

.if ${_USE_HARDENING:Mlock} == ""
OPTIONS_GROUP_HARDENING+=PIE
.endif

.if ${USE_HARDENING:Mpie} && ${pie_ARGS:Moff} == ""
OPTIONS_DEFAULT+=	PIE
.if ${_USE_HARDENING:Mlock} != ""
OPTIONS_GROUP_HARDENING+=PIE
.endif
.endif

.endif
.endif

################################
### RELRO + BIND_NOW support ###
################################

.if ${HARDENING_OFF:Mrelro} == ""

relro_ARGS?=		auto

.if ${relro_ARGS:Mauto}
.if ${_USE_HARDENING:Mlib} || ${_USE_HARDENING:Mkmod} || ${_USE_HARDENING:Mfortran} || ${_USE_HARDENING:Mx11} || ${_USE_HARDENING:Mlinux} || ${_USE_HARDENING:Mstatic}
relro_ARGS+=		off
.else
USE_HARDENING:=		relro ${USE_HARDENING:Nrelro}
.endif
.endif

RELRO_DESC=		Build with RELRO + BIND_NOW
RELRO_USES=		relro

.if ${_USE_HARDENING:Mlock} == ""
OPTIONS_GROUP_HARDENING+=RELRO
.endif

.if ${USE_HARDENING:Mrelro} && ${relro_ARGS:Moff} == ""
OPTIONS_DEFAULT+=	RELRO
.if ${_USE_HARDENING:Mlock} != ""
OPTIONS_GROUP_HARDENING+=RELRO
.endif
.endif

.endif

#########################
### SafeStack support ###
#########################

.if ${HARDENING_OFF:Msafestack} == ""
.if ${OSVERSION} >= 1100122 && ${ARCH} == "amd64"

safestack_ARGS?=

.if ${safestack_ARGS:Mauto}
.if ${_USE_HARDENING:Mstatic}
safestack_ARGS+=	off
.endif
.endif

SAFESTACK_DESC=		Build with SafeStack
SAFESTACK_USES=		safestack

.if ${_USE_HARDENING:Mlock} == ""
OPTIONS_GROUP_HARDENING+=SAFESTACK
.endif

.if ${USE_HARDENING:Msafestack} && ${safestack_ARGS:Moff} == ""
OPTIONS_DEFAULT+=	SAFESTACK
.if ${_USE_HARDENING:Mlock} != ""
OPTIONS_GROUP_HARDENING+=SAFESTACK
.endif
.endif

.endif
.endif

###################
### CFI support ###
###################

.if ${HARDENING_OFF:Mcfi} == ""

.if ${OSVERSION} >= 1200020 && ${ARCH} == "amd64" && \
	${LLD_IS_LD} == "yes" && \
	${LLVM_AR_IS_AR} == "yes" && \
	${LLVM_RANLIB_IS_RANLIB} == "yes" && \
	${LLVM_NM_IS_NM} == "yes" && \
	${LLVM_OBJDUMP_IS_OBJDUMP} == "yes"

cfi_ARGS?=

.if ${cfi_ARGS:Mauto}
.if ${_USE_HARDENING:Mstatic}
cfi_ARGS+=		off
.endif
.endif

CFIHARDEN_DESC=		Build with CFI (Requires lld 4.0.0 or later in base)
CFIHARDEN_USES=		cfi

.if ${_USE_HARDENING:Mlock} == ""
OPTIONS_GROUP_HARDENING+=CFIHARDEN
.endif

.if ${USE_HARDENING:Mcfi} && ${cfi_ARGS:Moff} == ""
OPTIONS_DEFAULT+=	CFIHARDEN
.if ${_USE_HARDENING:Mlock} != ""
OPTIONS_GROUP_HARDENING+=CFIHARDEN
.endif
.endif

.endif
.endif

.endif # !HARDENINGMKINCLUDED

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
# USE_HARDENING=	pie:auto pie:configure,java
# USE_HARDENING+=	pie
# USE_HARDENING+=	safestack
#
# A single-line style is recommended for port defaults unless conditional
# hardening is required, e.g. for STATIC builds which do not support PIE.
# Placement of the USE_HARDENING directive is below LICENSE, DEPENDS and
# similar, but before USES or OPTIONS are defined.  Also make sure that
# the directive is added before inclusion of <bsd.port.pre.mk> to end up
# being evaluated correctly.
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
#
# Individual information about argument support can be found in the
# respective ${PORTSDIR}/Mk/Uses/"feature".mk files.
#
# MAINTAINER:	franco.fichtner@hardenedbsd.org

.if !defined(HARDENINGMKINCLUDED)
HARDENINGMKINCLUDED=	bsd.hardening.mk

.if exists(/usr/include/sys/pax.h)
HBSDVERSION!=		${AWK} '/^\#define[[:blank:]]__HardenedBSD_version/ {print $$3}' /usr/include/sys/pax.h \
	| ${SED} -e 's/UL$$//g'
.else
# if HardenedBSD is not installed disable all features by passing zero
HBSDVERSION=		0
.endif

HARDENING_ALL=		cfi pie relro retpoline safestack slh
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

PIE_DESC=		Build as Position Independent Executable
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

RELRO_DESC=		Build with Relocation Read-Only + BIND_NOW
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

.if ${OSVERSION} >= 1200020 && \
	${LLD_IS_LD} == "yes" && \
	${LLVM_AR_IS_AR} == "yes" && \
	${LLVM_RANLIB_IS_RANLIB} == "yes" && \
	${LLVM_NM_IS_NM} == "yes" && \
	${LLVM_OBJDUMP_IS_OBJDUMP} == "yes" && \
	(${ARCH} == "amd64" || ${ARCH} == "aarch64")

cfi_ARGS?=

.if ${cfi_ARGS:Mauto}
.if ${_USE_HARDENING:Mstatic}
cfi_ARGS+=		off
.endif
.endif

CFI_DESC=		Build with Control Flow Integrity
CFI_USES=		cfi

.if ${_USE_HARDENING:Mlock} == ""
OPTIONS_GROUP_HARDENING+=CFI
.endif

.if ${USE_HARDENING:Mcfi} && ${cfi_ARGS:Moff} == ""
OPTIONS_DEFAULT+=	CFI
.if ${_USE_HARDENING:Mlock} != ""
OPTIONS_GROUP_HARDENING+=CFI
.endif
.endif

.endif
.endif

#########################
### Retpoline support ###
#########################

.if ${HARDENING_OFF:Mretpoline} == ""

.if ${OSVERSION} >= 1200055 && ${HBSDVERSION} >= 1200057 \
	&& ${ARCH} == "amd64" && ${LLD_IS_LD} == "yes" \
	&& !defined(LLD_UNSAFE) && !defined(USE_GCC)

retpoline_ARGS?=	auto

.if ${retpoline_ARGS:Mauto}
USE_HARDENING:=		retpoline ${USE_HARDENING:Nretpoline}
.endif

RETPOLINE_DESC=		Build with Retpoline
RETPOLINE_USES=		retpoline

.if ${_USE_HARDENING:Mlock} == ""
OPTIONS_GROUP_HARDENING+=RETPOLINE
.endif

.if ${USE_HARDENING:Mretpoline} && ${retpoline_ARGS:Moff} == ""
OPTIONS_DEFAULT+=	RETPOLINE
.if ${_USE_HARDENING:Mlock} != ""
OPTIONS_GROUP_HARDENING+=RETPOLINE
.endif
.endif

.endif
.endif

###########################################
### Spectulative Load Hardening support ###
###########################################

.if ${HARDENING_OFF:Mslh} == ""

.if ${OSVERSION} >= 1200055 && ${HBSDVERSION} >= 1200057 \
	&& ${ARCH} == "amd64" && ${LLD_IS_LD} == "yes" \
	&& !defined(LLD_UNSAFE) && !defined(USE_GCC)

slh_ARGS?=	auto

.if ${slh_ARGS:Mauto}
slh_ARGS:=	off
.endif

SLH_DESC=		Build with Speculative Load Hardening (large perf hit)
SLH_USES=		speculative_load_hardening

.if ${_USE_HARDENING:Mlock} == ""
OPTIONS_GROUP_HARDENING+=SLH
.endif

.if ${USE_HARDENING:Mslh} && ${slh_ARGS:Moff} == ""
OPTIONS_DEFAULT+=	SLH
.if ${_USE_HARDENING:Mlock} != ""
OPTIONS_GROUP_HARDENING+=SLH
.endif
.endif

.endif
.endif

.endif # !HARDENINGMKINCLUDED

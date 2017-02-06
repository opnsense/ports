# $FreeBSD$
#
# HardenedBSD-related ports options

.if !defined(HARDENINGMKINCLUDED)
HARDENINGMKINCLUDED=	bsd.hardening.mk

${PORTNAME}_HARDENING_QURIKS?=	# can pass exceptions from global make.conf
HARDENING_QUIRKS?=		# can pass exceptions from port Makefile

.include "${PORTSDIR}/Mk/bsd.hardening.exceptions.mk"

# XXX fix expansion
HARDENING_QUIRKS+=	${${PORTNAME}_HARDENING_QURIKS}

.if defined(PORTNAME)
.if ${PORTNAME:Mlib*} && ${PORTNAME:Mlibre*} == ""
HARDENING_QUIRKS+=	lib
.endif
.if ${PORTNAME:M*kmod*}
HARDENING_QUIRKS+=	kmod
.endif
.endif

.if defined(PKGNAMEPREFIX)
.if ${PKGNAMEPREFIX:Mlib}
HARDENING_QUIRKS+=	lib
.endif
.endif

.if defined(PKGNAMESUFFIX)
.if ${PKGNAMESUFFIX:M-lib*}
HARDENING_QUIRKS+=	lib
.endif
.endif

.if defined(USES)
.if ${USES:Mkmod}
HARDENING_QUIRKS+=	kmod
.endif
.if ${USES:Mfortran}
HARDENING_QUIRKS+=	fortran
.endif
.endif

.if defined(CATEGORIES)
.if ${CATEGORIES:Mx11-drivers}
HARDENING_QUIRKS+=	x11
.endif
.endif

#################################################
### Option-less PIC enforcement for libraries ###
#################################################

.if ${HARDENING_QUIRKS:Mlib}
CFLAGS+=	-fPIC
CXXFLAGS+=	-fPIC
.endif

####################################################
### Position-Idependent Executable (PIE) support ###
####################################################

.if ${HARDENING_QUIRKS:Mlib} || ${HARDENING_QUIRKS:Mkmod} || ${HARDENING_QUIRKS:Mfortran}
HARDENING_QUIRKS+=	nopie
.endif

# Do not enable PIE for several groups of ports.
# However, provide a way for still enabling PIE
# if desired by allowing them to define:
#
# HARDENING_QURIKS=pie

.if !defined(HARDENING_OFF)
.if ${HARDENING_QUIRKS:Mpie} || ${HARDENING_QUIRKS:Mnopie} == ""
PIE_DESC=		Build as PIE
PIE_USES=		pie
OPTIONS_DEFINE+=	PIE
OPTIONS_DEFAULT+=	PIE
.endif
.endif

################################
### RELRO + BIND_NOW support ###
################################

.if ${HARDENING_QUIRKS:Mlib} || ${HARDENING_QUIRKS:Mkmod} || ${HARDENING_QUIRKS:Mfortran} || ${HARDENING_QUIRKS:Mx11}
HARDENING_QUIRKS+=	norelro
.endif

# Same reasoning here with RELRO as with PIE.
#
# HARDENING_QURIKS=relro

.if !defined(HARDENING_OFF)
.if ${HARDENING_QUIRKS:Mrelro} || ${HARDENING_QUIRKS:Mnorelro} == ""
RELRO_DESC=		Build with RELRO + BIND_NOW
RELRO_USES=		relro
OPTIONS_DEFINE+=	RELRO
OPTIONS_DEFAULT+=	RELRO
.endif
.endif

.endif # !HARDENINGMKINCLUDED

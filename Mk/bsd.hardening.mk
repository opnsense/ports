# $FreeBSD$
#
# HardenedBSD-related ports options

.if !defined(HARDENINGMKINCLUDED)
HARDENINGMKINCLUDED=	bsd.hardening.mk

HARDENING_NOPIE_PORTS?=		# can pass exceptions from make.conf
HARDENING_NORELRO_PORTS?=	# can pass exceptions from make.conf
HARDENING_QUIRKS?=		# can pass exceptions from make.conf

.include "bsd.hardening.exceptions.mk"

.if defined(NO_PORTS_HARDENING)
HARDENING_QUIRKS+=	nopie norelro
.endif

.if defined(PORTNAME)
.if ${HARDENING_NOPIE_PORTS:M${PORTNAME}}
HARDENING_QUIRKS+=	nopie
.endif
.if ${HARDENING_NORELRO_PORTS:M${PORTNAME}}
HARDENING_QUIRKS+=	norelro
.endif
.if ${PORTNAME:Mlib*} && ${PORTNAME:Mlibre*} == ""
HARDENING_QUIRKS+=	lib
.endif
.if ${PORTNAME:M*kmod*}
HARDENING_QUIRKS+=	kmod
.endif
.endif
.endif

.if defined(PKGNAMEPREFIX)
.if ${PKGNAMEPREFIX:M*lib*} && ${PKGNAMEPREFIX:M*libre*} == ""
HARDENING_QUIRKS+=	lib
.endif
.endif

.if defined(PKGNAMESUFFIX)
.if ${PKGNAMESUFFIX:M*lib*} && ${PKGNAMESUFFIX:M*libre*} == ""
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

PIE_DESC=		Build as PIE
PIE_USES=		pie

# Do not enable PIE for libraries or kernel module ports. However,
# provide a way for still enabling PIE if desired by the port's
# maintainer by allowing them to define EXPLICIT_PIE.
#
# It's possible that keying off lib* as the port's name could
# introduce false positives. Hence even more reason to have
# EXPLICIT_PIE.

.if ${HARDENING_QUIRKS:Mlib} || ${HARDENING_QUIRKS:Mkmod} || ${HARDENING_QUIRKS:Mfortran}
.if !defined(EXPLICIT_PIE)
HARDENING_QUIRKS+=	nopie
.endif
.endif

.if ${HARDENING_QUIRKS:Mnopie} == ""
OPTIONS_DEFINE+=	PIE
OPTIONS_DEFAULT+=	PIE
.endif

################################
### RELRO + BIND_NOW support ###
################################

RELRO_DESC=		Build with RELRO + BIND_NOW
RELRO_USES=		relro

# Same reasoning here with RELRO as with PIE.
.if ${HARDENING_QUIRKS:Mlib} || ${HARDENING_QUIRKS:Mkmod} || ${HARDENING_QUIRKS:Mfortran} || ${HARDENING_QUIRKS:Mx11}
.if !defined(EXPLICIT_RELRO)
HARDENING_QUIRKS+=	norelro
.endif
.endif

.if ${HARDENING_QUIRKS:Mnorelro} == ""
OPTIONS_DEFINE+=	RELRO
OPTIONS_DEFAULT+=	RELRO
.endif

.endif # !__BSD_PORT_HARDENING_MK

# Treat this directory as a pluggable ports category:
THIS_CATEGORY=	opnsense
VALID_CATEGORIES=${THIS_CATEGORY}
CATEGORIES:=	${THIS_CATEGORY} ${CATEGORIES}
PKGORIGIN=	${.CURDIR:S/${PORTSDIR}\///1}

.if "${SRCVERSION}" != ""
DISTVERSION!=	eval export $$(${SH} ${SRC_BASE}/sys/conf/newvers.sh -V RELEASE) && echo $${RELEASE}
.endif

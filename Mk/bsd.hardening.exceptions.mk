.if ${PORTNAME} == suricata
CONFIGURE_ARGS+=	--enable-pie
NOPIE_PORTS=		yes
.elif ${PORTNAME} == pkg
NOPIE_PORTS=		yes
.endif

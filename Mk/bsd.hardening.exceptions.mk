.if ${PORTNAME:Msuricata}
CONFIGURE_ARGS+=	--enable-pie
NOPIE_PORTS=		yes
.elif ${PORTNAME:Mpkg}
NOPIE_PORTS=		yes
.endif

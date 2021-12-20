PORTNAME=		openvpn
DISTVERSION=		2.5.5
CATEGORIES=		security net net-vpn
MASTER_SITES=		https://swupdate.openvpn.org/community/releases/ \
			https://build.openvpn.net/downloads/releases/

MAINTAINER=		franco@opnsense.org
COMMENT=		Secure IP/Ethernet tunnel daemon

LICENSE=		GPLv2
LICENSE_FILE=		${WRKSRC}/COPYRIGHT.GPL

USES=			cpe libtool localbase:ldflags pkgconfig shebangfix tar:xz
USE_RC_SUBR=		openvpn

SHEBANG_FILES=		sample/sample-scripts/verify-cn \
			sample/sample-scripts/auth-pam.pl \
			sample/sample-scripts/ucn.pl

GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--enable-strict
# set PLUGIN_LIBDIR so that unqualified plugin paths are found:
CONFIGURE_ENV+=		PLUGINDIR="${PREFIX}/lib/openvpn/plugins"

CONFLICTS_INSTALL?=	openvpn-2.[!5].* openvpn-devel openvpn-mbedtls

SUB_FILES=		pkg-message openvpn-client

USERS=			openvpn
GROUPS=			openvpn

PORTDOCS=		*
PORTEXAMPLES=		*

OPTIONS_DEFINE=		ASYNC_PUSH LZ4 LZO TUNNELBLICK X509ALTUSERNAME
OPTIONS_DEFAULT=	LZ4 LZO OPENSSL TUNNELBLICK
OPTIONS_SINGLE=		SSL
OPTIONS_SINGLE_SSL=	OPENSSL MBEDTLS
ASYNC_PUSH_DESC=	Enable async-push support
MBEDTLS_DESC=		SSL/TLS via mbedTLS (lacks TLS v1.3)
TUNNELBLICK_DESC=	Tunnelblick XOR scramble patch (READ HELP!)
X509ALTUSERNAME_DESC=	Enable --x509-username-field (OpenSSL only)

ASYNC_PUSH_LIB_DEPENDS=	libinotify.so:devel/libinotify
ASYNC_PUSH_CONFIGURE_ENABLE=	async-push

LZ4_LIB_DEPENDS+=	liblz4.so:archivers/liblz4
LZ4_CONFIGURE_ENABLE=	lz4

LZO_LIB_DEPENDS+=	liblzo2.so:archivers/lzo2
LZO_CONFIGURE_ENABLE=	lzo

MBEDTLS_LIB_DEPENDS=	libmbedtls.so:security/mbedtls
MBEDTLS_CONFIGURE_ON=	--with-crypto-library=mbedtls

OPENSSL_USES=		ssl
OPENSSL_CONFIGURE_ON=	--with-crypto-library=openssl

TUNNELBLICK_EXTRA_PATCHES=	${FILESDIR}/extra-tunnelblick-openvpn_xorpatch:-p1

X509ALTUSERNAME_PREVENTS=	MBEDTLS
X509ALTUSERNAME_PREVENTS_MSG=	OpenVPN ${DISTVERSION} cannot use --x509-username-field with mbedTLS. Disable X509ALTUSERNAME, or use OpenSSL instead
X509ALTUSERNAME_CONFIGURE_ENABLE=	x509-alt-username

.ifdef (LOG_OPENVPN)
CFLAGS+=		-DLOG_OPENVPN=${LOG_OPENVPN}
.endif

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MMBEDTLS}
BROKEN_FreeBSD_14=      OpenVPN-mbedTLS fails on FreeBSD 14
_tlslibs=libmbedtls libmbedx509 libmbedcrypto
.else
# OpenSSL
_tlslibs=libssl libcrypto
.endif

.if ! ${PORT_OPTIONS:MLZ4} && ! ${PORT_OPTIONS:MLZO}
CONFIGURE_ARGS+=	--enable-comp-stub
.endif

post-patch:
	${REINPLACE_CMD} -E -i '' -e 's/(user|group) nobody/\1 openvpn/' \
		-e 's/"nobody"( after init)/"openvpn" \1/' \
		${WRKSRC}/sample/sample-config-files/*.conf \
		${WRKSRC}/sample/sample-config-files/xinetd-*-config \
		${WRKSRC}/doc/man-sections/generic-options.rst

pre-configure:
.ifdef (LOG_OPENVPN)
	@${ECHO} "Building with LOG_OPENVPN=${LOG_OPENVPN}"
.else
	@${ECHO} ""
	@${ECHO} "You may use the following build options:"
	@${ECHO} ""
	@${ECHO} "      LOG_OPENVPN={Valid syslog facility, default LOG_DAEMON}"
	@${ECHO} "      EXAMPLE:  make LOG_OPENVPN=LOG_LOCAL6"
	@${ECHO} ""
.endif

post-configure:
	${REINPLACE_CMD} '/^CFLAGS =/s/$$/ -fPIC/' \
	    ${WRKSRC}/src/plugins/auth-pam/Makefile \
	    ${WRKSRC}/src/plugins/down-root/Makefile

# sanity check that we don't inherit incompatible SSL libs through,
# for instance, pkcs11-helper:
post-build:
	@a=$$(LC_ALL=C ldd -f '%o\n' ${WRKSRC}/src/openvpn/openvpn \
	|	${SORT} -u) ; set -- $$(for i in ${_tlslibs} ; do ${PRINTF} '%s\n' "$$a" | ${GREP} $${i}.so | wc -l ; done | ${SORT} -u) ;\
	if test "$$*" != "1" ; then ${ECHO_CMD} >&2 "${.CURDIR} FAILED: either of ${_tlslibs} libraries linked multiple times" ; ${PRINTF} '%s\n' "$$a"; ${RM} ${BUILD_COOKIE} ; ( set -x ; ldd -a ${WRKSRC}/src/openvpn/openvpn ) ; exit 1 ; fi

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/openvpn/plugins/openvpn-plugin-auth-pam.so
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/openvpn/plugins/openvpn-plugin-down-root.so
	${INSTALL_SCRIPT} ${WRKSRC}/contrib/pull-resolv-conf/client.up ${STAGEDIR}${PREFIX}/libexec/openvpn-client.up
	${INSTALL_SCRIPT} ${WRKSRC}/contrib/pull-resolv-conf/client.down ${STAGEDIR}${PREFIX}/libexec/openvpn-client.down
	@${REINPLACE_CMD} 's|resolvconf -p -a|resolvconf -a|' ${STAGEDIR}${PREFIX}/libexec/openvpn-client.up
	${INSTALL_SCRIPT} ${WRKDIR}/openvpn-client ${STAGEDIR}${PREFIX}/sbin/openvpn-client
	${MKDIR} ${STAGEDIR}${PREFIX}/include

.include <bsd.port.mk>

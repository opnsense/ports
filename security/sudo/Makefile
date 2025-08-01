PORTNAME=	sudo
PORTVERSION=	1.9.17p2
CATEGORIES=	security
MASTER_SITES=	SUDO

MAINTAINER=	garga@FreeBSD.org
COMMENT=	Allow others to run commands as root
WWW=		https://www.sudo.ws/

LICENSE=	sudo
LICENSE_NAME=	Sudo license
LICENSE_FILE=	${WRKSRC}/LICENSE.md
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

FLAVORS=	default sssd
FLAVOR?=	${FLAVORS:[1]}
sssd_PKGNAMESUFFIX=	-sssd

USES=		cpe libtool pkgconfig
CPE_VENDOR=	todd_miller
USE_LDCONFIG=	yes
GNU_CONFIGURE=	yes
GNU_CONFIGURE_MANPREFIX=	${PREFIX}/share
CONFIGURE_ARGS=	--mandir=${PREFIX}/share/man \
		--sysconfdir=${PREFIX}/etc \
		--with-env-editor \
		--with-ignore-dot \
		--with-logfac=${LOGFAC} \
		--with-logincap \
		--with-long-otp-prompt \
		--with-rundir=/var/run/sudo \
		--with-tty-tickets
LDFLAGS+=	-lgcc

PORTSCOUT=	ignore:1

OPTIONS_DEFINE=		AUDIT DISABLE_AUTH DISABLE_ROOT_SUDO DOCS EXAMPLES \
			INSULTS LDAP NLS NOARGS_SHELL OPIE PAM PYTHON SSL
OPTIONS_DEFAULT=	AUDIT PAM SSL
OPTIONS_RADIO=		KERBEROS
OPTIONS_RADIO_KERBEROS=	GSSAPI_BASE GSSAPI_HEIMDAL GSSAPI_MIT
OPTIONS_SUB=		yes

AUDIT_DESC=		Enable BSM audit support
DISABLE_AUTH_DESC=	Do not require authentication by default
DISABLE_ROOT_SUDO_DESC=	Do not allow root to run sudo
INSULTS_DESC=		Enable insults on failures
KERBEROS_DESC=		Enable Kerberos 5 authentication (no PAM support)
NOARGS_SHELL_DESC=	Run a shell if no arguments are given
OPIE_DESC=		Enable one-time passwords (no PAM support)
PYTHON_DESC=		Enable python plugin support
SSL_DESC=		Use OpenSSL TLS and SHA2 functions

AUDIT_CONFIGURE_WITH=	bsm-audit

DISABLE_AUTH_CONFIGURE_ON=	--disable-authentication
DISABLE_ROOT_SUDO_CONFIGURE_ON=	--disable-root-sudo

GSSAPI_BASE_USES=		gssapi
GSSAPI_BASE_CONFIGURE_ON=	--with-kerb5=${GSSAPIBASEDIR} ${GSSAPI_CONFIGURE_ARGS}
GSSAPI_HEIMDAL_USES=		gssapi:heimdal
GSSAPI_HEIMDAL_CONFIGURE_ON=	--with-kerb5=${GSSAPIBASEDIR} ${GSSAPI_CONFIGURE_ARGS}
GSSAPI_MIT_USES=		gssapi:mit
GSSAPI_MIT_CONFIGURE_ON=	--with-kerb5=${GSSAPIBASEDIR} ${GSSAPI_CONFIGURE_ARGS}

INSULTS_CONFIGURE_ON=	--with-insults --with-all-insults

LDAP_USES=		ldap
LDAP_CONFIGURE_ON=	--with-ldap=${PREFIX} \
			--with-ldap-conf-file=${PREFIX}/etc/${SUDO_LDAP_CONF}

NLS_USES=		gettext
NLS_CONFIGURE_ENABLE=	nls
NLS_CFLAGS=		-I${LOCALBASE}/include
NLS_LDFLAGS=		-L${LOCALBASE}/lib -lintl

NOARGS_SHELL_CONFIGURE_ENABLE=	noargs-shell

OPIE_CONFIGURE_ON=	--with-opie

PAM_PREVENTS=		OPIE GSSAPI_BASE GSSAPI_HEIMDAL GSSAPI_MIT
PAM_PREVENTS_MSG=	PAM cannot be combined with any other authentication plugin
PAM_CONFIGURE_ON=	--with-pam

PYTHON_USES=		python
PYTHON_CONFIGURE_ENABLE=python

SSL_USES=		ssl
SSL_CONFIGURE_ON=	--enable-openssl=${OPENSSLBASE}

.if ${FLAVOR:U} == sssd
RUN_DEPENDS+=		sssd:security/sssd2
CONFIGURE_ARGS+=	--with-sssd
.endif

LOGFAC?=		authpriv
SUDO_LDAP_CONF?=	ldap.conf

# This is intentionally not an option.
# SUDO_SECURE_PATH is a PATH string that will override the user's PATH.
# ex: make SUDO_SECURE_PATH="/sbin:/bin:/usr/sbin:/usr/bin"
.if defined(SUDO_SECURE_PATH)
CONFIGURE_ARGS+=	--with-secure-path="${SUDO_SECURE_PATH}"
.endif

# This is intentionally not an option.
# SUDO_KERB5_INSTANCE is an optional instance string that will be appended
# to kerberos principals when to perform authentication. Common choices
# are "admin" and "sudo".
.if defined(SUDO_KERB5_INSTANCE)
CONFIGURE_ARGS+=	--enable-kerb5-instance="${SUDO_KERB5_INSTANCE}"
.endif

.include <bsd.port.options.mk>

.if ${OPSYS} == FreeBSD && ${OSVERSION} >= 1400072
. if ${PORT_OPTIONS:MOPIE}
BUILD_DEPENDS+=	opie>0:security/opie
RUN_DEPENDS+=	opie>0:security/opie
. endif
.endif

.if ${ARCH} == "arm"
CONFIGURE_ARGS+=	--disable-pie
.endif

post-patch:
	@${REINPLACE_CMD} -E '/install-(binaries|noexec):/,/^$$/ \
		s/\$$\(INSTALL\)/& ${STRIP}/;s/-b\~/-b ~/' \
		${WRKSRC}/src/Makefile.in

post-install:
	${INSTALL_DATA} ${FILESDIR}/pam.conf ${STAGEDIR}${PREFIX}/etc/pam.d/sudo.default
	${MV} ${STAGEDIR}${PREFIX}/etc/sudo.conf ${STAGEDIR}${PREFIX}/etc/sudo.conf.sample
	${MV} ${STAGEDIR}${PREFIX}/etc/sudo_logsrvd.conf ${STAGEDIR}${PREFIX}/etc/sudo_logsrvd.conf.sample
	${RM} ${STAGEDIR}${PREFIX}/etc/sudoers
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/cvtsudoers
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/sudoreplay
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/libexec/sudo/sudo_intercept.so
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/sudo_logsrvd
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/sudo_sendlog
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/visudo
.for f in audit_json.so group_file.so libsudo_util.so sudoers.so system_group.so
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/libexec/sudo/${f}
.endfor

post-install-PYTHON-on:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/libexec/sudo/python_plugin.so

.include <bsd.port.mk>

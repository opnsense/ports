PORTNAME=	rearx
DISTVERSIONPREFIX=	v
DISTVERSION=	0.1.4
PORTREVISION=	40
CATEGORIES=	www

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	TUI client for the Searx meta-search engine, written in Rust
WWW=		https://github.com/garak92/rearx

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE.md

USES=		cargo ssl

USE_GITHUB=	yes
GH_ACCOUNT=	garak92

CARGO_CRATES=	\
		arrayref-0.3.6 \
		arrayvec-0.5.2 \
		atty-0.2.14 \
		autocfg-1.0.1 \
		base64-0.13.0 \
		bitflags-1.2.1 \
		blake2b_simd-0.5.11 \
		bstr-0.2.15 \
		bumpalo-3.6.1 \
		byteorder-1.4.3 \
		bytes-1.0.1 \
		cc-1.0.67 \
		cfg-if-1.0.0 \
		clap-2.33.3 \
		constant_time_eq-0.1.5 \
		core-foundation-0.9.1 \
		core-foundation-sys-0.8.2 \
		crossbeam-utils-0.8.3 \
		csv-1.1.6 \
		csv-core-0.1.10 \
		dirs-1.0.5 \
		dtoa-0.4.7 \
		encode_unicode-0.3.6 \
		encoding_rs-0.8.28 \
		fnv-1.0.7 \
		foreign-types-0.3.2 \
		foreign-types-shared-0.1.1 \
		form_urlencoded-1.0.1 \
		futures-channel-0.3.13 \
		futures-core-0.3.13 \
		futures-sink-0.3.13 \
		futures-task-0.3.13 \
		futures-util-0.3.13 \
		gag-0.1.10 \
		getrandom-0.1.16 \
		getrandom-0.2.2 \
		h2-0.3.1 \
		hashbrown-0.9.1 \
		heck-0.3.2 \
		hermit-abi-0.1.18 \
		http-0.2.3 \
		http-body-0.4.0 \
		httparse-1.3.5 \
		httpdate-0.3.2 \
		hyper-0.14.4 \
		hyper-tls-0.5.0 \
		idna-0.2.2 \
		indexmap-1.6.2 \
		instant-0.1.9 \
		ipnet-2.3.0 \
		itoa-0.4.7 \
		js-sys-0.3.48 \
		lazy_static-1.4.0 \
		libc-0.2.88 \
		linked-hash-map-0.5.4 \
		lock_api-0.4.2 \
		log-0.4.14 \
		matches-0.1.8 \
		memchr-2.3.4 \
		mime-0.3.16 \
		mio-0.7.9 \
		miow-0.3.6 \
		native-tls-0.2.7 \
		ntapi-0.3.6 \
		num_cpus-1.13.0 \
		numtoa-0.1.0 \
		once_cell-1.7.2 \
		openssl-0.10.32 \
		openssl-probe-0.1.2 \
		openssl-sys-0.9.60 \
		parking_lot-0.11.1 \
		parking_lot_core-0.8.3 \
		percent-encoding-2.1.0 \
		pin-project-1.0.5 \
		pin-project-internal-1.0.5 \
		pin-project-lite-0.2.6 \
		pin-utils-0.1.0 \
		pkg-config-0.3.19 \
		ppv-lite86-0.2.10 \
		prettytable-rs-0.8.0 \
		proc-macro-error-1.0.4 \
		proc-macro-error-attr-1.0.4 \
		proc-macro2-1.0.24 \
		quote-1.0.9 \
		rand-0.8.3 \
		rand_chacha-0.3.0 \
		rand_core-0.6.2 \
		rand_hc-0.3.0 \
		redox_syscall-0.1.57 \
		redox_syscall-0.2.5 \
		redox_termios-0.1.2 \
		redox_users-0.3.5 \
		regex-automata-0.1.9 \
		remove_dir_all-0.5.3 \
		reqwest-0.11.2 \
		rust-argon2-0.8.3 \
		ryu-1.0.5 \
		schannel-0.1.19 \
		scopeguard-1.1.0 \
		security-framework-2.1.2 \
		security-framework-sys-2.1.1 \
		serde-1.0.124 \
		serde_derive-1.0.124 \
		serde_json-1.0.64 \
		serde_urlencoded-0.7.0 \
		serde_yaml-0.8.17 \
		signal-hook-registry-1.3.0 \
		slab-0.4.2 \
		smallvec-1.6.1 \
		socket2-0.3.19 \
		structopt-0.3.21 \
		structopt-derive-0.4.14 \
		syn-1.0.63 \
		tempfile-3.2.0 \
		term-0.5.2 \
		termion-1.5.6 \
		textwrap-0.11.0 \
		tinyvec-1.1.1 \
		tinyvec_macros-0.1.0 \
		tokio-1.3.0 \
		tokio-macros-1.1.0 \
		tokio-native-tls-0.3.0 \
		tokio-util-0.6.4 \
		tower-service-0.3.1 \
		tracing-0.1.25 \
		tracing-core-0.1.17 \
		try-lock-0.2.3 \
		unicode-bidi-0.3.4 \
		unicode-normalization-0.1.17 \
		unicode-segmentation-1.7.1 \
		unicode-width-0.1.8 \
		unicode-xid-0.2.1 \
		url-2.2.1 \
		vcpkg-0.2.11 \
		version_check-0.9.2 \
		want-0.3.0 \
		wasi-0.9.0+wasi-snapshot-preview1 \
		wasi-0.10.2+wasi-snapshot-preview1 \
		wasm-bindgen-0.2.71 \
		wasm-bindgen-backend-0.2.71 \
		wasm-bindgen-futures-0.4.21 \
		wasm-bindgen-macro-0.2.71 \
		wasm-bindgen-macro-support-0.2.71 \
		wasm-bindgen-shared-0.2.71 \
		web-sys-0.3.48 \
		winapi-0.3.9 \
		winapi-i686-pc-windows-gnu-0.4.0 \
		winapi-x86_64-pc-windows-gnu-0.4.0 \
		winreg-0.7.0 \
		yaml-rust-0.4.5

SUB_LIST=	ETCDIR=${ETCDIR}
SUB_FILES=	pkg-message

.include <bsd.port.options.mk>

.if ( ${OPSYS} == FreeBSD && ${OSVERSION} >= 1400092 && ${SSL_DEFAULT} == base ) || ${SSL_DEFAULT:Mopenssl} || ${SSL_DEFAULT:Mopenssl3*}
BROKEN_SSL=	base openssl openssl31
BROKEN_SSL_REASON=	Fails to detect OpenSSL 3.0.0 and later
.endif

post-patch:
	${REINPLACE_CMD} -e 's|/etc/rearx/rearx.yaml|${PREFIX}/etc/rearx/rearx.yaml|' ${WRKSRC}/src/request.rs

post-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/etc/rearx
	${INSTALL_DATA} ${WRKSRC}/rearx.yaml ${STAGEDIR}${PREFIX}/etc/rearx/rearx.yaml.sample

.include <bsd.port.mk>

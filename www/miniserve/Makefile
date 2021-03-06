PORTNAME=	miniserve
DISTVERSIONPREFIX=	v
DISTVERSION=	0.14.0
PORTREVISION=	2
CATEGORIES=	www

MAINTAINER=	mikael@FreeBSD.org
COMMENT=	Ad-hoc HTTP server for file sharing

LICENSE=	APACHE20 BSD3CLAUSE CC0-1.0 ISCL MIT MPL20 UNLICENSE
LICENSE_COMB=	multi
LICENSE_FILE_MIT=	${WRKSRC}/LICENSE

USES=		cargo ssl:build
USE_GITHUB=	yes
GH_ACCOUNT=	svenstaro

GH_TUPLE=	svenstaro:mime_guess:ac76840e14bc6f2f7cbbb347052ec7e4de7e3043:mime_guess
CARGO_CRATES=	actix-codec-0.3.0 \
		actix-connect-2.0.0 \
		actix-files-0.5.0 \
		actix-http-2.2.0 \
		actix-macros-0.1.3 \
		actix-multipart-0.3.0 \
		actix-router-0.2.7 \
		actix-rt-1.1.1 \
		actix-server-1.0.4 \
		actix-service-1.0.6 \
		actix-testing-1.0.1 \
		actix-threadpool-0.3.3 \
		actix-tls-2.0.0 \
		actix-utils-2.0.0 \
		actix-web-3.3.2 \
		actix-web-codegen-0.4.0 \
		actix-web-httpauth-0.5.1 \
		adler-1.0.2 \
		adler32-1.2.0 \
		ahash-0.3.8 \
		aho-corasick-0.7.15 \
		alphanumeric-sort-1.4.1 \
		ansi_term-0.11.0 \
		ansi_term-0.12.1 \
		assert_cmd-1.0.3 \
		assert_fs-1.0.1 \
		async-trait-0.1.50 \
		atty-0.2.14 \
		autocfg-1.0.1 \
		awc-2.0.3 \
		base-x-0.2.8 \
		base64-0.13.0 \
		beef-0.4.4 \
		bit-set-0.5.2 \
		bit-vec-0.6.3 \
		bitflags-1.2.1 \
		block-buffer-0.9.0 \
		brotli-sys-0.3.2 \
		brotli2-0.3.2 \
		bstr-0.2.15 \
		buf-min-0.4.0 \
		bumpalo-3.6.1 \
		byteorder-1.4.3 \
		bytes-0.5.6 \
		bytes-1.0.1 \
		bytesize-1.0.1 \
		bytestring-1.0.0 \
		bzip2-0.3.3 \
		bzip2-sys-0.1.10+1.0.8 \
		cc-1.0.67 \
		cfg-if-0.1.10 \
		cfg-if-1.0.0 \
		chrono-0.4.19 \
		chrono-humanize-0.1.2 \
		clap-2.33.3 \
		codemap-0.1.3 \
		const_fn-0.4.7 \
		convert_case-0.4.0 \
		cookie-0.14.4 \
		copyless-0.1.5 \
		cpuid-bool-0.1.2 \
		crc32fast-1.2.1 \
		crossbeam-utils-0.8.3 \
		ctor-0.1.20 \
		derive_more-0.99.13 \
		diff-0.1.12 \
		difference-2.0.0 \
		digest-0.9.0 \
		discard-1.0.4 \
		doc-comment-0.3.3 \
		either-1.6.1 \
		encoding_rs-0.8.28 \
		enum-as-inner-0.3.3 \
		filetime-0.2.14 \
		flate2-1.0.20 \
		float-cmp-0.8.0 \
		fnv-1.0.7 \
		form_urlencoded-1.0.1 \
		fuchsia-zircon-0.3.3 \
		fuchsia-zircon-sys-0.3.3 \
		futf-0.1.4 \
		futures-0.3.14 \
		futures-channel-0.3.14 \
		futures-core-0.3.14 \
		futures-executor-0.3.14 \
		futures-io-0.3.14 \
		futures-macro-0.3.14 \
		futures-sink-0.3.14 \
		futures-task-0.3.14 \
		futures-util-0.3.14 \
		fxhash-0.2.1 \
		generic-array-0.14.4 \
		getrandom-0.1.16 \
		getrandom-0.2.2 \
		globset-0.4.6 \
		globwalk-0.8.1 \
		grass-0.10.4 \
		h2-0.2.7 \
		h2-0.3.2 \
		hashbrown-0.8.2 \
		hashbrown-0.9.1 \
		heck-0.3.2 \
		hermit-abi-0.1.18 \
		hex-0.4.3 \
		hostname-0.3.1 \
		html5ever-0.25.1 \
		http-0.2.4 \
		http-body-0.4.1 \
		httparse-1.4.0 \
		httpdate-0.3.2 \
		hyper-0.14.5 \
		hyper-rustls-0.22.1 \
		idna-0.2.3 \
		ignore-0.4.17 \
		indexmap-1.6.2 \
		instant-0.1.9 \
		iovec-0.1.4 \
		ipconfig-0.2.2 \
		ipnet-2.3.0 \
		itoa-0.4.7 \
		js-sys-0.3.50 \
		kernel32-sys-0.2.2 \
		language-tags-0.2.2 \
		lasso-0.3.1 \
		lazy_static-1.4.0 \
		libc-0.2.93 \
		libflate-1.1.0 \
		libflate_lz77-1.1.0 \
		linked-hash-map-0.5.4 \
		lock_api-0.4.3 \
		log-0.4.14 \
		lru-cache-0.1.2 \
		mac-0.1.1 \
		markup5ever-0.10.0 \
		markup5ever_rcdom-0.1.0 \
		match_cfg-0.1.0 \
		matches-0.1.8 \
		maud-0.22.2 \
		maud_htmlescape-0.17.0 \
		maud_macros-0.22.2 \
		memchr-2.3.4 \
		mime-0.3.16 \
		miniz_oxide-0.4.4 \
		mio-0.6.23 \
		mio-0.7.11 \
		mio-uds-0.6.8 \
		miow-0.2.2 \
		miow-0.3.7 \
		nanoid-0.4.0 \
		net2-0.2.37 \
		new_debug_unreachable-1.0.4 \
		nom-4.2.3 \
		normalize-line-endings-0.3.0 \
		ntapi-0.3.6 \
		num-bigint-0.3.2 \
		num-integer-0.1.44 \
		num-rational-0.3.2 \
		num-traits-0.2.14 \
		num_cpus-1.13.0 \
		once_cell-1.7.2 \
		opaque-debug-0.3.0 \
		output_vt100-0.1.2 \
		parking_lot-0.11.1 \
		parking_lot_core-0.8.3 \
		peekmore-0.5.6 \
		percent-encoding-2.1.0 \
		pest-2.1.3 \
		phf-0.8.0 \
		phf_codegen-0.8.0 \
		phf_generator-0.8.0 \
		phf_macros-0.8.0 \
		phf_shared-0.8.0 \
		pin-project-0.4.28 \
		pin-project-1.0.7 \
		pin-project-internal-0.4.28 \
		pin-project-internal-1.0.7 \
		pin-project-lite-0.1.12 \
		pin-project-lite-0.2.6 \
		pin-utils-0.1.0 \
		pkg-config-0.3.19 \
		port_check-0.1.5 \
		ppv-lite86-0.2.10 \
		precomputed-hash-0.1.1 \
		predicates-1.0.7 \
		predicates-core-1.0.2 \
		predicates-tree-1.0.2 \
		pretty_assertions-0.7.2 \
		proc-macro-error-1.0.4 \
		proc-macro-error-attr-1.0.4 \
		proc-macro-hack-0.5.19 \
		proc-macro-nested-0.1.7 \
		proc-macro2-1.0.26 \
		qrcodegen-1.6.0 \
		quick-error-1.2.3 \
		quote-1.0.9 \
		rand-0.7.3 \
		rand-0.8.3 \
		rand_chacha-0.2.2 \
		rand_chacha-0.3.0 \
		rand_core-0.5.1 \
		rand_core-0.6.2 \
		rand_hc-0.2.0 \
		rand_hc-0.3.0 \
		rand_pcg-0.2.1 \
		redox_syscall-0.2.6 \
		regex-1.4.5 \
		regex-automata-0.1.9 \
		regex-syntax-0.6.23 \
		remove_dir_all-0.5.3 \
		reqwest-0.11.3 \
		resolv-conf-0.7.0 \
		ring-0.16.20 \
		rle-decode-fast-1.0.1 \
		rstest-0.7.0 \
		rustc_version-0.2.3 \
		rustc_version-0.3.3 \
		rustls-0.19.1 \
		ryu-1.0.5 \
		same-file-1.0.6 \
		scopeguard-1.1.0 \
		sct-0.6.1 \
		select-0.5.0 \
		semver-0.9.0 \
		semver-0.11.0 \
		semver-parser-0.7.0 \
		semver-parser-0.10.2 \
		serde-1.0.125 \
		serde_derive-1.0.125 \
		serde_json-1.0.64 \
		serde_urlencoded-0.7.0 \
		sha-1-0.9.4 \
		sha1-0.6.0 \
		sha2-0.9.3 \
		signal-hook-registry-1.3.0 \
		simplelog-0.10.0 \
		siphasher-0.3.5 \
		slab-0.4.2 \
		smallvec-1.6.1 \
		socket2-0.3.19 \
		socket2-0.4.0 \
		spin-0.5.2 \
		standback-0.2.17 \
		stdweb-0.4.20 \
		stdweb-derive-0.5.3 \
		stdweb-internal-macros-0.2.9 \
		stdweb-internal-runtime-0.1.5 \
		string_cache-0.8.1 \
		string_cache_codegen-0.5.1 \
		strsim-0.8.0 \
		structopt-0.3.21 \
		structopt-derive-0.4.14 \
		strum-0.20.0 \
		strum_macros-0.20.1 \
		syn-1.0.69 \
		tar-0.4.33 \
		tempfile-3.2.0 \
		tendril-0.4.2 \
		termcolor-1.1.2 \
		textwrap-0.11.0 \
		thiserror-1.0.24 \
		thiserror-impl-1.0.24 \
		thread_local-1.1.3 \
		threadpool-1.8.1 \
		time-0.1.43 \
		time-0.2.26 \
		time-macros-0.1.1 \
		time-macros-impl-0.1.1 \
		tinyvec-1.2.0 \
		tinyvec_macros-0.1.0 \
		tokio-0.2.25 \
		tokio-1.5.0 \
		tokio-rustls-0.22.0 \
		tokio-util-0.3.1 \
		tokio-util-0.6.6 \
		tower-service-0.3.1 \
		tracing-0.1.25 \
		tracing-core-0.1.17 \
		tracing-futures-0.2.5 \
		treeline-0.1.0 \
		trust-dns-proto-0.19.7 \
		trust-dns-resolver-0.19.7 \
		try-lock-0.2.3 \
		twoway-0.2.1 \
		typenum-1.13.0 \
		ucd-trie-0.1.3 \
		unchecked-index-0.2.2 \
		unicase-2.6.0 \
		unicode-bidi-0.3.5 \
		unicode-normalization-0.1.17 \
		unicode-segmentation-1.7.1 \
		unicode-width-0.1.8 \
		unicode-xid-0.2.1 \
		untrusted-0.7.1 \
		url-2.2.1 \
		utf-8-0.7.6 \
		v_escape-0.15.0 \
		v_escape_derive-0.8.4 \
		v_htmlescape-0.12.0 \
		vec_map-0.8.2 \
		version_check-0.1.5 \
		version_check-0.9.3 \
		wait-timeout-0.2.0 \
		walkdir-2.3.2 \
		want-0.3.0 \
		wasi-0.9.0+wasi-snapshot-preview1 \
		wasi-0.10.2+wasi-snapshot-preview1 \
		wasm-bindgen-0.2.73 \
		wasm-bindgen-backend-0.2.73 \
		wasm-bindgen-futures-0.4.23 \
		wasm-bindgen-macro-0.2.73 \
		wasm-bindgen-macro-support-0.2.73 \
		wasm-bindgen-shared-0.2.73 \
		web-sys-0.3.50 \
		webpki-0.21.4 \
		webpki-roots-0.21.1 \
		widestring-0.4.3 \
		winapi-0.2.8 \
		winapi-0.3.9 \
		winapi-build-0.1.1 \
		winapi-i686-pc-windows-gnu-0.4.0 \
		winapi-util-0.1.5 \
		winapi-x86_64-pc-windows-gnu-0.4.0 \
		winreg-0.6.2 \
		winreg-0.7.0 \
		ws2_32-sys-0.2.1 \
		xattr-0.2.2 \
		xml5ever-0.16.1 \
		yansi-0.5.0 \
		zip-0.5.12
CARGO_USE_GITHUB=	yes

# maud_macros uses feature(proc_macro)
MAKE_ENV=	RUSTC_BOOTSTRAP=1

PLIST_FILES=	bin/miniserve
PORTDOCS=	README.md

OPTIONS_DEFINE=	DOCS

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/miniserve

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/README.md ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>

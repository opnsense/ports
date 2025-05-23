PORTNAME=	neocmakelsp
DISTVERSIONPREFIX=	v
DISTVERSION=	0.8.22
CATEGORIES=	lang

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Cmake language server
WWW=		https://github.com/Decodetalkers/neocmakelsp

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	rust-nightly>0:lang/rust-nightly # feature `edition2024` is required

USES=		cargo

USE_GITHUB=	yes
GH_ACCOUNT=	Decodetalkers

CARGO_BUILDDEP=	no
CARGO_CRATES=	addr2line-0.24.2 \
		adler2-2.0.0 \
		aho-corasick-1.1.3 \
		anstream-0.6.18 \
		anstyle-1.0.10 \
		anstyle-parse-0.2.6 \
		anstyle-query-1.1.2 \
		anstyle-wincon-3.0.7 \
		anyhow-1.0.97 \
		assert_cmd-2.0.16 \
		async-trait-0.1.86 \
		auto_impl-1.2.1 \
		autocfg-1.4.0 \
		backtrace-0.3.74 \
		bitflags-1.3.2 \
		bitflags-2.9.0 \
		bstr-1.11.3 \
		bytes-1.10.1 \
		cc-1.2.17 \
		cfg-if-1.0.0 \
		clap-4.5.35 \
		clap_builder-4.5.35 \
		clap_complete-4.5.47 \
		clap_derive-4.5.32 \
		clap_lex-0.7.4 \
		cli-table-0.5.0 \
		cli-table-derive-0.5.0 \
		colorchoice-1.0.3 \
		const-random-0.1.18 \
		const-random-macro-0.1.16 \
		crossbeam-deque-0.8.6 \
		crossbeam-epoch-0.9.18 \
		crossbeam-utils-0.8.21 \
		crunchy-0.2.3 \
		csv-1.3.1 \
		csv-core-0.1.11 \
		dashmap-6.1.0 \
		difflib-0.4.0 \
		displaydoc-0.2.5 \
		dlv-list-0.5.2 \
		doc-comment-0.3.3 \
		equivalent-1.0.2 \
		errno-0.3.10 \
		fastrand-2.3.0 \
		form_urlencoded-1.2.1 \
		futures-0.3.31 \
		futures-channel-0.3.31 \
		futures-core-0.3.31 \
		futures-io-0.3.31 \
		futures-macro-0.3.31 \
		futures-sink-0.3.31 \
		futures-task-0.3.31 \
		futures-util-0.3.31 \
		getrandom-0.2.15 \
		getrandom-0.3.2 \
		gimli-0.31.1 \
		glob-0.3.2 \
		globset-0.4.15 \
		hashbrown-0.14.5 \
		hashbrown-0.15.2 \
		heck-0.5.0 \
		httparse-1.10.0 \
		icu_collections-1.5.0 \
		icu_locid-1.5.0 \
		icu_locid_transform-1.5.0 \
		icu_locid_transform_data-1.5.0 \
		icu_normalizer-1.5.0 \
		icu_normalizer_data-1.5.0 \
		icu_properties-1.5.1 \
		icu_properties_data-1.5.0 \
		icu_provider-1.5.0 \
		icu_provider_macros-1.5.0 \
		idna-1.0.3 \
		idna_adapter-1.2.0 \
		ignore-0.4.23 \
		indexmap-2.8.0 \
		is_executable-1.0.4 \
		is_terminal_polyfill-1.70.1 \
		itoa-1.0.15 \
		lazy_static-1.5.0 \
		libc-0.2.171 \
		linux-raw-sys-0.9.4 \
		litemap-0.7.4 \
		lock_api-0.4.12 \
		log-0.4.25 \
		lsp-types-0.95.1 \
		memchr-2.7.4 \
		miniz_oxide-0.8.5 \
		mio-1.0.3 \
		nu-ansi-term-0.46.0 \
		object-0.36.7 \
		once_cell-1.21.1 \
		ordered-multimap-0.7.3 \
		overload-0.1.1 \
		parking_lot-0.12.3 \
		parking_lot_core-0.9.10 \
		path-absolutize-3.1.1 \
		path-dedot-3.1.1 \
		pathdiff-0.2.3 \
		percent-encoding-2.3.1 \
		pin-project-lite-0.2.16 \
		pin-utils-0.1.0 \
		predicates-3.1.3 \
		predicates-core-1.0.9 \
		predicates-tree-1.0.12 \
		proc-macro2-1.0.94 \
		quote-1.0.40 \
		r-efi-5.2.0 \
		redox_syscall-0.5.10 \
		regex-1.11.1 \
		regex-automata-0.4.9 \
		regex-syntax-0.8.5 \
		rust-ini-0.21.1 \
		rustc-demangle-0.1.24 \
		rustix-1.0.5 \
		ryu-1.0.20 \
		same-file-1.0.6 \
		scopeguard-1.2.0 \
		serde-1.0.219 \
		serde_derive-1.0.219 \
		serde_json-1.0.140 \
		serde_repr-0.1.19 \
		serde_spanned-0.6.8 \
		sharded-slab-0.1.7 \
		shlex-1.3.0 \
		signal-hook-registry-1.4.2 \
		slab-0.4.9 \
		smallvec-1.14.0 \
		socket2-0.5.8 \
		stable_deref_trait-1.2.0 \
		streaming-iterator-0.1.9 \
		strsim-0.11.1 \
		syn-2.0.100 \
		sync_wrapper-1.0.2 \
		synstructure-0.13.1 \
		tempfile-3.19.1 \
		termcolor-1.4.1 \
		termtree-0.5.1 \
		thread_local-1.1.8 \
		tiny-keccak-2.0.2 \
		tinystr-0.7.6 \
		tokio-1.44.2 \
		tokio-macros-2.5.0 \
		tokio-util-0.7.13 \
		toml-0.8.20 \
		toml_datetime-0.6.8 \
		toml_edit-0.22.23 \
		tower-0.5.2 \
		tower-layer-0.3.3 \
		tower-lsp-f-0.21.0 \
		tower-lsp-macros-f-0.9.0 \
		tower-service-0.3.3 \
		tracing-0.1.41 \
		tracing-attributes-0.1.28 \
		tracing-core-0.1.33 \
		tracing-log-0.2.0 \
		tracing-subscriber-0.3.19 \
		tree-sitter-0.25.3 \
		tree-sitter-cmake-0.6.1 \
		tree-sitter-language-0.1.5 \
		treesitter_kind_collector-0.2.0 \
		trim-in-place-0.1.7 \
		unicode-ident-1.0.18 \
		unicode-width-0.2.0 \
		url-2.5.4 \
		utf16_iter-1.0.5 \
		utf8_iter-1.0.4 \
		utf8parse-0.2.2 \
		valuable-0.1.1 \
		wait-timeout-0.2.1 \
		walkdir-2.5.0 \
		wasi-0.11.0+wasi-snapshot-preview1 \
		wasi-0.14.2+wasi-0.2.4 \
		winapi-0.3.9 \
		winapi-i686-pc-windows-gnu-0.4.0 \
		winapi-util-0.1.9 \
		winapi-x86_64-pc-windows-gnu-0.4.0 \
		windows-sys-0.52.0 \
		windows-sys-0.59.0 \
		windows-targets-0.52.6 \
		windows_aarch64_gnullvm-0.52.6 \
		windows_aarch64_msvc-0.52.6 \
		windows_i686_gnu-0.52.6 \
		windows_i686_gnullvm-0.52.6 \
		windows_i686_msvc-0.52.6 \
		windows_x86_64_gnu-0.52.6 \
		windows_x86_64_gnullvm-0.52.6 \
		windows_x86_64_msvc-0.52.6 \
		winnow-0.7.0 \
		wit-bindgen-rt-0.39.0 \
		write16-1.0.0 \
		writeable-0.5.5 \
		yoke-0.7.5 \
		yoke-derive-0.7.5 \
		zerofrom-0.1.5 \
		zerofrom-derive-0.1.5 \
		zerovec-0.10.4 \
		zerovec-derive-0.10.3

PLIST_FILES=	bin/${PORTNAME}

.include <bsd.port.mk>

PORTNAME=	zoxide
DISTVERSIONPREFIX=	v
DISTVERSION=	0.9.8
CATEGORIES=	sysutils

MAINTAINER=	andoriyu@gmail.com
COMMENT=	Fast cd alternative that learns your habits
WWW=		https://github.com/ajeetdsouza/zoxide

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		cargo
USE_GITHUB=	yes
GH_ACCOUNT=	ajeetdsouza

CARGO_CRATES=	aho-corasick-1.1.3 \
		aliasable-0.1.3 \
		anstream-0.6.18 \
		anstyle-1.0.10 \
		anstyle-parse-0.2.6 \
		anstyle-query-1.1.2 \
		anstyle-wincon-3.0.8 \
		anyhow-1.0.98 \
		askama-0.14.0 \
		askama_derive-0.14.0 \
		askama_parser-0.14.0 \
		assert_cmd-2.0.17 \
		bincode-1.3.3 \
		bitflags-2.9.1 \
		bstr-1.12.0 \
		cfg-if-1.0.0 \
		cfg_aliases-0.2.1 \
		clap-4.5.38 \
		clap_builder-4.5.38 \
		clap_complete-4.5.50 \
		clap_complete_fig-4.5.2 \
		clap_complete_nushell-4.5.5 \
		clap_derive-4.5.32 \
		clap_lex-0.7.4 \
		color-print-0.3.7 \
		color-print-proc-macro-0.3.7 \
		colorchoice-1.0.3 \
		difflib-0.4.0 \
		dirs-6.0.0 \
		dirs-sys-0.5.0 \
		doc-comment-0.3.3 \
		dunce-1.0.5 \
		either-1.15.0 \
		env_home-0.1.0 \
		errno-0.3.12 \
		fastrand-2.3.0 \
		getrandom-0.2.16 \
		glob-0.3.2 \
		heck-0.4.1 \
		heck-0.5.0 \
		is_terminal_polyfill-1.70.1 \
		itoa-1.0.15 \
		libc-0.2.172 \
		libredox-0.1.3 \
		linux-raw-sys-0.4.15 \
		linux-raw-sys-0.9.4 \
		memchr-2.7.4 \
		minimal-lexical-0.2.1 \
		nix-0.30.1 \
		nom-7.1.3 \
		once_cell-1.21.3 \
		once_cell_polyfill-1.70.1 \
		option-ext-0.2.0 \
		ouroboros-0.18.5 \
		ouroboros_macro-0.18.5 \
		percent-encoding-2.3.1 \
		ppv-lite86-0.2.21 \
		predicates-3.1.3 \
		predicates-core-1.0.9 \
		predicates-tree-1.0.12 \
		proc-macro2-1.0.95 \
		proc-macro2-diagnostics-0.10.1 \
		quote-1.0.40 \
		rand-0.8.5 \
		rand_chacha-0.3.1 \
		rand_core-0.6.4 \
		redox_users-0.5.0 \
		regex-1.11.1 \
		regex-automata-0.4.9 \
		regex-syntax-0.8.5 \
		relative-path-1.9.3 \
		rstest-0.25.0 \
		rstest_macros-0.25.0 \
		rstest_reuse-0.7.0 \
		rustc-hash-2.1.1 \
		rustc_version-0.4.1 \
		rustix-0.38.44 \
		rustix-1.0.7 \
		ryu-1.0.20 \
		semver-1.0.26 \
		serde-1.0.219 \
		serde_derive-1.0.219 \
		serde_json-1.0.140 \
		static_assertions-1.1.0 \
		strsim-0.11.1 \
		syn-2.0.101 \
		tempfile-3.15.0 \
		termtree-0.5.1 \
		thiserror-2.0.12 \
		thiserror-impl-2.0.12 \
		unicode-ident-1.0.18 \
		utf8parse-0.2.2 \
		version_check-0.9.5 \
		wait-timeout-0.2.1 \
		wasi-0.11.0+wasi-snapshot-preview1 \
		which-7.0.3 \
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
		winnow-0.7.10 \
		winsafe-0.0.19 \
		yansi-1.0.1 \
		zerocopy-0.8.25 \
		zerocopy-derive-0.8.25

post-install:
	${INSTALL_MAN} ${WRKSRC}/man/man1/* ${STAGEDIR}${PREFIX}/share/man/man1

.include <bsd.port.mk>

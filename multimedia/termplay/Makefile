PORTNAME=	termplay
DISTVERSION=	2.0.6
PORTREVISION=	45
CATEGORIES=	multimedia
MASTER_SITES=	CRATESIO
DISTFILES=	${CARGO_DIST_SUBDIR}/${DISTNAME}${CARGO_CRATE_EXT}

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Tool that converts images to ANSI sequences, plays videos in terminals
WWW=		https://github.com/jD91mZM2/termplay

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libsixel.so:graphics/libsixel

USES=		cargo gnome gstreamer
USE_GNOME=	glib20

CARGO_FEATURES=	bin
CARGO_CRATES=	\
		adler32-1.0.4 \
		ansi_term-0.11.0 \
		atty-0.2.14 \
		autocfg-0.1.7 \
		backtrace-0.3.40 \
		backtrace-sys-0.1.32 \
		bitflags-1.2.1 \
		byteorder-1.3.2 \
		cc-1.0.49 \
		cfg-if-0.1.10 \
		clap-2.33.0 \
		color_quant-1.0.1 \
		crc32fast-1.2.0 \
		crossbeam-deque-0.7.2 \
		crossbeam-epoch-0.8.0 \
		crossbeam-queue-0.2.1 \
		crossbeam-utils-0.7.0 \
		deflate-0.7.20 \
		either-1.5.3 \
		failure-0.1.6 \
		failure_derive-0.1.6 \
		futures-channel-0.3.1 \
		futures-core-0.3.1 \
		futures-executor-0.3.1 \
		futures-macro-0.3.1 \
		futures-task-0.3.1 \
		futures-util-0.3.1 \
		gif-0.10.3 \
		glib-0.9.0 \
		glib-sys-0.9.1 \
		gobject-sys-0.9.1 \
		gstreamer-0.15.0 \
		gstreamer-app-0.15.0 \
		gstreamer-app-sys-0.8.1 \
		gstreamer-base-0.15.0 \
		gstreamer-base-sys-0.8.1 \
		gstreamer-sys-0.8.1 \
		hermit-abi-0.1.6 \
		image-0.22.3 \
		inflate-0.4.5 \
		jpeg-decoder-0.1.18 \
		lazy_static-1.4.0 \
		libc-0.2.66 \
		lzw-0.10.0 \
		memoffset-0.5.3 \
		muldiv-0.2.1 \
		num-derive-0.2.5 \
		num-integer-0.1.41 \
		num-iter-0.1.39 \
		num-rational-0.2.2 \
		num-traits-0.2.10 \
		num_cpus-1.11.1 \
		numtoa-0.1.0 \
		paste-0.1.6 \
		paste-impl-0.1.6 \
		pin-utils-0.1.0-alpha.4 \
		pkg-config-0.3.17 \
		png-0.15.2 \
		proc-macro-hack-0.5.11 \
		proc-macro-nested-0.1.3 \
		proc-macro2-0.4.30 \
		proc-macro2-1.0.7 \
		quote-0.6.13 \
		quote-1.0.2 \
		rayon-1.3.0 \
		rayon-core-1.7.0 \
		redox_syscall-0.1.56 \
		redox_termios-0.1.1 \
		rustc-demangle-0.1.16 \
		rustc_version-0.2.3 \
		scoped_threadpool-0.1.9 \
		scopeguard-1.0.0 \
		semver-0.9.0 \
		semver-parser-0.7.0 \
		slab-0.4.2 \
		strsim-0.8.0 \
		syn-0.15.44 \
		syn-1.0.13 \
		synstructure-0.12.3 \
		termion-1.5.4 \
		textwrap-0.11.0 \
		tiff-0.3.1 \
		unicode-width-0.1.7 \
		unicode-xid-0.1.0 \
		unicode-xid-0.2.0 \
		vec_map-0.8.1 \
		winapi-0.3.8 \
		winapi-i686-pc-windows-gnu-0.4.0 \
		winapi-x86_64-pc-windows-gnu-0.4.0

PLIST_FILES=	bin/${PORTNAME}

.include <bsd.port.mk>

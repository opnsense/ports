PORTNAME=	netflector
DISTVERSIONPREFIX=	v
DISTVERSION=	0.15.2
PORTREVISION=	1
CATEGORIES=	net

MAINTAINER=	sergii@bogomolov.io
COMMENT=	Reflect link-local service discovery between interfaces
WWW=		https://github.com/netflector/netflector

LICENSE=	BSD2CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	aarch64 amd64
ONLY_FOR_ARCHS_REASON=	packs a 64-bit reactor key into kevent's pointer-sized udata (compile-time assert); untested beyond aarch64 and amd64

USES=		cargo
USE_GITHUB=	yes

USE_RC_SUBR=	netflector
CARGO_CRATES=	equivalent-1.0.2 \
		hashbrown-0.17.1 \
		indexmap-2.14.0 \
		libc-0.2.189 \
		log-0.4.33 \
		proc-macro2-1.0.106 \
		quote-1.0.45 \
		serde-1.0.229 \
		serde_core-1.0.229 \
		serde_derive-1.0.229 \
		serde_spanned-1.1.1 \
		syn-3.0.0 \
		thiserror-2.0.20 \
		thiserror-impl-2.0.20 \
		toml-1.1.4+spec-1.1.0 \
		toml_datetime-1.1.1+spec-1.1.0 \
		toml_parser-1.1.3+spec-1.1.0 \
		toml_writer-1.1.2+spec-1.1.0 \
		unicode-ident-1.0.24 \
		winnow-1.0.3

SUB_FILES=	netflector.toml.sample pkg-message

PLIST_FILES=	bin/netflector \
		"@sample etc/netflector.toml.sample" \
		share/man/man5/netflector.toml.5.gz \
		share/man/man8/netflector.8.gz

post-install:
	${INSTALL_DATA} ${WRKDIR}/netflector.toml.sample ${STAGEDIR}${PREFIX}/etc
	${INSTALL_MAN} ${WRKSRC}/man/netflector.8 ${STAGEDIR}${PREFIX}/share/man/man8
	${INSTALL_MAN} ${WRKSRC}/man/netflector.toml.5 ${STAGEDIR}${PREFIX}/share/man/man5

.include <bsd.port.mk>

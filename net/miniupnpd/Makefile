PORTNAME=	miniupnpd
DISTVERSION=	2.3.10
PORTEPOCH=	1
CATEGORIES=	net
MASTER_SITES=	https://miniupnp.tuxfamily.org/files/ \
		https://github.com/miniupnp/miniupnp/releases/download/${PORTNAME}_${DISTVERSION:S|.|_|g}/

PATCH_SITES=	https://github.com/Self-Hosting-Group/miniupnp/commit/
# Backport: Makefile.bsd: fix linking of teststun with --libpfctl:
PATCHFILES=	74ebc28c0a64ee886d5e8923aa0b6cddef2adb82.patch:-p2
# miniupnpd: UPnP IGDv2 Microsoft/Apple compatibility:
PATCHFILES+=	7adadd181b52f46c4aff3d97b3186c9345594137.patch:-p2
# miniupnpd: Improve startup banner and add security warnings:
PATCHFILES+=	15c578035e975242da49f4448cc549db8dc72b27.patch:-p2
# miniupnpd: Less excessive logging by default:
PATCHFILES+=	38e01919d585b0fd663d2b3249963b336061cbd3.patch:-p2

MAINTAINER=	squat@squat.no
COMMENT=	Lightweight UPnP IGD & PCP/NAT-PMP daemon which uses pf
WWW=		https://miniupnp.tuxfamily.org/

LICENSE=	BSD3CLAUSE

LIB_DEPENDS=	libpfctl.so:net/libpfctl

USES=		cpe
CPE_VENDOR=	miniupnp_project

USE_RC_SUBR=	${PORTNAME}

HAS_CONFIGURE=	yes
# unconditionally use pf, ipfw does not work on FreeBSD
CONFIGURE_ARGS=	--disable-pppconn --firewall=pf --libpfctl --vendorcfg
MAKE_ENV=	MANPREFIX=${PREFIX}/share
MAKE_JOBS_UNSAFE=	yes

PLIST_FILES=	etc/miniupnpd.conf.sample \
		share/man/man8/miniupnpd.8.gz \
		sbin/miniupnpd

OPTIONS_DEFINE=		CHECK_PORTINUSE IPV6 LEASEFILE UPNP_IGDV2 UPNP_STRICT
CHECK_PORTINUSE_DESC=		Check if ports are in use
LEASEFILE_DESC=			Enable lease file
UPNP_IGDV2_DESC=		Build an IGDv2 instead of an IGDv1
UPNP_STRICT_DESC=		More strict UPnP specification compliance

CHECK_PORTINUSE_CONFIGURE_ON=	--portinuse
IPV6_CONFIGURE_ON=		--ipv6
LEASEFILE_CONFIGURE_ON=		--leasefile
UPNP_IGDV2_CONFIGURE_ON=	--igd2
UPNP_STRICT_CONFIGURE_ON=	--strict

.include <bsd.port.mk>

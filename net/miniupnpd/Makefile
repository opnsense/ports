PORTNAME=	miniupnpd
DISTVERSION=	2.3.11
PORTEPOCH=	1
CATEGORIES=	net
MASTER_SITES=	http://miniupnp.free.fr/files/ \
		https://github.com/miniupnp/miniupnp/releases/download/${PORTNAME}_${DISTVERSION:S|.|_|g}/

# Backport commits from release to 671e5c0a81d8afd3fee94b33c8fc10f558a6b033 (2026-08-29)
PATCH_SITES=	https://github.com/miniupnp/miniupnp/compare/
PATCHFILES=	miniupnpd_2_3_11...671e5c0a81d8afd3fee94b33c8fc10f558a6b033.patch:-p2

PATCH_SITES+=	https://github.com/Self-Hosting-Group/miniupnp/commit/
# miniupnpd: UPnP IGDv2 Microsoft/Apple compatibility
PATCHFILES+=	f94e5bf7a60a41911af8d7e23cdb4ebe166257e2.patch:-p2
# miniupnpd: Improve start banner and add security warnings
PATCHFILES+=	9589d513e6f7d3e957c2aef67320d93200c710de.patch:-p2
# miniupnpd: Less excessive logging by default
PATCHFILES+=	0fa8265e19ddb2a34b4260306a8b0c2971736cdd.patch:-p2
# miniupnpd: Log IPv4 mapping disabled/enabled messages by default
PATCHFILES+=	4ab86cce25c2a3fad6845d324aad29783c2fe390.patch:-p2
# miniupnpd: Fix IPv4 mapping re-enable after network down/up on CGNAT
PATCHFILES+=	12eac8afebbedcbd5d984e8e105fa74dc0dee394.patch:-p2
# miniupnpd: No IPv4 mapping disabled logging on requests, but more cases
PATCHFILES+=	be8cd00eddb2f974debbc72ac1329260d08ca5f5.patch:-p2
# miniupnpd: Clearer IPv4 mapping disabled/enabled logging
#PATCHFILES+=	22a056e0c4b7c117bd2e0c06e93771c3961dcb15.patch:-p2

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

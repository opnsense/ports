PORTNAME=	pfSense
PORTVERSION=	0.1
PORTREVISION=	1
CATEGORIES=	devel
MASTER_SITES=
DISTFILES=
PKGNAMEPREFIX=	php-

MAINTAINER=	franco@lastsummer.de
COMMENT=	Library for getting useful info

USE_PHP=	yes
USE_PHPEXT=	yes

BUILD_DEPENDS=	dhcpd:${PORTSDIR}/net/isc-dhcp42-server

MAKE_ARGS=      CC="${CC}" CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}"
#CFLAGS+=	-I/usr/local/include -L/usr/local/lib -I. -DDHCP_INTEGRATION -DIPFW_FUNCTIONS
#LDFLAGS+=	-lomapi -ldhcpctl -ldns-dhcp -lisc-dhcp
CFLAGS+=	-I/usr/local/include -L/usr/local/lib -I. 

CONFIGURE_ARGS=	--enable-pfSense

extract:
	mkdir -p ${WRKSRC}
	cp -r files/* ${WRKSRC}

post-install:
	cp ${WRKSRC}/modules/pfSense.so /usr/local/lib/php/${PHP_EXT_DIR}/

.include <bsd.port.mk>

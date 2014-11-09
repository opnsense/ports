
PORTNAME=		zmq
PORTVERSION=	0.9.0
PORTREVISION?=	0
CATEGORIES?=	lang
MASTER_SITES=	# empty
DISTFILES=		# none
EXTRACT_ONLY=	# empty
#NO_STAGE=	yes

MAINTAINER?=	sullrich@gmail.com
COMMENT?=		run various pfSense scripts on event.

#WHERE=		sbin
#PLIST_FILES=    ${WHERE}/${PORTNAME}
USE_PHP=        yes
USE_PHPEXT=     yes
CONFIGURE_ARGS= --with-zmq=/usr/local/lib/php/${PHP_EXT_DIR}/

extract:
	mkdir -p ${WRKSRC}
	cp -r files/* ${WRKSRC}

post-install:
	cp ${WRKSRC}/modules/zmq.so /usr/local/lib/php/${PHP_EXT_DIR}/

.include <bsd.port.mk>

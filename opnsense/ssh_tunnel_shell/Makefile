PORTNAME=	ssh_tunnel_shell
PORTVERSION=	0.1
PORTREVISION=	3
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@lastsummer.de
COMMENT=	SSH Tunneling Shell

do-extract:
	mkdir -p ${WRKSRC}

do-build:
	${CC} ${CFLAGS} -static -o ${WRKSRC}/ssh_tunnel_shell ${FILESDIR}/ssh_tunnel_shell.c

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/sbin
	${INSTALL_PROGRAM} ${WRKSRC}/ssh_tunnel_shell ${STAGEDIR}${PREFIX}/sbin

.include <bsd.port.mk>

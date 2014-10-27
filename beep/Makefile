# New ports collection makefile for:	beep
# Date Created:				June 9, 2002
# Whom:					Tyler Spivey
#
# $FreeBSD: ports/audio/beep/Makefile,v 1.8 2006/05/22 20:40:52 ehaupt Exp $

PORTNAME=	beep
PORTVERSION=	1.0
CATEGORIES=	audio
MASTER_SITES=	http://freebsd.unixfreunde.de/sources/ \
		http://ftp.osuosl.org/pub/FreeBSD/distfiles/

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Beeps a certain duration and pitch out of the PC Speaker

MAN1=		beep.1
MANCOMPRESSED=	maybe
WRKSRC=		${WRKDIR}/${PORTNAME}

ONLY_FOR_ARCHS=	i386 amd64 pc98

PLIST_FILES=	bin/beep

post-patch:	.SILENT
	${REINPLACE_CMD} 's|machine/speaker\.h|dev/speaker/speaker.h|' \
		${WRKSRC}/beep.c

.include <bsd.port.mk>

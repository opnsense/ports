PORTNAME=	artifactory
DISTVERSION=	5.8.3
PORTREVISION=	1
CATEGORIES=	devel java
MASTER_SITES=	https://bintray.com/artifact/download/jfrog/artifactory/
DISTNAME=	jfrog-${PORTNAME}-oss-${PORTVERSION}

MAINTAINER=	dharrigan@gmail.com
COMMENT=	Universal Artifact Repository Manager
WWW=		https://www.jfrog.com/artifactory

LICENSE=	GPLv3 APACHE20
LICENSE_COMB=	multi
LICENSE_FILE_GPLv3=	${WRKSRC}/COPYING.AFFERO
LICENSE_FILE_APACHE20=	${WRKSRC}/tomcat/LICENSE

FORBIDDEN=	Ships a very vulnerable Tomcat 8.5.23
DEPRECATED=	Outdated with known vulnerabilities and marked as forbidden in 2023
EXPIRATION_DATE=2025-05-31

RUN_DEPENDS=	bash:shells/bash

WRKSRC=		${WRKDIR}/${PORTNAME}-oss-${PORTVERSION}

USES=		cpe java shebangfix zip
CPE_VENDOR=	jfrog
SHEBANG_FILES=	bin/artifactory.sh
JAVA_VENDOR=	openjdk
NO_BUILD=	yes
NO_ARCH=	yes
USE_RC_SUBR=	${PORTNAME}

APP_NAME=	${PORTNAME}
APP_HOME?=	${PORTNAME}
PID_FILE?=	/var/run/${PORTNAME}.pid
VARDIR=		/var/${PORTNAME}

USERS=		artifactory
GROUPS=		artifactory

SUB_LIST=	APP_HOME=${PREFIX}/${APP_HOME} \
		APP_NAME=${APP_NAME} \
		PID_FILE=${PID_FILE} \
		VARDIR=${VARDIR}

SUB_FILES=	pkg-message \

PLIST_SUB=	APP_HOME=${APP_HOME} \
		VARDIR=${VARDIR}

do-install:
.for f in artifactory-service.exe artifactory.bat installService.bat \
	uninstallService.bat
	${RM} ${WRKSRC}/bin/${f}
.endfor
	${RM} ${WRKSRC}/tomcat/bin/*.bat

	${MKDIR} ${STAGEDIR}${PREFIX}/${APP_HOME}
	(cd ${WRKSRC} && ${COPYTREE_SHARE} . ${STAGEDIR}${PREFIX}/${APP_HOME})

	${MKDIR} ${STAGEDIR}/${VARDIR}/tomcat/logs/catalina
	${LN} -sf ${VARDIR}/tomcat/logs/catalina ${STAGEDIR}${PREFIX}/${APP_HOME}/tomcat/logs

.for d in etc logs
	${MV} ${STAGEDIR}${PREFIX}/${APP_HOME}/${d} ${STAGEDIR}/${VARDIR}
	${LN} -sf ${VARDIR}/${d} ${STAGEDIR}${PREFIX}/${APP_HOME}/${d}
.endfor

.for d in temp webapps work
	${MV} ${STAGEDIR}${PREFIX}/${APP_HOME}/tomcat/${d} ${STAGEDIR}/${VARDIR}/tomcat
	${LN} -sf ${VARDIR}/tomcat/${d} ${STAGEDIR}${PREFIX}/${APP_HOME}/tomcat/${d}
.endfor

.for d in data backup support access
	${MKDIR} ${STAGEDIR}/${VARDIR}/${d}
	${LN} -sf ${VARDIR}/${d} ${STAGEDIR}${PREFIX}/${APP_HOME}/${d}
.endfor

.include <bsd.port.mk>

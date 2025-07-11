PORTNAME=	csound
DISTVERSION=	6.15.0
PORTREVISION=	11
CATEGORIES=	audio lang

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Sound synthesizer
WWW=		https://csound.com/

LICENSE=	LGPL21+
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	boost-libs>0:devel/boost-libs \
		swig:devel/swig \
		gmm++>0:math/gmm++
LIB_DEPENDS=	libsamplerate.so:audio/libsamplerate \
		libsndfile.so:audio/libsndfile

USES=		alias bison cmake compiler:c++11-lib cpe eigen:3 localbase ncurses python:build # is python needed: https://github.com/csound/csound/issues/1437 ?
USE_GITHUB=	yes
USE_LDCONFIG=	yes

CPE_VENDOR=	csounds

CONFLICTS_INSTALL= clearsilver go-cs libextractor outguess

CFLAGS_powerpc=	-maltivec
CFLAGS_powerpcspe=	-DPFFFT_SIMD_DISABLE
CMAKE_ARGS=	-DBUILD_CSOUNDVST:BOOL=OFF \
		-DBUILD_PD_CLASS:BOOL=OFF \
		-DPYTHON_MODULE_INSTALL_DIR:PATH="${PYTHONPREFIX_SITELIBDIR}" \
		-DOPSYS:STRING="${OPSYS}"
CMAKE_OFF=	USE_ALSA BUILD_JAVA_INTERFACE BUILD_TESTS
SSP_UNSAFE=	yes
LDFLAGS+=	-lexecinfo

SUB_FILES=	pkg-message

OPTIONS_DEFINE=		CURL FLTK HDF5 NLS OPENMP PORTAUDIO PULSEAUDIO
OPTIONS_GROUP=		OPCODES # list is in Opcodes/CMakeLists.txt
OPTIONS_GROUP_OPCODES=	BUCHLA CHUA COUNTER DSSI EXCITER FAUST FLUIDSYNTH IMAGE JACK LUA LINALG MP3OUT OSC P5GLOVE PADSYNTH PLATEREV PVSGENDY PYTHON SCANSYN SELECT SERIAL STACK STK VST4CS WIIMOTE # Opcodes/CMakeLists.txt, Opcodes/stk/CMakeLists.txt
OPTIONS_DEFAULT=	FLTK OPENMP
OPTIONS_DEFAULT+=	BUCHLA CHUA DSSI EXCITER FAUST IMAGE JACK LINALG OSC P5GLOVE PADSYNTH PLATEREV SCANSYN SELECT SERIAL STACK STK # for OPCODES
OPTIONS_SUB=		yes

OPCODES_DESC=		Build/install opcodes

BUCHLA_DESC=		Build the Buchla filter opcode
BUCHLA_CMAKE_BOOL=	BUILD_BUCHLA_OPCODES

CHUA_DESC=		Build the chua opcodes
CHUA_CMAKE_BOOL=	BUILD_CHUA_OPCODES

COUNTER_DESC=		Build the serial opcode
COUNTER_CMAKE_BOOL=	BUILD_COUNTER_OPCODES

CURL_CMAKE_BOOL=	USE_CURL # see https://github.com/csound/csound/issues/1067
CURL_LIB_DEPENDS=	libcurl.so:ftp/curl

DSSI_DESC=		Build DSSI opcodes
DSSI_BUILD_DEPENDS=	dssi>0:audio/dssi
DSSI_LIB_DEPENDS=	libdssialsacompat.so:audio/libdssialsacompat
DSSI_RUN_DEPENDS=	dssi>0:audio/dssi
DSSI_CMAKE_BOOL=	BUILD_DSSI_OPCODES
DSSI_CFLAGS=		-isystem ${LOCALBASE}/include/dssi

EXCITER_DESC=		Build the exciter opcode
EXCITER_CMAKE_BOOL=	BUILD_EXCITER_OPCODES

FLTK_DESC=		Build FLTK plugin and GUI
FLTK_USES=		xorg
FLTK_USE=		XORG=ice,sm,x11,xext
FLTK_LIB_DEPENDS=	libfltk.so:x11-toolkits/fltk
FLTK_CMAKE_ON=		-DBUILD_WINSOUND:BOOL=ON
FLTK_CMAKE_OFF=		-DBUILD_CSOUND_AC:BOOL=OFF \
			-DBUILD_VIRTUAL_KEYBOARD:BOOL=OFF \
			-DUSE_FLTK:BOOL=OFF

FAUST_DESC=		Build the Faust opcodes
FAUST_USES=		ssl
FAUST_LLVM_VERSION=	11 # should be the same as in audio/faust
FAUST_LIB_DEPENDS=	libfaust.so:audio/faust
FAUST_CMAKE_BOOL=	BUILD_FAUST_OPCODES
FAUST_CMAKE_ON=		-DFAUST_LLVM_VERSION:STRING=${FAUST_LLVM_VERSION}

FLUIDSYNTH_DESC=	Building FluidSynth opcodes
FLUIDSYNTH_LIB_DEPENDS=	libfluidsynth.so:audio/fluidsynth
FLUIDSYNTH_CMAKE_BOOL=	BUILD_FLUID_OPCODES
FLUIDSYNTH_BROKEN=	FluidSynth 2.x is broken upstream: https://github.com/csound/csound/issues/1078#issuecomment-441459803

HDF5_DESC=		Build HDF5 read/write plugin
HDF5_LIB_DEPENDS=	libhdf5.so:science/hdf5 \
			libsz.so:science/libaec
HDF5_CMAKE_BOOL=	BUILD_HDF5_OPCODES

JACK_DESC=		Build the JACK related opcodes
JACK_LIB_DEPENDS=	libjack.so:audio/jack
JACK_CMAKE_BOOL=	BUILD_JACK_OPCODES USE_JACK

LINALG_DESC=		Build the linear algebra opcodes
LINALG_CMAKE_BOOL=	BUILD_LINEAR_ALGEBRA_OPCODES
LINALG_CXXFLAGS=	-DGMM_VERSION=x # workaround based on https://github.com/csound/csound/issues/1069#issuecomment-439648756

LUA_DESC=		Build Lua Interface and module
LUA_LIB_DEPENDS=	libluajit-5.1.so:lang/luajit
LUA_CMAKE_BOOL=		BUILD_CSOUND_AC_LUA_INTERFACE BUILD_LUA_INTERFACE BUILD_LUA_OPCODES

NLS_USES=		gettext
NLS_CMAKE_OFF=		-DGETTEXT_MSGFMT_EXECUTABLE:FILEPATH="" \
			-DGETTEXT_MSGMERGE_EXECUTABLE:FILEPATH="" \
			-DLIBINTL_LIBRARY:FILEPATH="" \
			-DUSE_GETTEXT:BOOL=OFF

OPENMP_CMAKE_BOOL=	USE_OPEN_MP

MP3OUT_DESC=		Build MP3OUT opcodes
MP3OUT_CMAKE_BOOL=	BUILD_MP3OUT_OPCODE

OSC_DESC=		Build OSC opcodes
OSC_LIB_DEPENDS=	liblo.so:audio/liblo
OSC_CMAKE_BOOL=		BUILD_OSC_OPCODES

PADSYNTH_DESC=		Build the Padsynth opcode
PADSYNTH_CMAKE_BOOL=	BUILD_PADSYNTH_OPCODES

IMAGE_DESC=		Build Image opcodes
IMAGE_LIB_DEPENDS=	libpng.so:graphics/png
IMAGE_CMAKE_BOOL=	BUILD_IMAGE_OPCODES

P5GLOVE_DESC=		Build PortAudio I/O module
P5GLOVE_CMAKE_BOOL=	BUILD_P5GLOVE_OPCODES

PORTAUDIO_DESC=		Build PortAudio I/O module
PORTAUDIO_LIB_DEPENDS=	libportaudio.so:audio/portaudio
PORTAUDIO_CMAKE_BOOL=	USE_PORTAUDIO

PULSEAUDIO_DESC=	Build PulseAudio I/O module
PULSEAUDIO_LIB_DEPENDS=	libpulse-simple.so:audio/pulseaudio
PULSEAUDIO_CMAKE_BOOL=	USE_PULSEAUDIO

PLATEREV_DESC=		Build the platerev opcode
PLATEREV_CMAKE_BOOL=	BUILD_PLATEREV_OPCODES

PVSGENDY_DESC=		Build the pvsgendy opcode
PVSGENDY_CMAKE_BOOL=	BUILD_PVSGENDY_OPCODE

PYTHON_DESC=		Build the Python opcodes
PYTHON_USES=		python
PYTHON_CMAKE_BOOL=	BUILD_PYTHON_OPCODES

SCANSYN_DESC=		Build the select opcodes
SCANSYN_CMAKE_BOOL=	BUILD_SCANSYN_OPCODES

SELECT_DESC=		Build the select opcode
SELECT_CMAKE_BOOL=	BUILD_SELECT_OPCODE

SERIAL_DESC=		Build the serial opcode
SERIAL_CMAKE_BOOL=	BUILD_SERIAL_OPCODES

STACK_DESC=		Build the stack opcodes
STACK_CMAKE_BOOL=	BUILD_STACK_OPCODES

STK_DESC=		Build the stk opcodes
STK_CMAKE_BOOL=		BUILD_STK_OPCODES
STK_LIB_DEPENDS=	libstk.so:audio/stk

VST4CS_DESC=		Build the vst4cs opcodes
VST4CS_CMAKE_BOOL=	BUILD_VST4CS_OPCODES

WIIMOTE_DESC=		Build the Wiimote opcodes
WIIMOTE_CMAKE_BOOL=	BUILD_WIIMOTE_OPCODES
WIIMOTE_BROKEN=		Need to port wiiuse: https://github.com/rpavlik/wiiuse

post-patch:
	@${REINPLACE_CMD} -e \
		's|/usr/include/Python2.7|${PYTHON_INCLUDEDIR}| ; \
		 s|/usr/local|${LOCALBASE}| ; \
		 /linuxjoystick/s|^|#| ; \
		 s| dl)|)|' \
		${WRKSRC}/Opcodes/CMakeLists.txt
	@${REINPLACE_CMD} -e \
		'/CMAKE_SYSTEM_NAME/s|"Linux"|"${OPSYS}"|' \
		${WRKSRC}/Frontends/CMakeLists.txt
	@${REINPLACE_CMD} -e \
		's| mixer)| csmixer)|' \
		${WRKSRC}/util/CMakeLists.txt

post-install:
	@${LN} -sf libcsnd6.so.6.0 ${STAGEDIR}${PREFIX}/lib/libcsnd6.so.6
	@${LN} -sf libcsound64.so.6.0 ${STAGEDIR}${PREFIX}/lib/libcsound64.so.6

post-install-FLTK-on:
	@${LN} -sf libCsoundAC.so.6.0 ${STAGEDIR}${PREFIX}/lib/libCsoundAC.so.6

.include <bsd.port.mk>

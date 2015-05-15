# Makefile for luadfui.
# $Id: Makefile,v 1.13 2005/08/26 22:44:37 cpressey Exp $

BASE?=../../..
include ${BASE}/Config

LUA=../../../lua

COMPAT?=../compat-5.1

LIB=	ldfui.so
OBJS=	common.o dfui.o progress.o

CFLAGS+=	${WARNS} -fPIC -I/usr/local/include
CFLAGS+=	-I${LUA}/include -I${COMPAT} -I../../libdfui
CFLAGS+=	${EXTRA_CFLAGS}
LDFLAGS+=	-L../../libdfui -L${LUA}/lib/
LDFLAGS+=	-ldfui -lm -llua50 -llualib50

all: ${LIB}

${LIB}: ${OBJS}
	${CC} ${OBJS} ${COMPAT}/compat-5.1.o -shared ${LDFLAGS} -o ${LIB}

strip: ${LIB}
	${STRIP} ${LIB}

clean:
	rm -f *.o *.so

install: strip
	mkdir -p ${DESTDIR}${PREFIX}/lib/lua/5.0
	cp ${LIB} ${DESTDIR}${PREFIX}/lib/lua/5.0
	mkdir -p ${DESTDIR}${PREFIX}/share/lua/5.0
	cp dfui.lua ${DESTDIR}${PREFIX}/share/lua/5.0

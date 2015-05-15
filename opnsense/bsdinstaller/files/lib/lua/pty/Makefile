# $Id: Makefile,v 1.11 2005/08/26 22:44:38 cpressey Exp $

BASE?=../../..
include ${BASE}/Config

LUA?=../../../lua

COMPAT?=../compat-5.1

CFLAGS+=	${WARNS} -fPIC -I../ -I${LUA}/include -I/usr/local/include
LDFLAGS+=	-L${LUA}/lib -L/usr/local/lib -lutil -lm -llua50 -llualib50

LIB=	lpty.so
OBJS=	pty.o

all: ${LIB}

strip: ${LIB}
	strip ${LIB}

${LIB}: ${OBJS}
	${CC} ${OBJS} ${COMPAT}/compat-5.1.o -shared ${LDFLAGS} -o ${LIB}

pty.o: pty.c
	${CC} ${CFLAGS} -c pty.c -o pty.o

clean:
	rm -rf *.so *.o

install: strip
	mkdir -p ${DESTDIR}${PREFIX}/lib/lua/5.0
	cp ${LIB} ${DESTDIR}${PREFIX}/lib/lua/5.0
	mkdir -p ${DESTDIR}${PREFIX}/share/lua/5.0
	cp pty.lua ${DESTDIR}${PREFIX}/share/lua/5.0

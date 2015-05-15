# Makefile for libdfui.
# $Id: Makefile,v 1.28 2005/08/26 22:44:37 cpressey Exp $

BASE?=../..
include ${BASE}/Config

LIB=	dfui
LIB_VER=4

OBJS=	encode.o decode.o conn_tcp.o \
	connection.o conn_caps.o conn_npipe.o \
	form.o dump.o system.o lang.o

CFLAGS+=	${EXTRA_CFLAGS} ${WARNS} -fPIC -I../libaura
LDFLAGS+=	../libaura/libaura.a -Wl,-soname,${SONAME}

# Default target:

all: ${SONAME} ${ANAME}

# Main targets, shared and static:

${SONAME}: ${OBJS}
	${CC} ${OBJS} -shared ${LDFLAGS} -o ${SONAME}
	${LN} -sf ${SONAME} ${SOLINK}

${ANAME}: ${OBJS}
	${AR} rc ${ANAME} ${OBJS}
	${RANLIB} ${ANAME}

strip: ${SONAME}
	${STRIP ${SONAME}

clean:
	rm -rf *.o *.so *.so.* *.So *.a

install: all
	mkdir -p ${DESTDIR}${PREFIX}/lib
	cp ${SONAME} ${DESTDIR}${PREFIX}/lib
	ln -sf ${SONAME} ${DESTDIR}${PREFIX}/lib/${SOLINK}
	cp ${ANAME} ${DESTDIR}${PREFIX}/lib

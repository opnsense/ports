# Makefile for dfuife_curses.
# $Id: Makefile,v 1.28 2005/08/29 19:19:13 cpressey Exp $

BASE?=../..
include ${BASE}/Config

PACKAGE=dfuife_curses

OBJS=	curses_util.o \
	curses_form.o curses_widget.o curses_bar.o \
	curses_xlat.o \
	main.o

CFLAGS+=	${WARNS}
CFLAGS+=	-I../../lib/libaura -I../../lib/libdfui
CFLAGS+=	-I/usr/local/include -I/usr/pkg/include
CFLAGS+=	${EXTRA_CFLAGS}

LDFLAGS+=	-L../../lib/libdfui -ldfui
LDFLAGS+=	-lpanel -lncurses

# Default target.

PROG=	dfuife_curses

all: ${PROG}

# Main target.

${PROG}: ${OBJS}
	${CC} ${OBJS} ${LDFLAGS} -o ${PROG}

strip: ${PROG}
	strip ${PROG}

clean:
	rm -f aura dfui
	rm -rf ${PROG} *.o *.core

# In-CVS-tree testing.

LIBPATH?=../../lib/libaura:../../lib/libdfui:/usr/pkg/lib
DEBUGGER?=gdb

test:
	env LD_LIBRARY_PATH="${LIBPATH}" ./${PROG}

debug:
	env LD_LIBRARY_PATH="${LIBPATH}" ${DEBUGGER} ./${PROG}

# Create directory layout for binary distribution.

install: all
	mkdir -p ${DESTDIR}${PREFIX}/sbin
	cp dfuife_curses ${DESTDIR}${PREFIX}/sbin
	mkdir -p ${DESTDIR}${PREFIX}/share/dfuife_curses
	cp *.txt ${DESTDIR}${PREFIX}/share/dfuife_curses

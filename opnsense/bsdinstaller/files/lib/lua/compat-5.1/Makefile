# $Id: Makefile,v 1.5.2.1 2009/01/03 19:49:46 sullrich Exp $

CFLAGS += -fPIC

BASE?=../../..
include ${BASE}/Config

LUA=../../../lua

CFLAGS+=-Wall $(EXTRA_CFLAGS)

all: compat-5.1.o

compat-5.1.o: compat-5.1.c compat-5.1.h
	$(CC) $(CFLAGS) -I$(LUA)/include -c compat-5.1.c -o compat-5.1.o

strip: compat-5.1.o
	strip compat-5.1.o

clean:
	rm -f *.o

install: strip
	mkdir -p $(DESTDIR)${PREFIX}/bin
	cp lua50c51.sh $(DESTDIR)${PREFIX}/bin/lua50c51
	mkdir -p ${DESTDIR}${PREFIX}/share/lua/5.0
	cp compat-5.1.lua ${DESTDIR}${PREFIX}/share/lua/5.0

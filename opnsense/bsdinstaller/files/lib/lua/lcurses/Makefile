# makefile for lcurses library for Lua
# $Id: Makefile,v 1.9 2005/08/26 22:44:38 cpressey Exp $

BASE?=../../..
include ${BASE}/Config

# change these to reflect your Lua installation
LUA=../../../lua
LUAINC= $(LUA)/include
LUALIB= $(LUA)/lib

COMPAT=../compat-5.1

# no need to change anything below here
CFLAGS+= -fPIC -O2 -I$(LUAINC) -Wall -ansi
LDFLAGS+=-L$(LUALIB) -L/usr/local/lib -lpanel -lcurses -llualib50 -llua50

MYNAME= curses
MYLIB= l$(MYNAME)

OBJS= $(MYLIB).o

T= $(MYLIB).so

VER=0.1-devel

all: $T

lua: lcurses.c lua.c
	$(CC) -I. -DDEBUG -g -o lua lua.c lcurses.c -L. -llualib -llua -lpanel -lcurses -lm -ldl

$T:	$(OBJS)
	$(CC) -fPIC -o $@ -shared $(OBJS) $(COMPAT)/compat-5.1.o $(LDFLAGS)

lcurses.o: lcurses.c lpanel.c

clean:
	rm -f $(OBJS) $T core core.* *.core a.out

strip: all
	${STRIP} $T

install: strip
	mkdir -p $(DESTDIR)${PREFIX}/lib/lua/5.0
	cp $T $(DESTDIR)${PREFIX}/lib/lua/5.0
	mkdir -p ${DESTDIR}${PREFIX}/share/lua/5.0
	cp curses.lua ${DESTDIR}${PREFIX}/share/lua/5.0

# Makefile for dfuibe_lua.
# $Id: Makefile,v 1.55 2005/08/27 08:04:49 cpressey Exp $

BASE?=../..
include ${BASE}/Config

PACKAGE=	dfuibe_lua

LUA?=		../../platform/lua
COMPAT?=	../../lib/lua/compat-5.1

MEDIAROOT?=	/usr/release/root
OSNAME?=        DragonFly

all:
	@echo "Nothing to build."

clean:
	rm -rf *.core

strip: all
	@echo "Nothing to strip."

test:
	su root -c "env LD_LIBRARY_PATH='../../lib/libaura:../../lib/libdfui:$(LUA)/lib' \
	LUA_PATH='../../lib/lua/?/?.lua;../../lib/lua/luasocket/lua/?.lua' \
	LUA_CPATH='../../lib/lua/posix/?.so;../../lib/lua/pty/?.so;../../lib/lua/dfui/?.so;../../lib/lua/luasocket/?.so' \
	$(LUA)/bin/lua -lcompat-5.1 main.lua \
	./conf/BSDInstaller.lua ./conf/${OSNAME}.lua \
	dir.root=${MEDIAROOT}"

# Create directory layout for binary distribution.

install: strip
	mkdir -p ${DESTDIR}/share/dfuibe_lua
	cp *.lua ${DESTDIR}/share/dfuibe_lua/
	for _subdir in lib conf easy_install pit install configure upgrade netboot; do \
		mkdir -p ${DESTDIR}/share/dfuibe_lua/$${_subdir}; \
		cp $${_subdir}/*.lua ${DESTDIR}/share/dfuibe_lua/$${_subdir}; \
	done

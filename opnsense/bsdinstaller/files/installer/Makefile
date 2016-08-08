# Makefile for dfuibe_lua.
# $Id: Makefile,v 1.55 2005/08/27 08:04:49 cpressey Exp $

BASE?=..
.include "${BASE}/Config"

all:
clean:

install:
	mkdir -p ${DESTDIR}${PREFIX}/share/dfuibe_lua
	cp *.lua ${DESTDIR}${PREFIX}/share/dfuibe_lua/
	for _subdir in lib conf easy_install pit install configure \
	    configure/menu netboot; do \
		mkdir -p ${DESTDIR}${PREFIX}/share/dfuibe_lua/$${_subdir}; \
		cp $${_subdir}/*.lua ${DESTDIR}${PREFIX}/share/dfuibe_lua/$${_subdir}; \
	done

.PHONY: install

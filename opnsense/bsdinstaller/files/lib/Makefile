# Make all libraries.
# $Id: Makefile,v 1.19.2.1 2009/01/03 19:49:46 sullrich Exp $

CFLAGS += -fPIC

BASE=..
include $(BASE)/Config

all:
	(cd libaura && ${MAKE} all) && \
	(cd libdfui && ${MAKE} all) && \
	(cd lua && ${MAKE} all)

nls:
	(cd libaura && ${MAKE} all) && \
	(cd libdfui && ${MAKE} all) && \
	(cd lua && ${MAKE} nls)

clean:
	(cd libaura && ${MAKE} clean) && \
	(cd libdfui && ${MAKE} clean) && \
	(cd lua && ${MAKE} clean)

distribution:
	(cd libaura && ${MAKE} distribution) && \
	(cd libdfui && ${MAKE} distribution) && \
	(cd lua && ${MAKE} distribution)

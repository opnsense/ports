# Build all backends.
# $Id: Makefile,v 1.14 2005/08/29 20:41:52 cpressey Exp $

BASE=..
include $(BASE)/Config

all:
	(cd lua && ${MAKE} all) && \
	cd test && ${MAKE} all

nls:
	(cd lua && ${MAKE} nls) && \
	cd test && ${MAKE} nls

clean:
	(cd lua && ${MAKE} clean) && \
	cd test && ${MAKE} clean

distribution:
	(cd lua && ${MAKE} distribution)

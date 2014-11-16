# Make all frontends.
# $Id: Makefile,v 1.16 2005/08/29 20:41:52 cpressey Exp $

BASE=..
include $(BASE)/Config

all:
	(cd test && ${MAKE} all) && \
	(cd ncurses && ${SKIP_NCURSES_FRONTEND} || ${MAKE} all)

nls:
	(cd test && ${MAKE} all) && \
	(cd ncurses && ${SKIP_NCURSES_FRONTEND} || ${MAKE} nls)

clean:
	(cd test && ${MAKE} clean) && \
	(cd ncurses && ${SKIP_NCURSES_FRONTEND} || ${MAKE} clean)

distribution:
	(cd ncurses && ${SKIP_NCURSES_FRONTEND} || ${MAKE} distribution)

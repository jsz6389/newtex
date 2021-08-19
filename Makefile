VERSION = 0.1

PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

CC := gcc
CFLAGS := -lconfig

SRCS := newtex.c

OBJS := $(SRCS:.c=.o)

EXEC := newtex

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile ; $(CC) -o $@ $(OBJS) $(CFLAGS)

clean: ; rm -f $(EXEC) $(OBJS)

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f newtex ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/newtex
	mkdir -p /etc/newtex.d/templates
	cp -f newtex.conf /etc/newtex.d/
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < newtex.1 > ${DESTDIR}${MANPREFIX}/man1/newtex.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/newtex.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/newtex\
		${DESTDIR}${MANPREFIX}/man1/newtex.1

.PHONY: all clean install uninstall

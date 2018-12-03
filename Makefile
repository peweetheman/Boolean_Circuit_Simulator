#
# File: Makefile
# Creator: George Ferguson
# Created: Mon Nov 28 13:52:02 2016
# Time-stamp: <Tue Jul 17 16:02:59 EDT 2018 ferguson>
#

SRCS = Boolean.c Gates.c Circuit.c main.c
HDRS = Boolean.h Gates.h Circuit.h
OBJS = $(SRCS:.c=.o)
EXE = boosim
ZIPDIR = CSC173 Project 5 Boolean Circuit Simulator

CFLAGS = -std=c99 -Wall -Werror -g

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS)

valgrind:
	valgrind ./$(EXE)

clean:
	-rm $(OBJS) $(EXE)

zip:
	mkdir '$(ZIPDIR)'
	cp -p README.txt $(SRCS) $(HDRS) Makefile '$(ZIPDIR)'
	zip -r '$(ZIPDIR)' '$(ZIPDIR)'
	rm -r '$(ZIPDIR)'


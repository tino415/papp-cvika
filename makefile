#
# Makefile for POSIX threads demo programs
#
# "make program" to make one program
# "make" or "make all" to make all executables
# "make clean" to remove executables
#

CC		= gcc
CFLAGS	=  -g -O3 -Wall
LFLAGS	= -lm -lpthread
UNAME := $(shell uname -s)

ALL =   basic

all:  $(ALL)

%: %.c 
	$(CC) -o $@ $(CFLAGS) $< $(LFLAGS)

# Windows
clean:
	-del *.exe

# Linux
ifeq ($(UNAME),Linux)
clean:
	-rm $(ALL)
endif

# OSX
ifeq ($(UNAME),Darwin)
clean:
	-rm $(ALL)
endif

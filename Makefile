# Makefile for Warp Do We Do Now?

# Most of the file is hard coded for more control.

# C compiler and flags
CC=gcc
CFLAGS=-Wall

# Special rules:
.PHONY : all clean

# All default targets
all : wdwdn

# Executable file
wdwdn : main.o gui.o turn-counter.o warp-space.o event-gen.o resourse-regen.o
	$(CC) $(CFLAGS)

# Generic Object creation rule
# (If an object is given other rule it will override this one.)
%.o :
	$(CC) $(CFLAGS) -c $< -o $@

# Objects for the different moduals.
main.o :           main.c
gui.o :            gui.c            gui.h
turn-counter.o :   turn-counter.c   turn-counter.h
warp-space.o :     warp-space.c     warp-space.h
event-gen.o :      event-gen.c      event-gen.h
resourse-regen.o : resourse-regen.c resourse-regen.h

# clean up rule
clean :
	rm *.o

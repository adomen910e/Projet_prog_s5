# Makefile

#le nom du fichier executable

OUTFILE = test-1 base

#les fichiers objets
SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:src/%.c=obj/%.o)

MAKEFILES := Makefile

#le compilateur
CC= gcc

#les flags de compilation
CFLAGS= -std=c99 -Wall -g

$(OBJECTS): $(MAKEFILES)

all: $(OUTFILE)

test-1: obj/projet-1.o obj/test-1.o
	$(CC) $^ -o $@
base: obj/projet-1.o obj/base.o
	$(CC) $^ -o $@

$(OBJECTS): obj/%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

test-1.o: test-1.c projet-1.h
base.o: base.c projet-1.h
projet-1.o: projet-1.c projet-1.h

.PHONY: clean

clean:
	rm -rf $(OUTFILE) $(OBJECTS)

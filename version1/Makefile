# Makefile

#le nom du fichier executable

OUTFILE = test-1 version1

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

test-1: obj/carte.o obj/joueur.o obj/memento.o obj/plateau.o obj/test-1.o
	$(CC) $^ -o $@
version1: obj/carte.o obj/joueur.o obj/memento.o obj/plateau.o obj/version1.o
	$(CC) $^ -o $@

$(OBJECTS): obj/%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

test-1.o: test-1.c plateau.h joueur.h carte.h memento.h
version1.o: version1.c plateau.h joueur.h carte.h memento.h
carte.o: carte.c carte.h
joueur.o: joueur.h carte.h joueur.c
memento.o: memento.h carte.h memento.c
plateau.o: plateau.h joueur.h carte.h plateau.c

.PHONY: clean

clean:
	rm -rf $(OUTFILE) $(OBJECTS)

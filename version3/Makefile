
# Makefile

#le nom du fichier executable

OUTFILE = test-1 version3

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

test-1: obj/carte.o obj/joueur.o obj/memento.o obj/plateau.o obj/ami.o obj/grille.o obj/test-1.o
	$(CC) $^ -o $@
version3: obj/carte.o obj/joueur.o obj/memento.o obj/plateau.o obj/grille.o obj/ami.o obj/version3.o
	$(CC) $^ -o $@

$(OBJECTS): obj/%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

test-1.o: test-1.c plateau.h joueur.h carte.h memento.h grille.h
version3.o: version3.c plateau.h joueur.h carte.h memento.h grille.h ami.h
carte.o: carte.c carte.h
joueur.o: ami.h joueur.h carte.h joueur.c
memento.o: memento.h carte.h memento.c
plateau.o: plateau.h joueur.h carte.h grille.h plateau.c
grille.o: grille.h grille.c
ami.o: joueur.h grille.h ami.h ami.c

.PHONY: clean

clean:
	rm -rf $(OUTFILE) $(OBJECTS)
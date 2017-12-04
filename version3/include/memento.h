#ifndef _MEMENTO_H_
#define _MEMENTO_H_

#include <stdio.h>
#include <stdlib.h>
#include "carte.h"



typedef struct memento* memento;
typedef struct memento_list* memento_list;

memento_list creer_memento();
memento_list ajouter_memento_fin(memento_list m, carte c);

memento_list supprimer_memento_debut(memento_list m);

memento_list remplir_memento(memento_list m);
void melanger_memento(carte* memento);
carte get_carte(memento m);
memento get_suivant(memento m);
memento get_premier(memento_list m);
int get_longueur(memento_list lm);
void supprimer_tout_memento(memento_list m);
void supprimer_memento(memento m);
void afficher_memento(memento_list m);

#endif


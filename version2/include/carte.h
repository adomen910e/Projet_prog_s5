#ifndef _CARTE_H_
#define _CARTE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct carte* carte;


//Fonctions associées a la structure carte
carte creer_carte(char* nom);
int get_cout(carte c);
int get_rarete(carte c);
char* get_nom(carte c);
void set_cout(carte c, int a);
void set_rarete(carte c, int a);
void set_nom(carte c, char* s);
void supprimer_carte(carte c);
carte copie_carte(carte c);
carte choisir_aleatoirement_carte();

#endif

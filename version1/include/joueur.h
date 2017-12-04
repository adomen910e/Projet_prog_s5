#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include <stdio.h>
#include <stdlib.h>
#include "carte.h"

typedef struct joueur* joueur;

//Fonction associé a la structure joueur
joueur creer_joueur(int numero);
int get_numero(joueur j);
int get_energie(joueur j);
int get_idee(joueur j);
int get_gain(joueur j);
int get_nb_carte(joueur j);
carte get_carte_main(int i, joueur j);
void supprimer_joueur(joueur j);

void set_numero(joueur j,int a);
void set_energie(joueur j,int a);
void set_idee(joueur j,int a);
void set_gain(joueur j,int a);
void set_nb_carte(joueur j,int a);
void set_carte_main(int i, joueur j, carte c);

int choisir_carte(joueur j);
void defausser(joueur j);
void piocher(joueur j, int i);
void augmenter_idee(joueur j);
void afficher_main(joueur j);




#endif

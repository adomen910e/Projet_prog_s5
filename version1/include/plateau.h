#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"

typedef struct plateau_de_jeu* plateau_de_jeu;

//fonction associé au plateau
void creer_plateau(int nb_joueur);
void afficher_resultat(int tour);
void afficher_joueurs();
void classer_joueur(int numero);
void quitte_partie(int numj);
int get_nb_joueur_vivant();
int get_nb_joueur();
joueur get_joueur(int i);
void traiter_carte(int i, joueur moi, joueur adversaire);

void supprimer_plateau();
void classe_joueur_egalite(int, int); 
#endif

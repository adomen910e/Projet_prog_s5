#ifndef _PROJET_1_H_
#define _PROJET_1_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct plateau_de_jeu* plateau_de_jeu;
typedef struct joueur* joueur;
typedef struct carte* carte;

int rand_a_b(int a, int b);

//Fonctions associées a la structure carte
carte creer_carte(char* nom);
int get_cout(carte c);
int get_rarete(carte c);
void afficher_main(joueur j);

//Fonction associé a la structure joueur
joueur creer_joueur(int numero);
int get_numero(joueur j);
int get_energie(joueur j);
int get_idee(joueur j);
int get_gain(joueur j);
int get_nb_carte(joueur j);
void afficher_joueurs();
int choisir_carte(joueur j);
void piocher(joueur j, int i);
void augmenter_idee(joueur j);



//fonction associé au memento
void remplir_memento(carte* memento);
void melanger_memento(carte* memento);


//fonction associé au plateau
void creer_plateau(int nb_joueur);
void afficher_resultat();
void classer_joueur(int numero);
void quitte_partie(int numj);
int get_nb_joueur_vivant();
int get_nb_joueur();
joueur get_joueur(int i);
void traiter_carte(int c, joueur moi, joueur adversaire);

void set_carte_main(int i, joueur j, carte c);
void set_cout(carte c, int a);
void set_rarete(carte c, int a);
void set_nom(carte c, char* s);
char* get_nom(carte c);
void set_idee(joueur j, int a);
void supprimer_joueur(joueur j);
void supprimer_carte(carte c);

void supprimer_joueur(joueur j);

void supprimer_carte(carte c);
void supprimer_plateau() ;
int get_classement(int i);

carte get_carte(joueur j , int i);

#endif

#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "carte.h"
#include "ami.h"

typedef struct joueur* joueur;



//Fonction associé a la structure joueur
joueur creer_joueur(int numero);
int get_numero(joueur j);
int get_energie(joueur j);
int get_idee(joueur j);
int get_gain(joueur j);
int get_nb_carte(joueur j);
carte get_carte_main(int i, joueur j);
int get_position_x(joueur j);
int get_position_y(joueur j);
struct position get_position(joueur j);
int get_nb_ami(joueur j);
ami get_ami(int i, joueur j);
void supprimer_joueur(joueur j);


void set_numero(joueur j, int a);
void set_energie(joueur j, int a);
void set_idee(joueur j, int a);
void set_gain(joueur j, int a);
void set_nb_carte(joueur j, int a);
void set_carte_main(int i, joueur j, carte c);
void set_position_x(joueur j, int vx);
void set_position_y(joueur j, int vy);
void set_ami(int i, joueur j, ami a);
void set_nb_ami(joueur j, int i);
void augmenter_nb_ami_joueur(joueur j);
void ami_mort(joueur j, int numj);

int choisir_carte(joueur j);
void defausser(joueur j);
void piocher(joueur j, int i);
void augmenter_idee(joueur j);
void afficher_main(joueur j);
bool est_mort(joueur j);



#endif

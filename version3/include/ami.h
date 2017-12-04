#ifndef _AMI_H_
#define _AMI_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "carte.h"

typedef struct ami* ami;

struct position {
    int x;
    int y;
};

ami creer_ami(int adversaire, int num, struct position p, carte c);
void augmenter_gain(ami a);
int get_numero_cible(ami a);
int get_numero_maitre(ami a);
struct position get_pos_ami(ami a);
int get_idee_ami(ami a);
int get_vie_ami(ami a);
void diminuer_vie(ami a);
carte recuperer_carte_ami(ami a);
void augmenter_energie(ami a, int i);
void augmenter_idee_ami(ami a);
void diminuer_energie(ami a, int i);
void diminuer_idee(ami a, int i);
void afficher_ami(ami a);
void supprimer_ami(ami a);
int numero_joueur_ami(ami a);

#endif

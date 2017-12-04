#include "../include/projet-1.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

#define NB_CARTE_BEGIN 5
#define MEMENTO 50
#define PROBA 131
#define FAIL -1

static plateau_de_jeu plateau;

struct joueur {
    int numero_joueur;
    int energie;
    int idee;
    int gain;
    int n_carte;
    carte *main;
    int indice;
  //carte* memento;
};

struct carte {
    char* nom;
    int cout;
    int rarete;
};

struct plateau_de_jeu {
    joueur* tab_joueur;
    int nb_joueur;
    int nb_joueur_vivant;
    int* classement_joueur;
};

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}

carte choisir_aleatoirement_carte() {

    int alea = rand_a_b(0, PROBA);

    if (alea < 20) {
       
        return creer_carte("think");
    } else if (alea < 30) {
       
        return creer_carte("steal");
    } else if (alea < 80) {
     ;
        return creer_carte("panacea");
    } else if (alea < 130) {
      ;
        return creer_carte("razor");
    }

 
    return creer_carte("hell");


}

carte creer_carte(char* nom) {

    if (nom == NULL) {
        echec("nom NULL: creer_carte()");
        return NULL;
    }

    carte c = (carte)malloc(sizeof (struct carte));

    if (strcmp(nom, "think") == 0) {
        c->nom = nom;
        c->cout = 5;
        c->rarete = 100 / 5;
    }
    if (strcmp(nom, "steal") == 0) {
        c->nom = nom;
        c->cout = 10;
        c->rarete = 100 / 10;
    }

    if (strcmp(nom, "panacea") == 0) {
        c->nom = nom;
        c->cout = 2;
        c->rarete = 100 / 2;
    }

    if (strcmp(nom, "razor") == 0) {
        c->nom = nom;
        c->cout = 2;
        c->rarete = 100 / 2;
    }


    if (strcmp(nom, "hell") == 0) {
        c->nom = nom;
        c->cout = 100;
        c->rarete = 1;
    }


    return c;

}


joueur creer_joueur(int numero) {
    joueur j = malloc(sizeof (struct joueur));
    if (!j) {
        echec("joueur non créé: creer_joueur()");
	
        return NULL;
    }

    j->numero_joueur = numero;
    j->energie = 50;
    j->idee = 0;
    j->gain = 1;
    j->n_carte = 0;
    j->main = malloc(NB_CARTE_BEGIN * sizeof (struct carte));
    if (!j->main) {
        echec("main non créé: creer_joueur()");
    }
    for(int i =0 ; i<NB_CARTE_BEGIN; i++)
      {
	j->main[i]=NULL;
      }

    j->indice = 0;

    for (int i = 0; i < NB_CARTE_BEGIN; i++) {
        piocher(j,i);
    }

    return j;

}

void creer_plateau(int nb_joueur) {

    if (nb_joueur == 0) {
        echec("nombre de joueur NULL: creer_plateau()");
        return;
    }

    plateau = malloc(sizeof (struct plateau_de_jeu));
    if (!plateau) {
        echec("plateau non créé: creer_plateau()");
        return;
    }


    plateau->tab_joueur = malloc(nb_joueur * sizeof (struct joueur));
    if (!plateau->tab_joueur) {
        echec("tableau de joueur non créé: creer_plateau()");
        return;
    }

    for (int i = 0; i < nb_joueur; i++) {
        plateau->tab_joueur[i] = creer_joueur(i);
    }

    plateau->nb_joueur = nb_joueur;
    plateau->nb_joueur_vivant = nb_joueur;
    plateau->classement_joueur = malloc(nb_joueur * sizeof (int));
    if (!plateau->classement_joueur) {
        echec("tableau de classement non créé: creer_plateau()");
        return;
    }

}

void afficher_main(joueur j) {

    if (j == NULL) {
        echec("joueur NULL: afficher_main()");
        return;
    }

    for (int i = 0; i < j->n_carte ; i++) {
        printf("CARTE %d\n", i);
        printf("Kitty %s\n", j->main[i]->nom);
        printf("Cout: %d\n", j->main[i]->cout);
        printf("Rareté: %d\n", j->main[i]->rarete);
        printf("\n");
    }
}

void afficher_joueurs() {

    if (plateau == NULL) {
        echec("plateau NULL: afficher_joueurs()");
        return;
    }

    for (int i = 0; i < plateau->nb_joueur_vivant; i++) {
        printf("JOUEUR %d :\n", i);
        printf("Energie : %d\n", plateau->tab_joueur[i]->energie);
        printf("Idee : %d\n", plateau->tab_joueur[i]->idee);
        printf("Gain : %d\n", plateau->tab_joueur[i]->gain);
        afficher_main(plateau->tab_joueur[i]);
    }
}

//carte choisir_carte(joueur j) {
//
//    if (j == NULL) {
//        echec("joueur NULL: choisir_carte()");
//        return NULL;
//    }
//
//    return j->main[rand_a_b(0, j->n_carte--)];
//}

int choisir_carte(joueur j) {

    if (j == NULL) {
        echec("joueur NULL: choisir_carte()"); 
        return FAIL;
    }

    int alea = rand_a_b(0, j->n_carte);
    int alea2 = 0;

    for (alea2 = (alea + 1) % 5; get_cout(j->main[alea2]) > get_idee(j);) {

        if ((get_cout(j->main[alea2]) > get_idee(j)) && (alea2 == alea)) {
            return FAIL;
        }
 
        if (get_cout(j->main[alea2]) < get_idee(j)) {
            break;
        }

        alea2 = (alea2 + 1) % 5;

    }
    

    return alea2;
}

void traiter_carte(int c, joueur moi, joueur adversaire) {

    if ( moi == NULL || adversaire == NULL) {
        echec("carte ou moi ou adversaire NULL : traiter_carte()");
        return;
    }

    if (strcmp(moi->main[c]->nom, "think") == 0) {
      //printf("================================THINK\n");
        moi->gain++;

    } else if (strcmp(moi->main[c]->nom, "steal") == 0) {
      //printf("================================STEAL\n");
        moi->gain++;
        if (adversaire->gain != 1)
            adversaire->gain--;

    } else if (strcmp(moi->main[c]->nom, "panacea") == 0) {
      //printf("================================panacea\n");
        moi->energie += 10;

    } else if (strcmp(moi->main[c]->nom, "razor") == 0) {
      //printf("================================razor\n");
        adversaire->energie -= 10;

    } else if (strcmp(moi->main[c]->nom, "hell") == 0) {
      // printf("================================hell\n");
        adversaire->energie -= INT_MAX;
    }

    moi->idee -= moi->main[c]->cout;
    supprimer_carte(moi->main[c]);
    //IL FAUT LE METTRE DANS LA FILE MEMENTO
    moi->n_carte--;
}

void piocher(joueur j, int i) {

    if (j == NULL) {
        echec("joueur NULL: piocher()");
        return;
    }
   
   
    
    j->main[i] = choisir_aleatoirement_carte();
    j->n_carte++;
}

void augmenter_idee(joueur j) {

    if (j == NULL) {
        echec("joueur NULL: augmenter_idee()");
        return;
    }

    j->idee += j->gain;
}

void classer_joueur(int numero) {
    //on classe le numero du joueur a la derniere case libre
    plateau->classement_joueur[plateau->nb_joueur_vivant] = numero;
}

void afficher_resultat() {

    if (plateau == NULL) {
        echec("plateau NULL: afficher_resultat()");
        return;
    }

    for (int i = 0; i < plateau->nb_joueur; i++) {
        printf("Le joueur numero %d est %d\n", i, plateau->classement_joueur[i]+1);
    }
}
void quitte_partie(int numj) {

    if (plateau->nb_joueur_vivant - 1 != 0) {
        bool b = false;
        joueur tmp;
        
        for (int i = 0; i < plateau->nb_joueur_vivant - 1; i++) {
            if (get_numero(plateau->tab_joueur[i]) == numj) {
                b = true;
                tmp = plateau->tab_joueur[i];
            }
            if (b == true)
                plateau->tab_joueur[i] = plateau->tab_joueur[i + 1];
        }

        if (b != false){ //Si on a trouvé le joueur
	  supprimer_joueur(tmp);
	}else{           //Sinon notre joueur est dernier
	  supprimer_joueur( plateau->tab_joueur[plateau->nb_joueur_vivant - 1]);
	}
        plateau->nb_joueur_vivant--;
       
    }else{
        
        supprimer_joueur(plateau->tab_joueur[0]);
        plateau->nb_joueur_vivant--;
        
    }
    
}

int get_nb_joueur_vivant() {
    return plateau->nb_joueur_vivant;
}

joueur get_joueur(int i) {
    if (i > plateau->nb_joueur_vivant) {
        echec("le numero est trop grand: get_joueur()");
        return NULL;
    }

    return plateau->tab_joueur[i];
}

int get_nb_joueur() {
    return plateau->nb_joueur;
}

int get_energie(joueur j) {

    if (j == NULL) {
        echec("Joueur NULL: get_energie()");
        return EXIT_FAILURE;
    }

    return j->energie;
}

int get_cout(carte c) {
    if (c == NULL) {
        echec("carte NULL : get_cout()");
        return EXIT_FAILURE;
    }

    return c->cout;
}

int get_rarete(carte c) {
    if (c == NULL) {
        echec("carte NULL : get_rarete()");
        return EXIT_FAILURE;
    }

    return c->rarete;
}

int get_numero(joueur j) {

    if (j == NULL) {
        echec("Joueur NULL: get_numero()");
        return EXIT_FAILURE;
    }

    return j->numero_joueur;
}

int get_idee(joueur j) {

    if (j == NULL) {
        echec("Joueur NULL: get_idee()");
        return EXIT_FAILURE;
    }

    return j->idee;
}

int get_gain(joueur j) {

    if (j == NULL) {
        echec("Joueur NULL: get_gain()");
        return EXIT_FAILURE;
    }

    return j->gain;
}

int get_nb_carte(joueur j) {

    if (j == NULL) {
        echec("Joueur NULL: get_nb_carte()");
        return EXIT_FAILURE;
    }

    return j->n_carte;
}

void set_carte_main(int i, joueur j, carte c) {
    
    if(j == NULL || c == NULL)
        return;


    set_nom(j->main[i],get_nom(c));
    set_cout(j->main[i],get_cout(c));
    set_rarete(j->main[i],get_rarete(c));

}

void set_cout(carte c, int a) {
    if (c == NULL || a == 0) {
        echec("carte NULL : set_cout()");
        return;
    }

    c->cout = a;
}

void set_rarete(carte c, int a) {
    if (c == NULL || a == 0) {
        echec("carte NULL : set_rarete()");
        return;
    }

    c->rarete = a;
}

void set_nom(carte c, char* s) {
    if (c == NULL || s == NULL) {
        echec("carte NULL : set_nom()");
        return;
    }

    c->nom = s;
}

char* get_nom(carte c) {
    if (c == NULL) {
        echec("carte NULL : get_nom()");
        return NULL;
    }

    return c->nom;
}

void set_idee(joueur j, int a) {

    if (j == NULL) {
        echec("Joueur NULL: set_idee()");
        return;
    }

    j->idee = a;
}
void supprimer_joueur(joueur j){
    for(int i=0; i<NB_CARTE_BEGIN;i++){
	supprimer_carte(j->main[i]);
    }
    free(j->main);

    free(j);
}


void supprimer_carte(carte c){
    free(c);
}

void supprimer_plateau() {

    for (int i = 0; i < plateau->nb_joueur_vivant; i++) {
        supprimer_joueur(plateau->tab_joueur[i]);
    }
    free(plateau->tab_joueur);
    
    free(plateau->classement_joueur);
    free(plateau);

}

int get_classement(int i){
  return plateau->classement_joueur[i];
}


carte get_carte(joueur j , int i){
  return j->main[i];
}

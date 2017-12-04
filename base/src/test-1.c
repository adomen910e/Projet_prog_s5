#include "../include/projet-1.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool test_equality_int(int expected, int value, char * msg) {
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}

bool test_equality_bool(bool expected, bool value, char * msg) {
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}

void test_failure_traiter_carte(int i, joueur moi, joueur adv) {
    traiter_carte(i, moi, adv);
}

void test_failure_joueur(joueur j, int i) {
    afficher_main(j);
    afficher_joueurs();
    choisir_carte(j);
    piocher(j,i);
    augmenter_idee(j);
}

void test_failure_plateau(plateau_de_jeu pdj) {
    afficher_resultat();
}

bool test_rand_a_b() {
    bool result = true;

    int a = 0;
    int b = 10;
    int r = rand_a_b(a, b);

    result = result && test_equality_bool(true, r >= a, "rand_a_b() >= a");
    result = result && test_equality_bool(true, r <= b, "rand_a_b() <= b");

    return result;
}

bool test_creer_carte() {
    bool result = true;

    carte c1 = creer_carte("think");
    result = result && test_equality_int(5, get_cout(c1), "think get_cout");
    result = result && test_equality_int(20, get_rarete(c1), "think get_rarete");

    carte c2 = creer_carte("steal");
    result = result && test_equality_int(10, get_cout(c2), "steal get_cout");
    result = result && test_equality_int(10, get_rarete(c2), "steal get_rarete");

    carte c3 = creer_carte("panacea");
    result = result && test_equality_int(2, get_cout(c3), "panacea get_cout");
    result = result && test_equality_int(50, get_rarete(c3), "panacea get_rarete");

    carte c4 = creer_carte("razor");
    result = result && test_equality_int(2, get_cout(c4), "razor get_cout");
    result = result && test_equality_int(50, get_rarete(c4), "razor get_rarete");

    carte c5 = creer_carte("hell");
    result = result && test_equality_int(100, get_cout(c5), "hell get_cout");
    result = result && test_equality_int(1, get_rarete(c5), "hell get_rarete");
    
    supprimer_carte(c1);
    supprimer_carte(c2);
    supprimer_carte(c3);
    supprimer_carte(c4);
    supprimer_carte(c5);
    return result;
}

bool test_creer_joueur() {
    bool result = true;
    int numero=10;

    joueur j = creer_joueur(numero);
    result = result && test_equality_int(10, get_numero(j), "get_numero");
    result = result && test_equality_int(50, get_energie(j), "get_energie");
    result = result && test_equality_int(0, get_idee(j), "get_idee");
    result = result && test_equality_int(1, get_gain(j), "get_gain");
    result = result && test_equality_int(5, get_nb_carte(j), "get_nb_carte");
    
    supprimer_joueur(j);
    return result;
}

bool test_creer_plateau(){
  bool result = true;
  int nb_joueur = 2;
  creer_plateau(nb_joueur);

  result = result && test_equality_int(nb_joueur, get_nb_joueur(), "get_nb_joueur");
  supprimer_plateau(); 
  return result;
}

bool test_choisir_carte(){
  bool result = true;
  int numero=5;

  joueur j = creer_joueur(numero);
  set_idee(j,1000);
  int num_carte = choisir_carte(j);

  result=result && test_equality_bool(true, (num_carte>=0),"num_carte >=0");
  result=result && test_equality_bool(true, (num_carte<5),"num_carte >5");
  
  
  supprimer_joueur(j);

  return result;
}

bool test_traiter_carte(){
  joueur j1 = creer_joueur(1);
  joueur j2 = creer_joueur(2);
  bool result = true; 


  carte c1=creer_carte("think");
  carte c2=creer_carte("steal");
  carte c3=creer_carte("panacea");
  carte c4=creer_carte("razor");
  carte c5=creer_carte("hell");

  set_carte_main(0,j1,c1);
  set_carte_main(0,j2,c2);
  set_carte_main(1,j1,c3);
  set_carte_main(1,j2,c4);
  set_carte_main(2,j1,c5);


  traiter_carte(0,j1,j2);
  result = result && test_equality_int(2, get_gain(j1), "Carte think");
  piocher(j1,0);

  traiter_carte(0,j2,j1);
  result = result && test_equality_int(1, get_gain(j1), "Carte steal");
  result = result && test_equality_int(2, get_gain(j2), "Carte steal");
  piocher(j2,0);

  traiter_carte(1,j1,j2);
  result = result && test_equality_int(60, get_energie(j1), "Carte Panacea");
  piocher(j1,1);


  traiter_carte(1,j2,j1);
  result = result && test_equality_int(50, get_energie(j1), "Carte Razor");
  piocher(j2,1);
  
  traiter_carte(2,j1,j2);
  result = result && test_equality_bool(true, get_energie(j2)<0,"Carte Hell");
  piocher(j1,2);

  supprimer_joueur(j1);
  supprimer_joueur(j2);
  
  supprimer_carte(c1);
  supprimer_carte(c2);
  supprimer_carte(c3);
  supprimer_carte(c4);
  supprimer_carte(c5);


  return result;  
}


bool test_piocher(){
  joueur j = creer_joueur(8);
  joueur adv = creer_joueur(7);
  bool result = true; 
  int choix_numero = 2;
  traiter_carte(choix_numero, j, adv);
  piocher(j, choix_numero);

  piocher(j,4); 
  int nb_carte = get_nb_carte(j);
  result = result && test_equality_int(5, nb_carte, "Nombre de cartes");
  
  supprimer_joueur(j);

  return result;
}

bool test_augmenter_idee(){
  bool result=true;
  joueur j = creer_joueur(8);
  int i_act = get_idee(j);
  augmenter_idee(j);
  int i_after=get_idee(j);
  int gain=get_gain(j);

  result = result && test_equality_int(i_act+gain, i_after, "Augmenter Idee");
 
  supprimer_joueur(j);

  return result;
}

bool test_quitte_partie(){

  bool result = true; 
  creer_plateau(3);
  int nb_avant = get_nb_joueur_vivant();
  quitte_partie(1);
  int nb_apres = get_nb_joueur_vivant();

  result = result && test_equality_int(nb_avant,nb_apres+1 , "quitter partie");
  supprimer_plateau(); 
  return result; 
}

int main(int argc, char* argv[]) {
    bool result = true;
    joueur no_joueur = NULL;
    joueur no_joueur2 = NULL;
    plateau_de_jeu no_plateau = NULL;
    int numero_carte = 0;


    printf("result of test error\n");
    test_equality_int(0, 1, "error test_equality_int ");
    test_equality_bool(true, false, "error test_equality_bool ");
    test_failure_traiter_carte(numero_carte, no_joueur, no_joueur2);
    test_failure_joueur(no_joueur,numero_carte);
    test_failure_plateau(no_plateau);
    printf("----------------------------------------------------------\n");
    result = result && test_equality_bool(true, test_rand_a_b(), "rand_a_b()");
    result = result && test_equality_bool(true, test_creer_carte(), "creer_carte()");
    result = result && test_equality_bool(true, test_creer_joueur(), "creer_joueur()");
    result = result && test_equality_bool(true, test_creer_plateau(), "creer_plateau()");
    result = result && test_equality_bool(true, test_choisir_carte(), "choisir_carte()");
    result = result && test_equality_bool(true, test_traiter_carte(), "traiter_carte()");
    //result = result && test_equality_bool(true, test_piocher(), "piocher()");
    result = result && test_equality_bool(true, test_augmenter_idee(), "augmenter_idee()");
    result = result && test_equality_bool(true, test_quitte_partie(), "quitte_partie()");

    if (result) {
        printf("Youpi !\n");
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;



}

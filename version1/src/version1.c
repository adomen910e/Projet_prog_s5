#include "../include/plateau.h"
#include <getopt.h>
#define NB_JOUEUR 5
#define FAIL -1

int seed = 0;

static int rand_a_b(int a, int b) {
  return rand() % (b - a) + a;
}

void parse_opts(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "s:")) != -1) {
    switch (opt) {
    case 's':
      seed = atoi(optarg);
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-s seed] \n",
	      argv[0]);
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char* argv[]) {

  parse_opts(argc, argv);
  printf("Seed : %d\n", seed);
    
    srand(seed);

  creer_plateau(NB_JOUEUR);
  int tour = 0 ;
  joueur j;

  while (get_nb_joueur_vivant() > 1 && tour < 1000) {
    afficher_joueurs();

    if (get_nb_joueur_vivant() == 2)
      tour++;
    

    for (int i = 0; i < get_nb_joueur_vivant(); i++) {
            
      if (get_joueur(i) != NULL) {
	j = get_joueur(i);
	int r;
	do {
	  r = rand_a_b(0, get_nb_joueur_vivant());
	} while (r == get_numero(j));

	joueur adversaire = get_joueur(r);

	augmenter_idee(j);

	int choix_numero = choisir_carte(j);
	        
	if (choix_numero != FAIL) { //si une carte a été selectionnée 
	  traiter_carte(choix_numero, j, adversaire);
		    
	  piocher(j, choix_numero);
	} 
                
	if (get_energie(j) <= 0) {
	  int numero = get_numero(j); 
	  quitte_partie(numero);
		    
	  classer_joueur(numero);
		    
	  if (get_nb_joueur_vivant() > 1)
	    i--;
	}

      } 
    }
  }

  if (tour < 1000){

    afficher_joueurs();
    
    if (get_nb_joueur_vivant() == 1) {
      
      int numero = get_numero(get_joueur(0));
      
      quitte_partie(numero);
      
      classer_joueur(numero); 
    }
    
    afficher_resultat(tour);
    
    supprimer_plateau();
  
  }else{

    int numero1 =get_numero(get_joueur(0));
    int numero2 =get_numero(get_joueur(1));

     printf("-----------------------------EGALITE-----------------------------\n");
    printf("Le joueur numero %d est 1eme\n", numero1);
    printf("Le joueur numero %d est 1eme\n", numero2);
 
    quitte_partie(numero2);
    quitte_partie(numero1);
    afficher_resultat(tour);
    
    supprimer_plateau();
  }
    
}
 

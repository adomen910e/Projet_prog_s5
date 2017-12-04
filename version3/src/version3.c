#include "../include/plateau.h"
#include "../include/grille.h"
#include <getopt.h>
#include <string.h>
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

    joueur j;

    while (get_nb_joueur_vivant() > 1) {
        afficher_joueurs();
        afficher_grille();
        //        afficher_position_ami();
        //printf("\n\n");

        for (int i = 0; i < get_nb_joueur_vivant(); i++) {

            if (get_joueur(i) != NULL) {
                j = get_joueur(i);
                int r;
                do {
                    r = rand_a_b(0, get_nb_joueur_vivant());
                } while (r == get_numero(j));

                joueur adversaire = get_joueur(r);

                augmenter_idee(j);
                deplacement_total(get_numero(j));

                int choix_numero = choisir_carte(j);

                if (choix_numero != FAIL) { //si une carte a été selectionnée 

                    traiter_carte(choix_numero, j, adversaire);
                    piocher(j, choix_numero);
                }

                faire_jouer_ami(j, adversaire);

                if (est_mort(j)) {
                    int numero = get_numero(j);
                    quitte_partie(numero);

                    classer_joueur(numero);

                    if (get_nb_joueur_vivant() > 1)
                        i--;
                }

            }
        }
        faire_deplacement_simultanement();
    }

    afficher_joueurs();

    if (get_nb_joueur_vivant() == 1) {

        int numero = get_numero(get_joueur(0));

        quitte_partie(numero);

        classer_joueur(numero);
    }

    afficher_resultat();

    supprimer_plateau();
}



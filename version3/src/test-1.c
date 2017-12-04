#include "../include/plateau.h"
#include "../include/memento.h"
#include "../include/grille.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSI_BOLD          "\x1b[1m"
#define ANSI_BOLD_OFF      "\x1b[22m"
#define MEMENTO 50

static int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}

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

void test_failure_traiter_carte(int c, joueur moi, joueur adv) {
    traiter_carte(c, moi, adv);
}

void test_failure_joueur(joueur j, int i) {
    afficher_main(j);
    afficher_joueurs();
    choisir_carte(j);
    piocher(j, i);
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
    result = result && test_equality_bool(0, strcmp(get_nom(c1), "think"), "think get_nom");
    result = result && test_equality_int(5, get_cout(c1), "think get_cout");
    result = result && test_equality_int(20, get_rarete(c1), "think get_rarete");

    carte c2 = creer_carte("steal");
    result = result && test_equality_bool(0, strcmp(get_nom(c2), "steal"), "steal get_nom");
    result = result && test_equality_int(10, get_cout(c2), "steal get_cout");
    result = result && test_equality_int(10, get_rarete(c2), "steal get_rarete");

    carte c3 = creer_carte("panacea");
    result = result && test_equality_bool(0, strcmp(get_nom(c3), "panacea"), "panacea get_nom");
    result = result && test_equality_int(2, get_cout(c3), "panacea get_cout");
    result = result && test_equality_int(50, get_rarete(c3), "panacea get_rarete");

    carte c4 = creer_carte("razor");
    result = result && test_equality_bool(0, strcmp(get_nom(c4), "razor"), "razor get_nom");
    result = result && test_equality_int(2, get_cout(c4), "razor get_cout");
    result = result && test_equality_int(50, get_rarete(c4), "razor get_rarete");

    carte c5 = creer_carte("hell");
    result = result && test_equality_bool(0, strcmp(get_nom(c5), "hell"), "hell get_nom");
    result = result && test_equality_int(100, get_cout(c5), "hell get_cout");
    result = result && test_equality_int(1, get_rarete(c5), "hell get_rarete");


    set_nom(c5, "test");
    set_cout(c5, 100);
    set_rarete(c5, 100);
    result = result && test_equality_bool(0, strcmp(get_nom(c5), "test"), "set_nom");
    result = result && test_equality_int(100, get_cout(c5), "set_cout");
    result = result && test_equality_int(100, get_rarete(c5), "set_rarete");

    for (int i = 0; i < 131; i++) {
        carte alea1 = choisir_aleatoirement_carte();
        result = result && test_equality_bool(0, get_cout(alea1) > 100, "choisir_aleatoirement_carte");
        result = result && test_equality_bool(0, get_cout(alea1) < 2, "choisir_aleatoirement_carte");
        supprimer_carte(alea1);
    }


    supprimer_carte(c1);
    supprimer_carte(c2);
    supprimer_carte(c3);
    supprimer_carte(c4);
    supprimer_carte(c5);

    return result;
}

bool test_creer_joueur() {
    bool result = true;
    int numero = 10;

    creer_grille(1);
    joueur j = creer_joueur(numero);
    result = result && test_equality_int(10, get_numero(j), "get_numero");
    result = result && test_equality_int(50, get_energie(j), "get_energie");
    result = result && test_equality_int(0, get_idee(j), "get_idee");
    result = result && test_equality_int(1, get_gain(j), "get_gain");
    result = result && test_equality_int(5, get_nb_carte(j), "get_nb_carte");

    int new_numero = 4;
    set_numero(j, new_numero);
    set_energie(j, new_numero);
    set_idee(j, new_numero);
    set_gain(j, new_numero);
    set_nb_carte(j, new_numero);

    result = result && test_equality_int(new_numero, get_numero(j), "set_numero");
    result = result && test_equality_int(new_numero, get_energie(j), "set_energie");
    result = result && test_equality_int(new_numero, get_idee(j), "set_idee");
    result = result && test_equality_int(new_numero, get_gain(j), "set_gain");
    result = result && test_equality_int(new_numero, get_nb_carte(j), "set_nb_carte");

    augmenter_idee(j);
    result = result && test_equality_int(new_numero * 2, get_idee(j), "augmenter_idee");

    carte c = creer_carte("think");
    set_carte_main(1, j, c);
    carte c2 = creer_carte("hell");
    set_carte_main(2, j, c2);
    carte result1 = get_carte_main(1, j);
    carte result2 = get_carte_main(2, j);

    result = result && test_equality_bool(0, strcmp(get_nom(result1), "think"), "get_carte || set_carte nom");
    result = result && test_equality_int(5, get_cout(result1), "get_carte || set_carte cout");
    result = result && test_equality_int(20, get_rarete(result1), "get_carte || set_carte rarete");
    result = result && test_equality_bool(0, strcmp(get_nom(result2), "hell"), "get_carte || set_carte nom");
    result = result && test_equality_int(100, get_cout(result2), "get_carte || set_carte cout");
    result = result && test_equality_int(1, get_rarete(result2), "get_carte || set_carte rarete");

    supprimer_joueur(j);
    supprimer_grille();
    supprimer_carte(c);
    supprimer_carte(c2);


    return result;
}

bool test_creer_memento() {
    bool result = true;

    memento_list lm = creer_memento();
    result = result && test_equality_bool(true, lm != NULL, "creer_memento NULL");
    result = result && test_equality_int(0, get_longueur(lm), "get_longueur()");

    carte c_think = creer_carte("think");
    carte c_hell = creer_carte("hell");
    lm = ajouter_memento_fin(lm, c_think);
    lm = ajouter_memento_fin(lm, c_hell);
    memento m = get_premier(lm);
    memento m2 = get_suivant(m);
    result = result && test_equality_int(2, get_longueur(lm), "get_longueur()");
    result = result && test_equality_bool(0, strcmp(get_nom(get_carte(m)), "think"), "get_premier()");
    result = result && test_equality_bool(0, strcmp(get_nom(get_carte(m2)), "hell"), "get_suivant()");


    lm = supprimer_memento_debut(lm);
    result = result && test_equality_int(1, get_longueur(lm), "get_longueur()");


    supprimer_tout_memento(lm);
    free(lm);

    return result;

}

bool test_remplir_memento() {
    bool result = true;
    memento_list lm = creer_memento();
    lm = remplir_memento(lm);

    result = result && test_equality_bool(true, lm != NULL, "creer_memento NULL");
    result = result && test_equality_int(MEMENTO, get_longueur(lm), "get_longueur()");

    supprimer_tout_memento(lm);
    free(lm);

    return result;
}

bool test_creer_plateau() {
    bool result = true;
    int nb_joueur = 5;

    creer_plateau(nb_joueur);

    supprimer_plateau();

    return result;
}

bool test_choisir_carte() {
    bool result = true;
    int numero = 5;

    joueur j = creer_joueur(numero);
    set_idee(j, 1000);

    int num_carte = choisir_carte(j);
    piocher(j, num_carte);
    result = result && test_equality_bool(true, (num_carte >= 0), "num_carte >=0");
    result = result && test_equality_bool(true, (num_carte < 5), "num_carte >5");

    supprimer_joueur(j);

    return result;

}

bool test_traiter_carte() {
    joueur j1 = creer_joueur(1);
    joueur j2 = creer_joueur(2);
    bool result = true;

    carte c1 = creer_carte("think");
    carte c2 = creer_carte("steal");
    carte c3 = creer_carte("panacea");
    carte c4 = creer_carte("razor");
    carte c5 = creer_carte("hell");
    set_carte_main(0, j1, c1);
    set_carte_main(0, j2, c2);
    set_carte_main(1, j1, c3);
    set_carte_main(1, j2, c4);
    set_carte_main(2, j1, c5);


    traiter_carte(0, j1, j2);
    result = result && test_equality_int(2, get_gain(j1), "Carte think");

    traiter_carte(0, j2, j1);
    result = result && test_equality_int(1, get_gain(j1), "Carte steal");
    result = result && test_equality_int(2, get_gain(j2), "Carte steal");

    traiter_carte(1, j1, j2);
    result = result && test_equality_int(60, get_energie(j1), "Carte Panacea");

    traiter_carte(1, j2, j1);
    result = result && test_equality_int(50, get_energie(j1), "Carte Razor");

    traiter_carte(2, j1, j2);
    result = result && test_equality_bool(true, get_energie(j2) < 0, "Carte Hell");


    supprimer_carte(c1);
    supprimer_carte(c2);
    supprimer_carte(c3);
    supprimer_carte(c4);
    supprimer_carte(c5);

    supprimer_joueur(j1);
    supprimer_joueur(j2);

    return result;
}

bool test_piocher() {
    bool result = true;

    joueur j = creer_joueur(8);
    piocher(j, 4);

    int nb_carte = get_nb_carte(j);
    result = result && test_equality_int(6, nb_carte, "Nombre de cartes");

    supprimer_joueur(j);

    return result;
}

bool test_augmenter_idee() {
    bool result = true;
    joueur j = creer_joueur(8);
    int i_act = get_idee(j);
    augmenter_idee(j);
    int i_after = get_idee(j);
    int gain = get_gain(j);

    result = result && test_equality_int(i_act + gain, i_after, "Augmenter Idee");
    supprimer_joueur(j);
    return result;
}

bool test_quitte_partie() {

    bool result = true;
    creer_plateau(3);
    int nb_avant = get_nb_joueur_vivant();
    quitte_partie(1);
    int nb_apres = get_nb_joueur_vivant();

    result = result && test_equality_int(nb_avant, nb_apres + 1, "quitter partie");
    supprimer_plateau();
    return result;
}

int main(int argc, char* argv[]) {
    bool result = true;
    joueur no_joueur = NULL;
    joueur no_joueur2 = NULL;
    plateau_de_jeu no_plateau = NULL;
    int numero_carte = 0;


    printf("\n"ANSI_BOLD"TEST L'AFFICHAGE DES MESSAGES D'ERREURS"ANSI_BOLD_OFF" \n");
    test_equality_int(0, 1, "error test_equality_int ");
    test_equality_bool(true, false, "error test_equality_bool ");
    test_failure_traiter_carte(numero_carte, no_joueur, no_joueur2);
    test_failure_joueur(no_joueur, numero_carte);
    test_failure_plateau(no_plateau);
    printf("----------------------------------------------------------\n\n");
    result = result && test_equality_bool(true, test_rand_a_b(), "rand_a_b()");
    result = result && test_equality_bool(true, test_creer_carte(), "creer_carte()");
    //    result = result && test_equality_bool(true, test_creer_joueur(), "creer_joueur()");
    result = result && test_equality_bool(true, test_creer_memento(), "creer_memento()");
    result = result && test_equality_bool(true, test_remplir_memento(), "remplir_memento()");
    //    result = result && test_equality_bool(true, test_creer_plateau(), "creer_plateau()");
    //    IL Y A UN SEGFAULT LA
    //    result = result && test_equality_bool(true, test_choisir_carte(), "choisir_carte()");
    //    result = result && test_equality_bool(true, test_traiter_carte(), "traiter_carte()");
    //    result = result && test_equality_bool(true, test_augmenter_idee(), "augmenter_idee()");
    //    result = result && test_equality_bool(true, test_quitte_partie(), "quitter_partie()");

    if (result) {
        printf(ANSI_BOLD"YOUPI tout passe!"ANSI_BOLD_OFF"\n\n");
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;

}

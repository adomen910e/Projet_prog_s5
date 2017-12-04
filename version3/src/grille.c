#include "../include/grille.h"
#include "../include/joueur.h"
#include "../include/plateau.h"
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD          "\x1b[1m"
#define ANSI_BOLD_OFF      "\x1b[22m"
#define TAILLE 50
#define THORIQUE (TAILLE)
#define NB_AMI 100

static grille grille_dj;

struct grille_de_jeu {
    bool** tab;
    int nb_joueur;
    int nb_ami;
    struct position* tab_position_ami;
    int* numero_ennemi;
    bool* autorisation;
    struct position* tab_position_actuelle;
    struct position* tab_position_futur;
};

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

void creer_grille(int nb_joueur) {
    grille_dj = malloc(sizeof (struct grille_de_jeu));
    if (!grille_dj) {
        echec("grille_dj non créé: creer_grille()");
        return;
    }

    grille_dj->tab = calloc(TAILLE, sizeof (bool*));
    if (!grille_dj->tab) {
        echec("grille_dj->tab non créé: creer_grille()");
        return;
    }

    for (int i = 0; i < TAILLE; i++) {
        grille_dj->tab[i] = calloc(TAILLE, sizeof (bool));
        if (!grille_dj->tab[i]) {
            echec("grille_dj->tab[i] non créé: creer_grille()");
            return;
        }
        for (int j = 0; j < TAILLE; j++) {
            grille_dj->tab[i][j] = true;
        }

    }
    grille_dj->nb_joueur = nb_joueur;
    grille_dj->nb_ami = 0;
    grille_dj->tab_position_ami = calloc(NB_AMI, sizeof (struct position));
    grille_dj->numero_ennemi = calloc(NB_AMI, sizeof (int));
    grille_dj->autorisation = calloc(NB_AMI, sizeof (bool));

    grille_dj->tab_position_actuelle = calloc(nb_joueur, sizeof (struct position));
    grille_dj->tab_position_futur = calloc(nb_joueur, sizeof (struct position));
}

void augmenter_nb_ami() {
    grille_dj->nb_ami++;
}

int nb_ami_g() {
    return grille_dj->nb_ami;
}

bool est_libre(int x, int y) {
    return grille_dj->tab[x % THORIQUE][y % THORIQUE];
}

void remplir_grille(int x, int y, int numj, bool ami) {
    grille_dj->tab[x][y] = false;

    if (ami == true) {
        grille_dj->tab_position_ami[grille_dj->nb_ami].x = x;
        grille_dj->tab_position_ami[grille_dj->nb_ami].y = y;
        grille_dj->numero_ennemi[grille_dj->nb_ami] = numj;
        grille_dj->autorisation[grille_dj->nb_ami] = false;
    } else {
        grille_dj->tab_position_actuelle[numj].x = x;
        grille_dj->tab_position_actuelle[numj].y = y;
    }

}

void supprimer_grille() {
    for (int i = 0; i < TAILLE; i++) {
        free(grille_dj->tab[i]);
    }
    free(grille_dj->tab);
    free(grille_dj->tab_position_actuelle);
    free(grille_dj->tab_position_futur);
    free(grille_dj->tab_position_ami);
    free(grille_dj->numero_ennemi);
    free(grille_dj->autorisation);
    free(grille_dj);
}

int est_joueur(int x, int y) {

    for (int i = 0; i < grille_dj->nb_joueur; i++) {
        if (grille_dj->tab_position_actuelle[i].x == x && grille_dj->tab_position_actuelle[i].y == y) {
            return i;
        }
    }

    return -1;
}

int est_ami(int x, int y) {

    for (int i = 0; i < grille_dj->nb_ami; i++) {
        if (grille_dj->tab_position_ami[i].x == x && grille_dj->tab_position_ami[i].y == y) {
            return i;
        }
    }

    return -1;
}

void afficher_grille() {

    for (int i = 0; i < TAILLE; i++) {
        printf(ANSI_COLOR_YELLOW"____"ANSI_COLOR_RESET);
    }

    printf("\n");
    for (int i = 0; i < TAILLE; i++) {

        for (int k = 0; k < TAILLE; k++) {
            if (i != 0) {
                printf(ANSI_COLOR_YELLOW"|___"ANSI_COLOR_RESET);
                if (k == TAILLE - 1)
                    printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET);
            }
        }
        if (i != 0)
            printf("\n");
        for (int j = 0; j < TAILLE; j++) {
            if (grille_dj->tab[i][j] == true) {
                printf(ANSI_COLOR_YELLOW"|   "ANSI_COLOR_RESET);
            } else {
                if (est_joueur(i, j) == -1 && est_ami(i, j) == -1) {
                    printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET " X ");
                } else {
                    if (est_joueur(i, j) == -1) {
                        if (est_ami(i, j) < 10) {
                            printf(ANSI_COLOR_YELLOW"| "ANSI_COLOR_RESET ANSI_COLOR_RED"%d "ANSI_COLOR_RESET, est_ami(i, j));
                        } else {
                            printf(ANSI_COLOR_YELLOW"| "ANSI_COLOR_RESET ANSI_COLOR_RED"%d"ANSI_COLOR_RESET, est_ami(i, j));
                        }
                    } else {
                        printf(ANSI_COLOR_YELLOW"| "ANSI_COLOR_RESET ANSI_BOLD"%d "ANSI_BOLD_OFF, est_joueur(i, j));
                    }

                }
            }

            if (j == TAILLE - 1) {
                printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET);
            }
        }

        printf("\n");
    }

    for (int i = 0; i < TAILLE; i++) {
        printf(ANSI_COLOR_YELLOW"|___"ANSI_COLOR_RESET);
        if (i == TAILLE - 1)
            printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET);
    }
    printf("\n");

}

void creer_bloc(int x, int y) {
    if (est_libre(x + 1, y)) {
        grille_dj->tab[(x + 1) % THORIQUE][y] = false;

    } else if (est_libre(x - 1 + THORIQUE, y)) {
        grille_dj->tab[(x - 1 + THORIQUE) % THORIQUE][y] = false;

    } else if (est_libre(x, y + 1)) {
        grille_dj->tab[x][(y + 1) % THORIQUE] = false;

    } else if (est_libre(x, y - 1 + THORIQUE)) {
        grille_dj->tab[x][(y - 1 + THORIQUE) % THORIQUE] = false;
    }
}

static int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}

static void deplacement_une_case(int numj) {

    int x = grille_dj->tab_position_futur[numj].x;
    int y = grille_dj->tab_position_futur[numj].y;

    int i = rand_a_b(1, 4);

    switch (i) {
        case 1:
            if (est_libre(x + 1, y)) {
                grille_dj->tab_position_futur[numj].x = (x + 1) % THORIQUE;
                grille_dj->tab_position_futur[numj].y = y;
                return;

            }

        case 2:
            if (est_libre((x - 1) + THORIQUE, y)) {
                grille_dj->tab_position_futur[numj].x = (x - 1 + THORIQUE) % THORIQUE;
                grille_dj->tab_position_futur[numj].y = y;
                return;

            }

        case 3:
            if (est_libre(x, y + 1)) {
                grille_dj->tab_position_futur[numj].x = x;
                grille_dj->tab_position_futur[numj].y = (y + 1) % THORIQUE;
                return;
            }

        case 4:
            if (est_libre(x, (y - 1) + THORIQUE)) {
                grille_dj->tab_position_futur[numj].x = x;
                grille_dj->tab_position_futur[numj].y = (y - 1 + THORIQUE) % THORIQUE;
                return;
            }

    }
}

void deplacement_total(int numj) {
    int i = rand_a_b(0, 4);

    for (; i < 5; i++) {
        deplacement_une_case(numj);
    }
}

void deplacement_une_case_ami(struct position *p, struct position ad) {


    grille_dj->tab[p->x][p->y] = true;

    int i = rand_a_b(1, 4);


    switch (i) {
        case 1:
            if (est_libre(p->x + 1, p->y) && (ad.x > p->x)) {
                p->x = (p->x + 1) % THORIQUE;
                return;

            }

        case 2:
            if (est_libre((p->x - 1) + THORIQUE, p->y) && (ad.x < p->x)) {
                p->x = (p->x - 1 + THORIQUE) % THORIQUE;
                return;

            }

        case 3:
            if (est_libre(p->x, p->y + 1) && (ad.y > p->y)) {
                p->y = (p->y + 1) % THORIQUE;
                return;
            }

        case 4:
            if (est_libre(p->x, (p->y - 1) + THORIQUE) && (ad.y < p->y)) {
                p->y = (p->y - 1 + THORIQUE) % THORIQUE;
                return;
            }

    }
}

void deplacement_ami(struct position *p, int i, struct position ad) {

    int j = rand_a_b(0, 1);

    for (; j < 2; j++) {
        deplacement_une_case_ami(p, ad);
    }

    remplir_grille(p->x, p->y, i, true);
}

bool est_autorise(int i) {
    return grille_dj->autorisation[i];
}

void init_autorisation() {
    for (int i = 0; i < grille_dj->nb_ami; i++) {
        grille_dj->autorisation[i] = false;
    }
}

void faire_deplacement_simultanement() {

    int tab_joueur_pas_deplacement[grille_dj->nb_joueur * 2];
    int indice = 0;


    //verifier les colisions
    for (int i = 0; i < grille_dj->nb_joueur; i++) {
        for (int j = i + 1; j < grille_dj->nb_joueur; j++) {
            if (grille_dj->tab_position_futur[i].x == grille_dj->tab_position_futur[j].x &&
                    grille_dj->tab_position_futur[i].y == grille_dj->tab_position_futur[j].y) {
                tab_joueur_pas_deplacement[indice++] = i;
                tab_joueur_pas_deplacement[indice++] = j;
            }
        }
    }

    //dire au joueur avec colision de ne pas bouger
    for (int i = 0; i < indice; i++) {
        grille_dj->tab_position_futur[tab_joueur_pas_deplacement[i]].x = grille_dj->tab_position_actuelle[tab_joueur_pas_deplacement[i]].x;
        grille_dj->tab_position_futur[tab_joueur_pas_deplacement[i]].y = grille_dj->tab_position_actuelle[tab_joueur_pas_deplacement[i]].y;
    }

    //joueur tout les deplacements des personnes
    for (int i = 0; i < grille_dj->nb_joueur; i++) {
        grille_dj->tab[ grille_dj->tab_position_actuelle[i].x][ grille_dj->tab_position_actuelle[i].y] = true;
        remplir_grille(grille_dj->tab_position_futur[i].x, grille_dj->tab_position_futur[i].y, i, false);
        if (!est_mort(get_joueur(i))) {
            set_position_x(get_joueur(i), grille_dj->tab_position_futur[i].x);
            set_position_y(get_joueur(i), grille_dj->tab_position_futur[i].y);
        }

    }

    for (int i = 0; i < grille_dj->nb_ami; i++) {
        if (est_autorise(i) == true) {
            struct position adversaire = grille_dj->tab_position_actuelle[grille_dj->numero_ennemi[i]];
            deplacement_ami(&grille_dj->tab_position_ami[i], i, adversaire);
        }
    }

    init_autorisation();

}

bool est_encercle(int x, int y) {
    if (!est_libre(x + 1, y) && !est_libre(x - 1 + THORIQUE, y) && !est_libre(x, y + 1) && !est_libre(x, y - 1 + THORIQUE)) {
        return true;
    }
    return false;
}

void afficher_position() {
    for (int i = 0; i < grille_dj->nb_joueur; i++)
        printf("Le joueur %d X=%d Y=%d\n", i, grille_dj->tab_position_actuelle[i].x, grille_dj->tab_position_actuelle[i].y);
}

void afficher_position_ami() {

    for (int i = 0; i < grille_dj->nb_ami; i++) {
        //printf("L' ami %d attaque %d --------   X=%d Y=%d\n", i, grille_dj->numero_ennemi[i], grille_dj->tab_position_ami[i].x, grille_dj->tab_position_ami[i].y);
        printf("%d", grille_dj->autorisation[i]);
    }
    printf(" \n");
}

void autoriser(int i) {
    grille_dj->autorisation[i] = true;
}

void non_autoriser(int i) {
    grille_dj->autorisation[i] = false;
}

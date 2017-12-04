#include "../include/carte.h"
#include <string.h>
#include <time.h>

#define PROBA 146

struct carte {
    char* nom;
    int cout;
    int rarete;
};

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

carte creer_carte(char* nom) {
    if (nom == NULL) {
        echec("nom NULL: creer_carte()");
        return NULL;
    }

    carte c = malloc(sizeof (struct carte));

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

    if (strcmp(nom, "stone") == 0) {
        c->nom = nom;
        c->cout = 10;
        c->rarete = 100 / 10;
    }

    if (strcmp(nom, "puppy") == 0) {
        c->nom = nom;
        c->cout = 5;
        c->rarete = 100 / 5;
    }

    return c;
}

void supprimer_carte(carte c) {
    free(c);
}

carte copie_carte(carte c) {
    return creer_carte(c->nom);
}

char* get_nom(carte c) {
    if (c == NULL) {
        echec("carte NULL : get_nom()");
        return NULL;
    }

    return c->nom;
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

void set_cout(carte c, int a) {
    if (c == NULL) {
        echec("carte NULL : set_cout()");
        return;
    }

    c->cout = a;
}

void set_rarete(carte c, int a) {
    if (c == NULL) {
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

int rand_a_b(int min, int max) {
    return rand() % (max - min) + min;
}

carte choisir_aleatoirement_carte() {

    int alea = rand_a_b(0, PROBA);

    if (alea < 20) {
        return creer_carte("think");
    } else if (alea < 30) {
        return creer_carte("steal");
    } else if (alea < 80) {
        return creer_carte("panacea");
    } else if (alea < 130) {
        return creer_carte("razor");
    } else if (alea == 131) {
        return creer_carte("hell");
    } else if (alea < 141) {
        return creer_carte("stone");
    }

    return creer_carte("puppy");
}
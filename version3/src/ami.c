#include "../include/ami.h"
#include "../include/grille.h"
#include "../include/carte.h"

#include <string.h>
#include <time.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD          "\x1b[1m"
#define ANSI_BOLD_OFF      "\x1b[22m"

#define THORIQUE 49

struct ami {
    int numero_adversaire;
    int numero_maitre;
    int numero_joueur;
    int vie;
    int energie;
    int idee;
    int gain;
    carte c;
    struct position position;
};

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

void definir_pos(ami a, struct position p) {
    if (est_libre(p.x + 1, p.y)) {
        a->position.x = (p.x + 1) % THORIQUE;
        a->position.y = p.y;

    } else if (est_libre(p.x - 1 + THORIQUE, p.y)) {
        a->position.x = (p.x - 1 + THORIQUE) % THORIQUE;
        a->position.y = p.y;

    } else if (est_libre(p.x, p.y + 1)) {
        a->position.x = p.x;
        a->position.y = (p.y + 1) % THORIQUE;

    } else if (est_libre(p.x, p.y - 1 + THORIQUE)) {
        a->position.x = p.x;
        a->position.y = (p.y - 1 + THORIQUE) % THORIQUE;
    }
}

ami creer_ami(int adversaire, int num, struct position p, carte c) {

    ami a = calloc(1, sizeof (struct ami));
    if (!a) {
        echec("ami non créé: cree_ami()");
        return NULL;
    }

    a->numero_adversaire = adversaire;
    a->numero_maitre = nb_ami_g();
    a->numero_joueur = num;
    a->vie = 20;
    a->energie = 1;
    a->idee = 1;
    a->gain = 1;
    a->c = c;


    definir_pos(a, p);
    remplir_grille(a->position.x, a->position.y, adversaire, true);
    augmenter_nb_ami();
    printf("NUMERO JOUEUR %d\n", num);
    printf("XXXXX= %d YYYYYYY= %d\n\n", p.x, p.y);
    printf("XXXXX= %d YYYYYYY= %d\n\n", a->position.x, a->position.y);

    return a;

}

void supprimer_ami(ami a) {
    supprimer_carte(a->c);
    free(a);
}

int numero_joueur_ami(ami a) {
    //TODO

    return a->numero_joueur;
}

void augmenter_gain(ami a) {
    //TODO

    a->gain++;
}

int get_numero_cible(ami a) {
    //TODO

    return a->numero_adversaire;
}

int get_numero_maitre(ami a) {
    //TODO

    return a->numero_maitre;
}

carte recuperer_carte_ami(ami a) {
    //TODO

    return a->c;
}

void augmenter_energie(ami a, int i) {
    //TODO

    a->energie += i;
}

void diminuer_energie(ami a, int i) {
    //TODO

    a->energie -= i;
}

void diminuer_idee(ami a, int i) {
    //TODO

    a->idee -= i;
}

int get_idee_ami(ami a) {
    //TODO

    return a->idee;
}

void diminuer_vie(ami a) {
    a->vie--;
}

int get_vie_ami(ami a) {
    //TODO

    return a->vie;
}

void afficher_ami(ami a) {

    if (a == NULL) {
        echec("joueur NULL: afficher_main()");
        return;
    }
    printf(ANSI_BOLD"  AMI %d :"ANSI_BOLD_OFF"\n", a->numero_maitre);
    printf("        -Nombre de tour restant : %d\n", a->vie);
    printf("        -Energie : %d\n", a->energie);
    printf("        -Idee : %d\n", a->idee);
    printf("        -Gain : %d\n", a->gain);

    printf("             __________ \n");
    if (strcmp(get_nom(a->c), "panacea") == 0) {
        printf("            |"ANSI_COLOR_RED ANSI_BOLD"  %s "ANSI_COLOR_RESET ANSI_BOLD_OFF"|  ", get_nom(a->c));
    } else if (strcmp(get_nom(a->c), "hell") == 0) {
        printf("            |"ANSI_COLOR_RED ANSI_BOLD"   %s   "ANSI_COLOR_RESET ANSI_BOLD_OFF"|  ", get_nom(a->c));
    } else {
        printf("            |"ANSI_COLOR_RED ANSI_BOLD"  %s"ANSI_COLOR_RESET ANSI_BOLD_OFF"   |  ", get_nom(a->c));
    }
    printf("\n");
    printf("            |          |\n");
    if (get_cout(a->c) < 10) {
        printf("            |"ANSI_COLOR_YELLOW"         %d"ANSI_COLOR_RESET"|  ", get_cout(a->c));
    } else if (get_cout(a->c) == 100) {
        printf("            |"ANSI_COLOR_YELLOW"       %d"ANSI_COLOR_RESET"|  ", get_cout(a->c));
    } else {
        printf("            |"ANSI_COLOR_YELLOW"        %d"ANSI_COLOR_RESET"|  ", get_cout(a->c));
    }
    printf("\n");
    if (get_rarete(a->c) == 1) {
        printf("            |"ANSI_COLOR_YELLOW"     %d/131"ANSI_COLOR_RESET"|  ", get_rarete(a->c));
    } else {
        printf("            |"ANSI_COLOR_YELLOW"    %d/131"ANSI_COLOR_RESET"|  ", get_rarete(a->c));
    }
    printf("\n");
    printf("            |__________|\n");

    printf("\n\n\n");
}

void augmenter_idee_ami(ami a) {
    //TODO

    a->idee++;
}

struct position get_pos_ami(ami a) {
    //TODO

    return a->position;
}
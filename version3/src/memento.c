#include "../include/memento.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define NB_CARTE_BEGIN 5
#define MEMENTO 50

struct memento_list {
    int longueur;
    memento premier;
    memento dernier;
};

struct memento {
    memento precedent;
    memento suivant;
    carte c;
};

memento_list creer_memento() {
    memento_list m_new = malloc(sizeof (struct memento_list));
    if (m_new != NULL) {
        m_new->longueur = 0;
        m_new->premier = NULL;
        m_new->dernier = NULL;
    }
    return m_new;
}

void supprimer_memento(memento m) {
    supprimer_carte(m->c);
    free(m);
}

memento_list ajouter_memento_fin(memento_list p_list, carte ca) {

    if (p_list != NULL) {
        memento p_new = malloc(sizeof *p_new);
        if (p_new != NULL) {
            p_new->c = ca;
            p_new->suivant = NULL;
            if (p_list->dernier == NULL) {
                p_new->precedent = NULL;
                p_list->premier = p_new;
                p_list->dernier = p_new;
            } else {
                p_list->dernier->suivant = p_new;
                p_new->precedent = p_list->dernier;
                p_list->dernier = p_new;
            }
            p_list->longueur++;
        }
    }
    return p_list;
}

memento_list supprimer_memento_debut(memento_list m) {

    if (m != NULL) {
        if (m->longueur > 1) {
            memento tmp = m->premier->suivant;
            supprimer_memento(m->premier);

            m->premier = tmp;
            m->longueur--;

            return m;

        } else {
            supprimer_memento(m->premier);
            free(m);
        }
    }

    return NULL;
}

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

static int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}

memento_list remplir_memento(memento_list m) {
    if (m == NULL) {
        echec("memento NULL: remplir_memento()");
        return NULL;
    }

    for (int i = 0; i < MEMENTO; i++) {
        carte ca = choisir_aleatoirement_carte();
        m = ajouter_memento_fin(m, ca);
    }

    return m;
}

carte get_carte(memento m) {
    return m->c;
}

memento get_suivant(memento m) {
    return m->suivant;
}

memento get_premier(memento_list m) {
    return m->premier;
}

void melanger_memento(carte * memento) {

    if (memento == NULL) {
        echec("memento NULL: melanger_memento()");
        return;
    }

    for (int j = 0; j < NB_CARTE_BEGIN; j++) {
        srand(time(NULL));
        int randval = rand_a_b(0, MEMENTO - 1);

        //fonction d'echange de deux cartes
        char* tmp_nom = get_nom(memento[j]);
        int tmp_cout = get_cout(memento[j]);
        int tmp_rarete = get_rarete(memento[j]);

        set_nom(memento[j], get_nom(memento[randval]));
        set_cout(memento[j], get_cout(memento[randval]));
        set_rarete(memento[j], get_rarete(memento[randval]));

        set_nom(memento[randval], tmp_nom);
        set_cout(memento[randval], tmp_cout);
        set_rarete(memento[randval], tmp_rarete);

    }
}

void supprimer_tout_memento(memento_list m) {


    memento p_temp;
    memento p_del;

    if (m != NULL) {
        p_temp = m->premier;
        while (p_temp != NULL) {
            p_del = p_temp;
            p_temp = p_temp->suivant;
            supprimer_memento(p_del);
        }
    }
}

void afficher_memento(memento_list m) {
    memento tmp = m->premier;
    for (int i = 0; i < m->longueur; i++) {
        tmp = tmp->suivant;
    }
}

int get_longueur(memento_list lm) {
    if (lm == NULL) {
        echec("liste de memento NULL : longueur_memento()");
        return EXIT_FAILURE;
    }

    return lm->longueur;
}


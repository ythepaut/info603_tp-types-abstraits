/**
 * INFO603 TP Exercice 3
 * Lucas CHARDONNET - Yohann THEPAUT
 *
 * Implémentation du type abstrait graphe
 */

#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"


/**
 * Crée un graphe d'ordre n
 * @param matriceAdjacences in          int[][]         Matrice d'ajacences :
 *                                                      Soit i, j les coordonnées dans la matrice,
 *                                                      matrice[i][j] ≠ 0 ⇒ noeud i est lié au noeud j par une arête
 *                                                      de poids matrice[i][j].
 * @param n                 in          int             Ordre du graphe
 * @return                                              Graphe correspondant à la matrice d'ajacences
 */
Graphe *creerGraphe(const int *matriceAdjacences, int n) {

    // Initialisation du graphe
    Graphe *graphe = malloc(sizeof(Graphe));
    graphe->ordre = n;
    graphe->noeuds = calloc(graphe->ordre, sizeof(Noeud));

    // Initialisation des noeuds
    for (int i = 0 ; i < graphe->ordre ; ++i) {
        Noeud *noeud = &graphe->noeuds[i];
        noeud->numero = i;
        noeud->aretes = NULL;
        noeud->nbAretes = 0;
    }
    // Lecture de la matrice d'adjacences et ajout des aretes au graphe
    for (int i = 0 ; i < graphe->ordre ; ++i) {
        Noeud *noeud = &graphe->noeuds[i];
        for (int j = 0 ; j < graphe->ordre ; ++j) {
            int poids = *((matriceAdjacences + i * n) + j);
            if (poids != 0) {
                ajouteArete(noeud, creerArete(noeud, &graphe->noeuds[j], poids));
            }
        }
    }

    return graphe;
}

/**
 * Libère toutes les allocations du graphe
 * @param graphe        in-out          Graphe          Graphe à libérer
 */
void detruireGraphe(Graphe *graphe) {
    for (int i = 0 ; i < graphe->ordre ; ++i)
        free(graphe->noeuds[i].aretes);
    free(graphe->noeuds);
    free(graphe);
}

/**
 * Fonction qui crée une arête entre deux noeuds
 * @param noeudA        in              Noeud           Premier noeud à lier
 * @param noeudB        in              Noeud           Deuxieme noeud à lier
 * @param poids         in              int             Poids de l'arête
 * @return                                              Arête créée
 */
Arete creerArete(Noeud *noeudA, Noeud *noeudB, int poids) {
    Arete arete = {
            .noeudA = noeudA,
            .noeudB = noeudB,
            .poids = poids
    };
    return arete;
}

/**
 * Fonction qui ajoute une arête au noeud
 * @param noeud         in-out          Noeud           Noeud à modifier
 * @param arete         in              Arete           Arête à ajouter au noeud
 */
void ajouteArete(Noeud *noeud, Arete arete) {
    assert(arete.noeudA == noeud || arete.noeudB == noeud);
    noeud->aretes = realloc(noeud->aretes, ++noeud->nbAretes * sizeof(Arete));
    noeud->aretes[noeud->nbAretes - 1] = arete;
}

/**
 * Fonction qui "affiche" le graphe (affiche toutes les relations)
 * @param graphe        in              Graphe          Graphe à afficher
 */
void afficheGraphe(Graphe *graphe) {
    for (int i = 0; i < graphe->ordre; ++i) {
        Noeud *noeud = &graphe->noeuds[i];
        for (int j = 0; j < noeud->nbAretes; ++j) {
            Arete *arete = &noeud->aretes[j];
            printf("Noeud %d    --[%d]->    Noeud %d\n", arete->noeudA->numero, arete->poids, arete->noeudB->numero);
        }
    }
}

/**
 * Algorithme de Dijkstra : Recherche le plus cours chemin entre deux noeuds
 * @param graphe        in              Graphe          Graphe dans lequel on fait la recherche
 * @param origine       in              Noeud           Noeud de départ
 * @param destination   in              Noeud           Noeud d'arrivée
 */
void dijkstra(Graphe *graphe, Noeud origine, Noeud destination) {

    // Initialisation des poids de tous les noeuds à -1 (infini)
    int poids[graphe->ordre];
    for (int i = 0 ; i < graphe->ordre ; ++i)
        poids[i] = -1;

    // Initialisation des prédécesseurs, càd le noeud par lequel le chemin est le
    // plus court pour un accéder à ce noeud
    Noeud* predecesseurs[graphe->ordre];
    for (int i = 0 ; i < graphe->ordre ; ++i)
        predecesseurs[i] = NULL;

    // Initialisation du sous-graphe P contenant les noeuds parcourus
    //Graphe P = creerGraphe();
}

int main() {

    int matriceAdjacences[13][13] = {
            {0, 7, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {7, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0},
            {2, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0},
            {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
            {0, 4, 4, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0},
            {0, 0, 0, 0, 5, 0, 0, 0, 3, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 4, 4, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 6, 4},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 4},
            {0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4, 4, 0}
    };

    Graphe *graphe = creerGraphe((int *) matriceAdjacences, 13);

    afficheGraphe(graphe);

    detruireGraphe(graphe);

    return EXIT_SUCCESS;
}

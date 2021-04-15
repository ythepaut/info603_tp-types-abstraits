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
        for (int j = i ; j < graphe->ordre ; ++j) {
            int poids = *((matriceAdjacences + i * n) + j);
            if (poids != 0) {
                ajouteArete(noeud, creerArete(noeud, &graphe->noeuds[j], poids));
                ajouteArete(noeud, creerArete(&graphe->noeuds[j], noeud, poids));
            }
        }
    }

    return graphe;
}

/**
 * Fonction qui crée une arête entre deux noeuds
 * @param noeudA        in              Noeud           Premier noeud à lier
 * @param noeudB        in              Noeud           Deuxieme noeud à lier
 * @param poids         in              int             Poids de l'arête
 * @return                                              Arête créée
 */
Arete *creerArete(Noeud *noeudA, Noeud *noeudB, int poids) {
    Arete *arete = (Arete *) malloc(sizeof(Arete));
    arete->noeudA = noeudA;
    arete->noeudB = noeudB;
    arete->poids = poids;
    return arete;
}

/**
 * Fonction qui ajoute une arête au noeud
 * @param noeud         in-out          Noeud           Noeud à modifier
 * @param arete         in              Arete           Arête à ajouter au noeud
 */
void ajouteArete(Noeud *noeud, Arete *arete) {
    noeud->aretes = realloc(noeud->aretes, ++noeud->nbAretes * sizeof(Arete));
    noeud->aretes[noeud->nbAretes - 1] = *arete;
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

    return EXIT_SUCCESS;
}

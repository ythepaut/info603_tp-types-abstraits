/**
 * INFO603 TP Exercice 3
 * Lucas CHARDONNET - Yohann THEPAUT
 *
 * Implémentation du type abstrait graphe
 */

#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"
#include "utils.h"


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
    // Lecture de la matrice d'adjacences et ajout des arêtes au graphe
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
 * Fonction qui retourne vrai s'il existe un noeud dans g1 qui n'est pas dans g2
 */
int noeudPresent(Graphe *g1, Graphe *g2) {
    for (int i = 0 ; i < g1->ordre ; ++i) {
        int present = 0;
        for (int j = 0 ; j < g2->ordre ; ++j) {
            if (g2->noeuds[j].numero == g1->noeuds[i].numero) {
                present = 1;
                break;
            }
        }
        if (!present) {
            return 0;
        }
    }
    return 1;
}

/**
 * Fonction qui trouve le noeud dans g, hors du sous graphe, de plus petit poids
 * (Utilisé pour l'algorithme de Dijkstra)
 * @param graphe        in              Graphe*         Graphe principal
 * @param sousGraphe    in              Graphe*         Sous graphe
 * @param poids         in              int[]           Liste des poids des noeuds
 * @return                                              Noeud
 */
Noeud *noeudDePlusPetitPoidsHorsDeP(Graphe *graphe, Graphe* sousGraphe, int poids[]) {
    Noeud *resultat = NULL;
    int minPoids = -1;

    for (int i = 0 ; i < graphe->ordre ; ++i) {

    }

    return resultat;
}

/**
 * Algorithme de Dijkstra : Recherche le plus cours chemin entre deux noeuds
 * @param graphe        in              Graphe*         Graphe dans lequel on fait la recherche
 * @param origine       in              Noeud*          Noeud de départ
 * @param destination   in              Noeud*          Noeud d'arrivée
 */
void dijkstra(Graphe *graphe, Noeud *origine, Noeud *destination) {

    // Initialisation des poids de tous les noeuds à -1 (infini)
    int poids[graphe->ordre];
    for (int i = 0 ; i < graphe->ordre ; ++i)
        poids[i] = -1;

    // Initialisation des prédécesseurs, càd le noeud par lequel le chemin est le
    // plus court pour un accéder à ce noeud
    Noeud* predecesseurs[graphe->ordre];
    for (int i = 0 ; i < graphe->ordre ; ++i)
        predecesseurs[i] = NULL;

    // Initialisation du sous-graphe contenant les noeuds parcourus
    int *matriceAdjacences = matriceVide(graphe->ordre, graphe->ordre);
    Graphe *sousGraphe = creerGraphe(matriceAdjacences, graphe->ordre);
    free(matriceAdjacences);

    // Poids du noeud à l'origine initialisé à 0
    poids[index(graphe->noeuds, graphe->ordre, origine)] = 0;

    // Tant qu'il existe un sommet du graphe qui n'est pas dans sousGraphe
    do {




    } while (noeudPresent(graphe, sousGraphe));
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

    dijkstra(graphe, &graphe->noeuds[0], &graphe->noeuds[5]);

    detruireGraphe(graphe);

    return EXIT_SUCCESS;
}

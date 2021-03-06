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
Graphe *creerGraphe(int *matriceAdjacences, int n) {

    // Initialisation du graphe
    Graphe *graphe = malloc(sizeof(Graphe));
    graphe->ordre = n;
    graphe->noeuds = calloc(graphe->ordre, sizeof(Noeud));

    // Initialisation des noeuds
    for (int i = 0; i < graphe->ordre; ++i) {
        Noeud *noeud = &graphe->noeuds[i];
        noeud->numero = i;
        noeud->aretes = NULL;
        noeud->nbAretes = 0;
    }
    // Lecture de la matrice d'adjacences et ajout des arêtes au graphe
    for (int i = 0; i < graphe->ordre; ++i) {
        Noeud *noeud = &graphe->noeuds[i];
        for (int j = 0; j < graphe->ordre; ++j) {
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
    for (int i = 0; i < graphe->ordre; ++i)
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
    printf("== Affichage du graphe ==\n");
    for (int i = 0; i < graphe->ordre; ++i) {
        Noeud *noeud = &graphe->noeuds[i];
        for (int j = 0; j < noeud->nbAretes; ++j) {
            Arete *arete = &noeud->aretes[j];
            printf("Noeud %d    --[%d]->    Noeud %d\n", arete->noeudA->numero, arete->poids, arete->noeudB->numero);
        }
    }
    printf("========================\n");
}

/**
 * Retourne le noeud i du graphe
 */
Noeud *getNoeud(Graphe *graphe, int i) {
    return &graphe->noeuds[i];
}

/**
 * Retourne l'indice du noeud dans le graphe
 * @param graphe        in              Graphe          Graphe de recherche
 * @param noeud         in              Noeud           Noeud recherché
 * @return                                              Indice du noeud dans le graphe ou -1 si non présent
 */
int indiceNoeud(Graphe *graphe, Noeud *noeud) {
    for (int i = 0; i < graphe->ordre; ++i)
        if (graphe->noeuds[i].numero == noeud->numero)
            return i;
    return -1;
}

/**
 * Fonction qui retourne vrai s'il existe un noeud dans g1 qui n'a pas été
 * marqué comme parcouru dans g2
 */
int noeudNonParcouru(Graphe *g1, const int g2[]) {
    for (int i = 0; i < g1->ordre; ++i)
        if (!g2[i])
            return 1;
    return 0;
}

/**
 * Fonction qui retourne le poids entre deux noeuds (0 si non voisins)
 */
int poidsEntreNoeuds(Graphe *graphe, Noeud *a, Noeud *b) {
    for (int i = 0; i < a->nbAretes; i++)
        if (a->aretes[i].noeudA->numero == b->numero || a->aretes[i].noeudB->numero == b->numero)
            return a->aretes[i].poids;
    return 0;
}

/**
 * Fonction qui trouve le noeud dans g, hors du sous graphe, de plus petit poids
 * (Utilisé pour l'algorithme de Dijkstra)
 * @param graphe        in              Graphe*         Graphe principal
 * @param sousGraphe    in              int[]           Sous graphe qui indique si le noeud d'indice i a été parcouru
 * @param poids         in              int[]           Liste des poids des noeuds
 * @return                                              Indice du noeud dans le graphe
 */
int noeudDePlusPetitPoidsHorsDeSousGraphe(Graphe *graphe, const int sousGraphe[], const int poids[]) {
    int resultat = -1;
    for (int i = 0; i < graphe->ordre; ++i)
        if (sousGraphe[i] == 0)
            if (resultat == -1 || (poids[i] < poids[resultat] && poids[i] != -1))
                resultat = i;
    return resultat;
}

/**
 * Algorithme de Dijkstra : Recherche le plus cours chemin entre deux noeuds
 * @param graphe        in              Graphe*         Graphe dans lequel on fait la recherche
 * @param origine       in              Noeud*          Noeud de départ
 */
void dijkstra(Graphe *graphe, Noeud *origine) {

    // Initialisation des poids de tous les noeuds à -1 (infini)
    int poids[graphe->ordre];
    for (int i = 0; i < graphe->ordre; ++i)
        poids[i] = -1;

    // Initialisation des prédécesseurs, càd le noeud par lequel le chemin est le
    // plus court pour un accéder à ce noeud
    Noeud *predecesseurs[graphe->ordre];
    for (int i = 0; i < graphe->ordre; ++i)
        predecesseurs[i] = NULL;

    // Initialisation de la liste des noeuds parcourus (sousGraphe[i] = 1 => noeud i parcouru)
    int sousGraphe[graphe->ordre];
    for (int i = 0; i < graphe->ordre; ++i)
        sousGraphe[i] = 0;

    // Poids du noeud à l'origine initialisé à 0
    poids[indiceNoeud(graphe, origine)] = 0;

    // Tant que le noeud destination n'a pas été parcouru
    do {

        // Récupère le noeud de plus petite distance, non parcouru
        int indiceNoeudA = noeudDePlusPetitPoidsHorsDeSousGraphe(graphe, sousGraphe, poids);
        Noeud *noeudA = getNoeud(graphe, indiceNoeudA);

        // Défini le noeud comme parcouru
        sousGraphe[indiceNoeudA] = 1;

        // Pour chaque noeud, non parcouru, voisin de noeudA
        for (int i = 0; i < graphe->ordre; ++i) {
            Noeud *noeudB = getNoeud(graphe, i);
            if (sousGraphe[i] == 0 && poidsEntreNoeuds(graphe, noeudA, noeudB)) {

                int poidsA = poids[indiceNoeud(graphe, noeudA)];
                int poidsB = poids[indiceNoeud(graphe, noeudB)];
                int poidsAB = poidsEntreNoeuds(graphe, noeudA, noeudB);

                // Si poids plus leger
                if ((poidsB == -1 || poidsB > poidsA + poidsAB) && poidsA != -1) {

                    // Affectation du nouveau poids du noeudB
                    poids[indiceNoeud(graphe, noeudB)] = poidsA + poidsAB;

                    // Modification du prédecesseur de B, à A
                    predecesseurs[indiceNoeud(graphe, noeudB)] = noeudA;
                }

            }
        }

    } while (noeudNonParcouru(graphe, sousGraphe));

    // DEBUG : Affichage de tous les noeuds avec poids et predecesseur
    for (int i = 0; i < graphe->ordre; ++i) {
        printf("Noeud %d, poids=%d par %d\n", getNoeud(graphe, i)->numero, poids[i],
               predecesseurs[i] != NULL ? predecesseurs[i]->numero : -1);
    }
}

int main() {

    printf("Implémentation du graphe avec les structures noeud et aretes (pointeurs)\n");

    // Matrice d'adjacence uniquement utilisée pour créer le graphe avec la structure de donnée
    // définie dans graphe.h
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

    dijkstra(graphe, getNoeud(graphe, 0));

    detruireGraphe(graphe);

    return EXIT_SUCCESS;
}

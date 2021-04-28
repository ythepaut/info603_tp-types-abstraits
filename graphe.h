/**
 * INFO603 TP Exercice 3
 * Lucas CHARDONNET - Yohann THEPAUT
 *
 * Implémentation du type abstrait graphe
 */

#ifndef TP1_GRAPHE_H
#define TP1_GRAPHE_H

#include "assert.h"

struct SNoeud;

typedef struct SArete {
    struct SNoeud *noeudA;
    struct SNoeud *noeudB;
    int poids;
} Arete;

typedef struct SNoeud {
    int numero;
    Arete *aretes;
    int nbAretes;
} Noeud;

typedef struct SGraphe {
    int ordre;
    Noeud *noeuds;
} Graphe;


Graphe *creerGraphe(const int *matriceAdjacences, int n);

void detruireGraphe(Graphe *graphe);

Arete creerArete(Noeud *noeudA, Noeud *noeudB, int poids);

void ajouteArete(Noeud *noeud, Arete arete);

void afficheGraphe(Graphe *graphe);

int noeudPresent(Graphe *g1, Graphe *g2);

void dijkstra(Graphe *graphe, Noeud *origine, Noeud *destination);

#endif //TP1_GRAPHE_H

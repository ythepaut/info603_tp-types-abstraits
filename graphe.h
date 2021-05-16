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

int indiceNoeud(Graphe *graphe, Noeud *noeud);

int noeudNonParcouru(Graphe *g1, const int g2[]);

int poidsEntreNoeuds(Noeud *a, Noeud *b);

int noeudDePlusPetitPoidsHorsDeSousGraphe(Graphe *graphe, const int sousGraphe[], const int poids[]);

void dijkstra(Graphe *graphe, Noeud *origine, Noeud *destination);

#endif //TP1_GRAPHE_H

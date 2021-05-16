/**
 * INFO603 TP Exercice 3
 * Lucas CHARDONNET - Yohann THEPAUT
 *
 * Deuxième implémentation du type abstrait graphe
 */

#ifndef TP1_GRAPHE2_H
#define TP1_GRAPHE2_H

#include "assert.h"

typedef struct SGraphe {
    int *matrice;
    int ordre;
} Graphe;

typedef struct SNoeud {
    int numero;
} Noeud;


void dijkstra(Graphe *graphe, Noeud *origine);


// Fonctions communes au type graphe
Graphe *creerGraphe(int *matriceAdjacences, int n);

void detruireGraphe(Graphe *graphe);

void afficheGraphe(Graphe *graphe);

Noeud *getNoeud(Graphe *graphe, int i);

int indiceNoeud(Graphe *graphe, Noeud *noeud);

int noeudNonParcouru(Graphe *g1, const int g2[]);

int poidsEntreNoeuds(Graphe *graphe, Noeud *a, Noeud *b);

int noeudDePlusPetitPoidsHorsDeSousGraphe(Graphe *graphe, const int sousGraphe[], const int poids[]);

#endif //TP1_GRAPHE2_H

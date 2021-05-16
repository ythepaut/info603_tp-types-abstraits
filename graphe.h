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


// Fonctions spécifiques à l'implémentation du graphe
Arete creerArete(Noeud *noeudA, Noeud *noeudB, int poids);

void ajouteArete(Noeud *noeud, Arete arete);

#endif //TP1_GRAPHE_H

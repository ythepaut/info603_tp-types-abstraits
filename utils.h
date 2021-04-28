/**
 * INFO603 TP
 * Lucas CHARDONNET - Yohann THEPAUT
 *
 * Fonctions utiles communes aux exercices
 */

#ifndef TP1_UTILS_H
#define TP1_UTILS_H

#include <stdio.h>

void permuter(int* a, int* b);

int* max(int* a, int* b);

int* min(int* a, int* b);

void afficheTableau(int* tab, int n);

void tableauAleatoire(int* tab, int n, int max);

int plusGrandElement(const int *tab, int indexDebut, int indexFin);

int plusPetitElement(const int *tab, int indexDebut, int indexFin);

int estTrie(const int* tab, int indexDebut, int indexFin);

int *matriceVide(int n, int m);

int index(void *tab, int taille, void* element);

#endif //TP1_UTILS_H

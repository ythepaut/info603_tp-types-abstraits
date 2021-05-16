/**
 * INFO603 TP Exercice 1
 * Lucas CHARDONNET - Yohann THEPAUT
 *
 * Sémentique axiomatique de la procédure partition
 */

#include <stdlib.h>
#include <assert.h>
#include "utils.h"
#include "partition.h"

/**
 * Trouve la valeur médiane
 * @param a             in              int             a
 * @param b             in              int             b
 * @param c             in              int             c
 * @return                                              Valeur médiane entre a, b et c
 */
int* median(int* a, int* b, int* c) {
    int* max1 = max(a, b);
    int* max2 = max(b, c);
    if (*max1 == *max2)
        max2 = max(a, c);
    return min(max1, max2);
}

/**
 * Procédure partition du tri rapide
 * @param tab           in-out          int*            Pointeur sur le premier element
 *                                                      du tableau d'entiers
 * @param i             in              int             Indice de la borne inférieur
 * @param j             in              int             Indice de la borne supérieur
 * @param k             out             int*            Pivot
 */
void partition(int* tab, int i, int j, int* k) {

    int l;

    permuter(&tab[i], median(&tab[i], &tab[j], &tab[(i + j) / 2]));
    l = i + 1;
    *k = j;

    // (temporaire) variables utilisées pour l'assertion 6
    int pivot = tab[i];
    printf("Pivot : %d\n", pivot);

    assert(&tab[i] == median(&tab[i], &tab[j], &tab[(i + j) / 2])); // (1)

    while (l <= *k) {
        while (tab[*k] > tab[i] && l <= *k) {
            assert(assertion2(tab, *k, j, i)); // (2)
            --(*k);
        }

        while (tab[l] <= tab[i] && l <= *k) {
            assert(assertion3(tab, i, l)); // (3)
            ++l;
        }

        if (l < *k) {
            permuter(&tab[l], &tab[*k]);
            ++l;
            --(*k);
        }

        assert(assertion2(tab, *k+1, j, i) && assertion3(tab, i, l-1) && assertion4(tab, l, *k)); // (4)
    }

    assert(assertion2(tab, *k+1, j, i) && assertion3(tab, i, l-1) && assertion4(tab, l, *k) && l > *k); // (5)

    permuter(&tab[i], &tab[*k]);

    assert(assertion6(tab, i, j, pivot, *k)); // (6)
}

/**
 * ∀x, k ≤ x ≤ j, t[x] > t[i]
 */
int assertion2(int* tab, int k, int j, int i) {
    for (int x = k ; x <= j ; ++x)
        if (!(tab[x] > tab[i]))
            return 0;
    return 1;
}

/**
 * ∀y, i ≤ y ≤ l, t[y] ≤ t[i]
 */
int assertion3(int* tab, int i, int l) {
    for (int y = i ; y <= l ; ++y)
        if (!(tab[y] <= tab[i]))
            return 0;
    return 1;
}

/**
 * l < k ⇒ t[l-1] ≤ t[k+1]
 */
int assertion4(int* tab, int l, int k) {
    if (l < k)
        return tab[l-1] <= tab[k+1];
    return 1;
}

/**
 * (∀x, i ≤ x ≤ positionPivot, t[x] ≤ t[pivot]) ∧ (∀y, positionPivot < y ≤ j, t[y] ≥ t[pivot])
 */
int assertion6(int* tab, int i, int j, int pivot, int positionPivot) {
    for (int x = i ; x <= positionPivot ; ++x)
        if (!(tab[x] <= pivot))
            return 0;
    for (int y = positionPivot+1 ; y <= j ; ++y)
        if (!(tab[y] >= pivot))
            return 0;
    return 1;
}


int main(int argc, char *argv[]) {
    const int TAILLE_TABLEAU = argc > 1 ? atoi(argv[1]) : 10;

    int* tab = malloc(sizeof(int) * TAILLE_TABLEAU);
    tableauAleatoire(tab, TAILLE_TABLEAU, 100);

    printf("Tableau initial :   \t\t");
    afficheTableau(tab, TAILLE_TABLEAU);

    int k;
    partition(tab, 0, TAILLE_TABLEAU - 1, &k);

    printf("Tableau après partition :\t");
    afficheTableau(tab, TAILLE_TABLEAU);

    free(tab);

    return EXIT_SUCCESS;
}

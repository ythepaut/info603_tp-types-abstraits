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

    printf("pivot=%d\n", tab[i]); //TODO remove print
    afficheTableau(tab, j);

    assert(1); // (1)

    while (l <= *k) {
        while (tab[*k] > tab[i] && l <= *k) {
            assert(1); // (2)
            --(*k);
        }

        while (tab[l] <= tab[i] && l <= *k) {
            assert(1); // (3)
            ++l;
        }

        if (l < *k) {
            permuter(&tab[l], &tab[*k]);
            ++l;
            --(*k);
        }

        assert(1); // (4)
    }

    assert(1); // (5)

    permuter(&tab[i], &tab[*k]);

    assert(1); // (6)
}


int main(int argc, char *argv[]) {
    const int TAILLE_TABLEAU = argc > 1 ? atoi(argv[1]) : 10;

    int* tab = malloc(sizeof(int) * TAILLE_TABLEAU);
    tableauAleatoire(tab, TAILLE_TABLEAU, 100);

    printf("Tableau initial :\t\t");
    afficheTableau(tab, TAILLE_TABLEAU);

    int k;
    partition(tab, 0, TAILLE_TABLEAU - 1, &k);

    printf("Tableau après partition :\t");
    afficheTableau(tab, TAILLE_TABLEAU);

    free(tab);

    return EXIT_SUCCESS;
}

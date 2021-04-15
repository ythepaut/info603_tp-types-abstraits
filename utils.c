/**
 * INFO603 TP
 * Lucas CHARDONNET - Yohann THEPAUT
 *
 * Fonctions utiles communes aux exercices
 */

#include <stdlib.h>
#include <unistd.h>
#include "utils.h"


/**
 * Échange le contenu de deux entiers
 * @param a             in-out          int*            Pointeur sur l'entier à échanger avec b
 * @param b             in-out          int*            Pointeur sur l'entier à échanger avec a
 */
void permuter(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Trouve le maximum entre a et b
 * @param a             in              int*            a
 * @param b             in              int*            b
 * @return                                              Le maximum entre a et b
 */
int* max(int* a, int* b) {
    return *a > *b ? a : b;
}

/**
 * Trouve le minimum entre a et b
 * @param a             in              int*            a
 * @param b             in              int*            b
 * @return                                              Le minimum entre a et b
 */
int* min(int* a, int* b) {
    return *a < *b ? a : b;
}

/**
 * Affiche le tableau
 * @param tab           in-out          int*            Pointeur sur le premier element
 *                                                      du tableau d'entiers
 * @param n             in              int             Taille du tableau
 */
void afficheTableau(int* tab, int n) {
    printf("[");
    for (int i = 0 ; i < n - 1 ; ++i)
        printf("%d, ", tab[i]);
    printf("%d]\n", tab[n - 1]);
}

/**
 * Crée un tableau d'entiers avec des valeurs aléatoires
 * @param tab           out             int*            Pointeur sur le premier element
 *                                                      du tableau d'entiers
 * @param n             in              int             Taille du tableau
 * @param max           in              int             Borne max des nombres dans le tableau
 */
void tableauAleatoire(int* tab, int n, int max) {
    srand(getpid());

    for (int i = 0 ; i < n ; ++i) {
        tab[i] = rand() % max;
    }
}

/**
 * Retourne le plus petit élément du tableau dans l'intervalle donnée.
 * @param tab           in          int*            tableau d'entier
 * @param n             in          int             taille du tableau
 * @param indexDebut    in          int             borne minimale du parcours
 * @param indexFin      in          int             borne maximale du parcours
 * @return                                          le plus petit élément trouvé
 */
int plusPetitElement(int* tab, int n, int indexDebut, int indexFin) {
    int plusPetitElement = tab[indexDebut];
    for (int i = indexDebut; i <= indexFin; i++)
        if (tab[i] < plusPetitElement)
            plusPetitElement = tab[i];
    return plusPetitElement;
}

/**
 * Retourne le plus grand élément du tableau dans l'intervalle donnée.
 * @param tab           in          int*            tableau d'entier
 * @param n             in          int             taille du tableau
 * @param indexDebut    in          int             borne minimale du parcours
 * @param indexFin      in          int             borne maximale du parcours
 * @return                                          le plus grand élément trouvé
 */
int plusGrandElement(int* tab, int n, int indexDebut, int indexFin) {
    int plusGrandElement = tab[indexDebut];
    for (int i = indexDebut; i <= indexFin; i++)
        if (tab[i] > plusGrandElement)
            plusGrandElement = tab[i];
    return plusGrandElement;
}

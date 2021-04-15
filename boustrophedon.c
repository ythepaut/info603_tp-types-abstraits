/**
 * INFO603 TP Exercice 2
 * Lucas CHARDONNET - Yohann THEPAUT
 *
 * Tri Boustrophédon
 */

#include <stdlib.h>
#include <assert.h>

#include "boustrophedon.h"
#include "utils.h"

/**
 * Parcours le tableau passé en argument à partir de l'index de début jusqu'à l'index de fin.
 * Le sens du parcours est déterminé par les valeurs de l'index de début et de fin.
 * Si le tableau est parcouru dans un sens ascendant, si l'élément courant
 * est plus grand que le suivant, on les permute.
 * Si le tableau est parcouru dans un sens descendant, si l'élément courant
 * est plus petit que le suivant, on les permute.
 * @param t             in-out      int*        tableau à parcourir
 * @param n             in          int         taille du tableau
 * @param indiceDebut    in          int         index de début de parcours
 * @param indiceFin      in          int         index de fin de parcours
 */
void iterationBoustrophedon(int *t, int n, int indiceDebut, int indiceFin) {

    assert(0 <= indiceDebut && indiceDebut < n);

    if (indiceDebut < indiceFin) {
        for (int i = indiceDebut; i <= indiceFin; i++) {
            assert(t[i] <= plusGrandElement(t, n, 0, n));
            if (t[i] > t[i + 1]) {
                permuter(&t[i], &t[i + 1]);
            }
        }
        assert(t[indiceFin] == plusGrandElement(t, n, indiceDebut, indiceFin));
    }

    else if (indiceDebut > indiceFin) {
        for (int i = indiceDebut; i >= indiceFin; i--) {
            assert(t[i] >= plusPetitElement(t, n, indiceFin, n));
            if (t[i] < t[i - 1]) {
                permuter(&t[i], &t[i - 1]);
            }
        }
        // ici on cherche le plus petit élément depuis l'indice de fin jusqu'à celui du début
        // car l'indice de fin est plus petit que celui du début.
        assert(t[indiceFin] == plusPetitElement(t, n, indiceFin, indiceDebut));
    }
}

/**
 * Parcours le tableau t en le balayant de gauche puis à droite à chaque itération.
 * Une itération de gauche à droite amène l'élément rencontré le plus grand
 * à l'index de fin en partant de l'index de début.
 * Une itération de droite droite gauche amène l'élément rencontré le plus petit
 * à l'index de fin en partant de l'index de début.
 * @param t         in-out      int*        tableau à trier
 * @param n         in          int         taille du tableau
 */
void boustrophedon(int* t, int n) {
    for (int k = 0; k < n / 2; k++) {
        iterationBoustrophedon(t, n, k, n - k - 1);
        iterationBoustrophedon(t, n, n - k - 2, k);
    }
}

int main(int argc, char *argv[]) {
    const int TAILLE_TABLEAU = argc > 1 ? atoi(argv[1]) : 10;

    int* tab = malloc(sizeof(int) * TAILLE_TABLEAU);
    tableauAleatoire(tab, TAILLE_TABLEAU, 200);

    printf("Tableau initial :\t");
    afficheTableau(tab, TAILLE_TABLEAU);

    boustrophedon(tab, TAILLE_TABLEAU);

    printf("Tableau après tri :\t");
    afficheTableau(tab, TAILLE_TABLEAU);

    free(tab);
    return EXIT_SUCCESS;
}

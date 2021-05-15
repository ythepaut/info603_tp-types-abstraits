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
 * Parcours le tableau passé en argument à partir de l'index de début jusqu'à l'indexDe de fin.
 * Le sens du parcours est déterminé par les valeurs de l'indexDe de début et de fin.
 * Si le tableau est parcouru dans un sens ascendant, si l'élément courant
 * est plus grand que le suivant, on les permute.
 * Si le tableau est parcouru dans un sens descendant, si l'élément courant
 * est plus petit que le suivant, on les permute.
 * @param t             in-out      int*        tableau à parcourir
 * @param n             in          int         taille du tableau
 * @param indiceDebut    in          int         indexDe de début de parcours
 * @param indiceFin      in          int         indexDe de fin de parcours
 */
void iterationBoustrophedon(int *t, int n, int indiceDebut, int indiceFin) {
    assert(0 <= indiceDebut && indiceDebut < n);

    // trie à partir de la gauche
    if (indiceDebut < indiceFin) {
        for (int i = indiceDebut; i <= indiceFin; i++) {

            // l'élément courant ne peut pas être plus grand
            // que le plus grand élément de la partie du tableau
            // en train d'être triée
            assert(t[i] <= plusGrandElement(t, i, n));

            if (t[i] > t[i + 1]) {
                permuter(&t[i], &t[i + 1]);
            }

            // l'élément permuté est forcément plus petit que
            // n'importe quel élément de la partie de droite
            assert(t[i] <= plusGrandElement(t, i, n));
        }
        // le dernier élément permuté est forcément
        // le plus grand élément de la partie qui vient d'être triée
        assert(t[indiceFin] == plusGrandElement(t, indiceDebut, indiceFin));
    }

    // trie à partir de la droite
    else if (indiceDebut > indiceFin) {
        for (int i = indiceDebut; i >= indiceFin; i--) {

            // l'élément courant ne peut pas être plus petit
            // que le plus petit élément de la partie du tableau
            // en train d'être triée
            assert(t[i] >= plusPetitElement(t, indiceFin, i));

            if (t[i] < t[i - 1]) {
                permuter(&t[i], &t[i - 1]);
            }

            // l'élément permuté est forcément plus grand que
            // n'importe quel élément de la partie de gauche
            assert(t[i] >= plusPetitElement(t, 0, i));
        }
        // le dernier élément permuté est forcément
        // le plus petit élément de la partie qui vient d'être triée
        assert(t[indiceFin] == plusPetitElement(t, indiceFin, indiceDebut));
    }
}

/**
 * Parcours le tableau t en le balayant de gauche puis à droite à chaque itération.
 * Une itération de gauche à droite amène l'élément rencontré le plus grand
 * à l'index de fin en partant de l'indexDe de début.
 * Une itération de droite droite gauche amène l'élément rencontré le plus petit
 * à l'index de fin en partant de l'indexDe de début.
 * @param t         in-out      int*        tableau à trier
 * @param n         in          int         taille du tableau
 */
void boustrophedon(int* t, int n) {
    for (int k = 0; k < n / 2; k++) {

        assert(estTrie(t, 0, k)); // vérifie que la partie gauche passée est triée
        iterationBoustrophedon(t, n, k, n - k - 1);

        assert(estTrie(t, n - k - 2, n)); // vérifie que la partie droite passée est triée
        iterationBoustrophedon(t, n, n - k - 2, k);
    }
    // tout le tableau est trié
    assert(estTrie(t, 0, n));
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

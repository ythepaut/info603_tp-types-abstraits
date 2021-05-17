INFO603 TP rapport<br/>
Lucas CHARDONNET - Yohann THEPAUT

# **1. Sémantique axiomatique de la procédure partition**

**(1)** t[i] = median(t[i], [j], t[(i + j) / 2])

L'élément au début du tableau (pivot) est l'élément médian entre t[i], t[(i+j) / 2] et t[j].

**(2)** $\forall$x, k $\leq$ x $\leq$ j, t[x] $\gt$ t[i]

Les éléments à la fin du tableau sont plus grands que le pivot.

**(3)** $\forall$y, i $\leq$ y $\leq$ l, t[y] $\leq$ t[i]

Les éléments au début du tableau sont plus petits que le pivot.

**(4)** ($\forall$x, k+1 $\leq$ x $\leq$ j, t[x] $\gt$ t[i]) $\land$ ($\forall$y, i $\leq$ y $\leq$ l-1, t[y] $\leq$ t[i]) $\land$ ($l < k \Rightarrow$( t[l-1] $\leq$ t[k+1] ))

Les éléments d'indice k à j sont plus grands que le pivot, et les éléments d'indice i+1 à l sont plus petits que le pivot.

**(5)** ($\forall$x, k $\leq$ x $\leq$ j, t[x] $\gt$ t[i]) $\land$ ($\forall$y, i $\leq$ y $\leq$ l, t[y] $\leq$ t[i]) $\land$ ($l < k \Rightarrow$( t[l-1] $\leq$ t[k+1] )) $\land$ (l $\gt$ k)

Les éléments d'indice k à j sont plus grands que le pivot, et les éléments d'indice i+1 à l sont plus petits que le pivot et l > k

**(6)** ($\forall$x, i $\leq$ x $\leq$ position_pivot, t[x] $\leq$ t[pivot]) $\land$ ($\forall$y, position_pivot $\lt$ y $\leq$ j, t[y] $\geq$ t[pivot])

Tous les éléments plus petit que le pivot sont à gauche du pivot, et tous les éléments plus grand que le pivot sont à droite du pivot.

# **2. Le tri Boustrophédon**

L'implémentation faite ici repose sur une fonction _itération_ qui est répétée plusieurs fois.<br/>
Une itération consiste en un parcourt du tableau, à partir d'un indice de début, jusqu'à un indice de fin.
À chaque étapes, l'élément courant et l'élément suivant sont inversé si l'élément avec l'index le plus bas est plus grand que l'élément avec l'index le plus petit.

```
itération(in_out t : tableau[1..n] de entier; in n : entier; in indice_début : entier, in indice_fin : entier );
```

On a donc la fonction principale _boustrophédon_ suivante.<br/>
Les numéros commentés correspondent à des numéros d'assertions.<br/>
On décrit les assersions à la suite, avec la fonction _est\_trié_ qui vérifie si une portion donnée du tableau est triée.

```
procédure boustrophédon(in_out t : tableau[1..n] de entier, in n);
var
    k = 1;
début
    tantque k < n / 2 faire
        // (1)
        itération(t, n, k, n-k);
        // (1.1)
        // (2)
        itération(t, n, n-k-1, k);
        // (2.1)
        k := k + 1;
    fin tantque;
    // (3)
fin;
```

(1) est_trié(t, 1, k)<br/>
(1.1) t[k + 1] >= t[k..n-k]<br/>
(2) est_trié(t, n-k-1, n)<br/>
(2.1) t[k] >= t[n-k-1..k]<br/>
(3) est trié(t, 1, n)<br/>

<br/>

Le corps de la fonction d'itération serait alors écrit de la sorte.<br/>
Les assertions comportent les fonctions plus_grand_élément(t, a, b) et plus_petit_élément(t, a, b), qui retournent l'élément indiqué dans le tableau t dans l'intervale d'indexes a et b.

```
procédure itération(in_out t : tableau[1..n] de entier; in n : entier; in indice_début : entier, in indice_fin : entier );
var
    i := indice_début;
début
    
    // (0)

    si indice_début < indice_fin alors
        tantque i <= indice_fin faire

            // (1)

            si t[i] > t[i + 1] alors
                permuter(t[i], t[i + 1]);
            finsi;

            // (2)

            i := i + 1;
        fin tantque;

        // (3)

    sinon si indice_début > indice_fin alors
        tantque i >= indice_fin faire

            // (4)

            si t[i] < t[i - 1] alors
                permuter(t[i], t[i - 1]);
            finsi;

            // (5)

            i := i - 1;
        fin tantque;

        // (6)

    finsi;
fin;
```

(0) 0 <= indice_debut $\wedge$ indiceDebut < n<br/>
(1) t[i] $\le$ plus_grand_élément(t, i, n)<br/>
(2) t[i] $\le$ plus_grand_élément(t, i, n)<br/>
(3) t[indice_fin] = plus_grand_élément(t, indice_debut, indice_fin)<br/>
(4) t[i] $\ge$ plus_petit_élément(t, indice_fin, i)<br/>
(5) t[i] $\ge$ plus_petit_élément(t, 0, i)<br/>
(6) t[indice_fin] = plus_petit_élément(t, indice_fin, indice_debut)<br/>

<br/>
Le code source est disponible dans boustrophedon.c.<br/>
Le code est commenté pour expliquer les assertions, et à la différence de ci-dessus, les tableaux sont indexés en 0.<br/>
<br/>

# **3. Implémentation du type abstrat graphe**

# 3.1 Type graphe

## Graphe

__Sorte__ : graphe ;

__utilise__ : entier, noeud ;

__Opérations__<br/>
creerGraphe : tableau de tableau de entier * entier $\to$ graphe ;<br/>
ordre : graphe $\to$ entier ;<br/>
detruireGraphe : graphe $\to\ \perp$ ;<br/>
afficheGraphe : graphe $\to\ \perp$ ;<br/>
getNoeud : graphe * entier $\to$ noeud ;<br/>
indiceNoeud : graphe * noeud $\to$ entier ;<br/>
noeudNonParcouru : graphe * tableau de entier $\to$ entier ;<br/>
poidsEntreNoeuds : graphe * noeud * noeud $\to$ entier ;<br/>
noeudDePlusPetitPoidsHorsDeSousGraphe : graphe * tableau de entier * tableau de entier $\to$ entier ;<br/>
dijkstra : graphe * noeud $\to\ \perp$ ;<br/>

__avec__<br/>
x : entier ;<br/>
n : noeud ;<br/>
g : graphe ;<br/>

__préconditions__<br/>
getNoeud(g, x) _est-définie-ssi_ 0 $\le$ x $\le$ ordre(g) ;<br/>

<br/>

# 3.3 Implémentations différentes

Pour la première représentation de données, nous avons utilisé les définitions de structure du langage C.
Une structure noeud, une structure arête, et une structure graphe.<br/>
La structure noeud possède un numéro qui lui est propre, et un ensemble d'arêtes qui sont ses arêtes adjacentes.<br/>
La structure arête possède strictement deux noeuds, ainsi qu'un entier représentant son poid.<br/>
La structure graphe possède quant à elle un ensemble de noeuds, et un entier représentant son ordre.<br/>
<br/>
Dans la seconde implémentation, un graphe est représenté par un matrice d'adjacence. Avec m comme matrice, l'arrête reliant i et j auraient comme poids m[i][j].
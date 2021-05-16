# **1. Sémantique axiomatique de la procédure partition**

**Invariants de boucle :**

**(1)** 

**(2)**

**(3)**

**(4)**

**(5)**

**(6)**

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
        // (2)
        itération(t, n, n-k-1, k);
        k := k + 1;
    fin tantque;
    // (3)
fin;
```

(1) est_trié(t, 1, k)<br/>
(2) est_trié(t, n-k-1, n)<br/>
(3) est trié(t, 1, n)<br/>

<br/>

Le corps de la fonction d'itération serait alors écrit de la sorte.<br/>
Les assertions comportent les fonctions plus_grand_element(t, a, b) et plus_petit_element(t, a, b), qui retournent l'élément indiqué dans le tableau t dans l'intervale d'indexes a et b.

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
(1) t[i] $\le$ plus_grand_element(t, i, n)<br/>
(2) t[i] $\le$ plus_grand_element(t, i, n)<br/>
(3) t[indice_fin] = plus_grand_element(t, indice_debut, indice_fin)<br/>
(4) t[i] $\ge$ plus_petit_element(t, indice_fin, i)<br/>
(5) t[i] $\ge$ plus_petit_element(t, 0, i)<br/>
(6) t[indice_fin] = plus_petit_element(t, indice_fin, indice_debut)<br/>

<br/>
Le code source est disponible dans boustrophedon.c.<br/>
Le code est commenté pour expliquer les assertions, et à la différence de ci-dessus, les tableaux sont indexés en 0.<br/>
<br/>

# **3. Implémentation du type abstrat graphe**

# 3.1 Type graphe

## Noeud

__Sorte__ : noeud ;

__utilise__ : entier, arête ;

__Opérations__

créer_noeud : entier * tableau de arête * entier $\to$ noeud ;<br/>
numéro : noeud $\to$ entier ;<br/>
arêtes : noeud $\to$ tableau de arête ;<br/>
nombre_arêtes : noeud $\to$ entier ;<br/>

__avec__<br/>
n : noeud ;<br/>
ta : tableau de arête ;<br/>
a : entier ;<br/>

__précondition__<br/>
créer_noeud(n, ta, a) _est-définie-ssi_ <br/> a = 2 $\wedge$ ( $\forall$ x, 0 < x < a, noeudA( ta[a] ) = n $\vee$ noeudB( ta[a] ) = n ) ;<br/>

<br/>

## Arête

__Sorte__ : arête ;

__utilise__ : entier, noeud ;

__Opérations__<br/>
créer_arête : noeud * noeud * entier $\to$ arête ;<br/>
noeudA : arête $\to$ noeud\ ;<br/>
noeudB : arête $\to$ noeud ;<br/>
poids : arête $\to$ entier ;<br/>

<br/>

## Graphe

__Sorte__ : graphe ;

__utilise__ : entier, noeud, arête ;

__Opérations__<br/>
créer_graphe : tableau de tableau de entier * entier $\to$ graphe ;<br/>
détruire_graphe : graphe $\to\ \perp$ ;<br/>
ordre : graphe $\to$ entier ;<br/>
ajoute_arête : graphe * noeud * arete $\to\ \perp$ ;<br/>
dijkstra : graphe * noeud * noeud $\to\ \perp$ ;<br/>
affiche_graphe : graphe $\to\ \perp$ ;<br/>

__avec__<br/>
n : noeud ;<br/>
a : arête ;<br/>
g : graphe ;<br/>

__précondition__<br/>
ajoute_arête(n, a) est-définie-ssi noeudA(a) = n $\vee$ noeudB(a) = n ;<br/>
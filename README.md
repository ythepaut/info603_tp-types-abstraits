# Noeud

<ins>Sorte</ins> : $noeud\ ;$<br/>
<ins>utilise</ins> : $entier,\ arête\ ;$

<ins>Opérations</ins><br/>
$créer\_noeud : entier * tableau\ de\ arête * entier \to noeud\ ;$<br/>
$numéro : noeud \to entier\ ;$<br/>
$arêtes : noeud \to tableau\ de\ arête\ ;$<br/>
$nombre\_arêtes : noeud \to entier\ ;$<br/>

<ins>avec</ins><br/>
$n : noeud\ ;$<br/>
$a : arête\ ;$<br/>

<ins>précondition</ins><br/>
$créer\_noeud(n, ta, a)$ est-définie-ssi $a = 2 \vee noeudB(a) = n\ ;$<br/>

<br/>

# Arête

<ins>Sorte</ins> : $arête\ ;$<br/>
<ins>utilise</ins> : $entier,\ noeud\ ;$

<ins>Opérations</ins><br/>
$créer\_arête : noeud * noeud * entier \to arête\ ;$<br/>
$noeudA : arête \to noeud\ ;$<br/>
$noeudB : arête \to noeud\ ;$<br/>
$poids : arête \to entier\ ;$<br/>

<br/>

# Graphe

<ins>Sorte</ins> : $graphe\ ;$<br/>
<ins>utilise</ins> : $entier,\ noeud,\ arête\ ;$

<ins>Opérations</ins><br/>
$créer\_graphe : entier * entier * entier \to graphe\ ;$<br/>
$détruire\_graphe : graphe \to \perp\ ;$<br/>
$ordre : graphe \to entier\ ;$<br/>
$ajoute\_arête : graphe * noeud * arete \to \perp\ ;$<br/>
$dijkstra : graphe * noeud * noeud \to \perp\ ;$<br/>
$affiche\_graphe : graphe \to \perp\ ;$<br/>

<ins>avec</ins><br/>
$n : noeud\ ;$<br/>
$a : arête\ ;$<br/>
$g : graphe\ ;$<br/>

<ins>précondition</ins><br/>
$ajoute\_arête(n, a)$ est-définie-ssi $noeudA(a) = n \vee noeudB(a) = n\ ;$<br/>
# Travail pratique 3

## Description

Ce programme permet de générer aléatoirement des labyrinthes sur une grille
carrée.

## Auteur

Alexandre Blondin Massé

## Installation

Actuellement, l'installation se fait uniquement à partir du code source. Il
suffit de cloner le projet, et ensuite de taper

~~~
make
~~~

L'exécutable se trouve dans le répertoire `bin`. Il suffit ensuite d'entrer
`bin/tp3 --help` pour afficher l'aide du programme.

## Fonctionnement

Pour lancer le programme, il suffit d'entrer `bin/tp3`, qui affiche par défaut
un labyrinthe de dimensions 5 par 5 sur `stdout` :

~~~
+-+-+-+-+-+
|         |
+ + +-+-+ +
| |   | | |
+ +-+-+ + +
| |   | | |
+ + + + + +
|   |   | |
+-+ + +-+ +
|   | |   |
+-+-+-+-+-+
~~~

Différentes options sont disponibles (voir `bin/tp3 --help` pour plus de
détails). Par exemple, on peut modifier le nombre de rangées et de colonnes :

~~~
$ bin/tp3 --num-rows 2 --num-cols 2
 +-+-+
 |   |
 + + +
 | | |
 +-+-+
~~~

Il est également possible de produire une image au format PNG. Par exemple, la
commande

~~~
$ bin/tp3 --num-rows 4 --num-cols 7 --output-format png --output-filename maze.png
~~~

produit un fichier `maze.png`, qui devrait ressembler à

![](images/maze.png)

## Plateformes supportées

Testé sur MacOS 10.10.5 Yosemite.

## Dépendances

- [Cairo](http://cairo.org/), une bibliothèque permettant de générer des images
  au format PNG. Cette bibliothèque doit être installée sur le système pour que
  le projet fonctionne.
- [CUnit](http://cunit.sourceforge.net/), pour les tests unitaires. Cette
  bibliothèque doit être installée sur le système pour que la commande `make
  test` fonctionne correctement.

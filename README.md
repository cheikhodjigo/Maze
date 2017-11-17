# Travail pratique 2

## Description

Ce programme permet de générer aléatoirement des labyrinthes sur une grille
carrée. Une fois compilé, l'exécutable principal est ``bin/tp2``. Un aperçu des
options disponibles peut être obtenu comme suit :

~~~sh
Usage: bin/tp2 [--help] [--num-rows VALUE] [--num-cols VALUE] [--start R,C]
    [--end R,C] [--with-solution] [--walls-color VALUE]
    [--output-format STRING] [--output-filename FILENAME]

Generates a random maze on the square grid.

Optional arguments:
  --help                   Shows this help message and exit
  --num-rows VALUE         The number of rows in the maze.
                           The default value is 5.
  --num-cols VALUE         The number of columns in the maze.
                           The default value is 5.
  --start R,C              The coordinates of the start room.
                           The default value is top left corner.
  --end R,C                The coordinates of the end room.
                           The default value is bottom right corner.
  --with-solution          Also displays solution in the maze.
  --walls-color VALUE      The color of the walls in the maze (e.g. "navy").
                           The name must be one of the 16 basic HTML colors.
                           Defaults to "black". The option is ignored if the
                           ouput format is "text".
  --output-format STRING   Selects the ouput format (either "text" or "png").
                           The default format is "text".
  --output-filename STRING The name of the output file.
                           Mandatory for png format.
                           If not specified, displays on stdout.
~~~

## Auteur

Alexandre Blondin Massé

## Installation

Actuellement, l'installation se fait uniquement à partir du code source. Dans
un premier temps, il faut installer un certain nombre de logiciels et de
bibliothèques (voir la section [Dépendances](#dependances)). Ensuite, il suffit
de cloner le projet et d'entrer la commande

~~~
make
~~~

L'exécutable se trouve dans le répertoire `bin`. Il suffit ensuite d'entrer
`bin/tp2 --help` pour afficher l'aide du programme.

## Fonctionnement

Par défaut, la commande `bin/tp2` affiche un labyrinthe de dimensions 5 par 5
sur `stdout` :

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

Différentes options sont disponibles (voir `bin/tp2 --help` pour plus de
détails). Par exemple, on peut modifier le nombre de rangées et de colonnes :

~~~
$ bin/tp2 --num-rows 2 --num-cols 2
+-+-+
|   |
+ + +
| | |
+-+-+
~~~

Il est également possible d'afficher la solution du labyrinthe, en supposant
qu'on commence en haut à gauche et qu'on termine en bas à droite :

~~~
$ bin/tp2 --num-rows 6 --num-cols 8 --with-solution
+-+-+-+-+-+-+-+-+
|X|XXXXXXXXXXXXX|
+X+X+-+-+ +-+-+X+
|XXX  |   |   |X|
+ +-+-+-+-+-+ +X+
|     | |      X|
+-+ + + +-+-+-+X+
| | |   |   |  X|
+ + + +-+-+ +-+X+
|   |     |    X|
+ +-+ + +-+ + +X+
| |   | |   | |X|
+-+-+-+-+-+-+-+-+
~~~
Il est possible de produire un graphe non oriente qui sera en format dot et  
représentant le labyrinthe. À l'aide de ce format on  peut produire une image 
en format png nomme maze.png. Ce fichier est produit à l'aide de la bibliothèque
[Graphviz](http://www.graphviz.org/). Ainsi la commande:

~~~
$ bin/tp2 --num-rows 2 --num-cols 3 --output-format dot
~~~
produit le résultat suivant :
~~~
strict graph {
node [shape=box];
"(0,0)" [label="0,0", pos="0,0!"];
"(0,1)" [label="0,1", pos="1,0!"];
"(0,2)" [label="0,2", pos="2,0!"];
"(1,0)" [label="1,0", pos="0,-1!"];
"(1,1)" [label="1,1", pos="1,-1!"];
"(1,2)" [label="1,2", pos="2,-1!"];
"(0,2)" -- "(0,1)";
"(1,0)" -- "(0,0)";
"(1,1)" -- "(0,1)";
"(1,1)" -- "(1,0)";
"(1,2)" -- "(1,1)";
}

~~~ 
et la commande :


~~~
$ bin/tp2 --num-rows 2 --num-cols 3 --output-format dot | neato -Tpng -o maze.png
~~~

produit un fichier png nommé maze.png qui est en réalité la représentation graphique
de ce labyrinthe.
De la même manière on peut aussi produire: d'abord le format dot d'un labyrinthe avec une
solution puis son format png. Cela se fait avec les commandes suivantes qui sont chacunes
accompagnés de leurs résultats.

~~~
bin/tp2 --num-rows 2 --num-cols 3 --output-format dot --with-solution
~~~
strict graph {
node [shape=box];
"(0,0)" [label="0,0", pos="0,0!"];
"(0,1)" [label="0,1", pos="1,0!"];
"(0,2)" [label="0,2", pos="2,0!"];
"(1,0)" [label="1,0", pos="0,-1!"];
"(1,1)" [label="1,1", pos="1,-1!"];
"(1,2)" [label="1,2", pos="2,-1!"];
"(0,1)" -- "(0,0)";
"(1,1)" -- "(0,1)";
"(1,1)" -- "(1,0)";
"(1,2)" -- "(0,2)";
"(1,2)" -- "(1,1)";
"(0,0)" [style=filled, fillcolor=azure, color=blue, penwidth=3];
"(0,1)" [style=filled, fillcolor=azure, color=blue, penwidth=3];
"(0,0)" -- "(0,1)" [penwidth=3, color=blue];
"(1,1)" [style=filled, fillcolor=azure, color=blue, penwidth=3];
"(0,1)" -- "(1,1)" [penwidth=3, color=blue];
"(1,2)" [style=filled, fillcolor=azure, color=blue, penwidth=3];
"(1,1)" -- "(1,2)" [penwidth=3, color=blue];
}

~~~
$ bin/tp2 --num-rows 2 --num-cols 3 --output-format dot --with-solution | neato -Tpng -o maze.png
~~~

Cela produit une image en format png nommé maze.png et qui mets en évidence la solution du 
labyrinthe.

Finalement, il est également possible de produire une image au format PNG,
grâce à la bibliothèque [Cairo](http://cairo.org/). Par exemple, la commande

~~~
$ bin/tp2 --num-rows 4 --num-cols 7 --output-format png --output-filename maze.png
~~~

produit un fichier `maze.png`, qui devrait ressembler à

![](images/maze.png)

## Plateformes supportées

Testé sur MacOS 10.10.5 Yosemite, sur malt.labunix.uqam.ca et sur
java.labunix.uqam.ca.

## Dépendances

- [Cairo](http://cairographics.org/), une bibliothèque permettant de générer des images
  au format PNG. Cette bibliothèque doit être installée sur le système pour que
  le projet fonctionne.
- [Bats](https://github.com/sstephenson/bats), pour les tests unitaires en
  boîte noire. Ce logiciel permet d'écrire des petits tests en Bash pour
  s'assurer que le programme a le comportement souhaité.
- [Graphviz](http://www.graphviz.org/), un logiciel pour visualiser des graphiques. Il
  permet de représenter des informations, qui initialement été sous formes de fichier
  text, en graphique. Ce dernier utilise le format dot dont la documentation peut être 
  trouver sur internet, afin de faire cette représentation graphique.
- [PKG-config](https://www.freedesktop.org/wiki/Software/pkg-config/), un
  logiciel facilitant la compilation et l'édition des liens lorsqu'on utilise
  des bibliothèques tierces.
- [CUnit](http://cunit.sourceforge.net/), pour les tests unitaires. Cette
  bibliothèque doit être installée pour que la commande `make test` fonctionne
  correctement.

## License

Le contenu de ce projet est sous [licence GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html).

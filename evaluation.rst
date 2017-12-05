Correction du TP2
~~~~~~~~~~~~~~~~~

Grille de points
================

+--------------------+----------------------------------------+--------+---------+
| Tâche              | Critères                               | Note   | Sur     |
+====================+========================================+========+=========+
|                    |                                        |        |         |
|                    | - Utilisation correcte de Git          |        |         |
|                    | - Qualité des *docstrings*             |        |         |
| Tâche 1            | - Qualité de la requête d'intégration  | 17     | 20      |
|                    | - Qualité du changement de code        |        |         |
|                    | - Tests automatisés                    |        |         |
|                    |                                        |        |         |
+--------------------+----------------------------------------+--------+---------+
|                    |                                        |        |         |
|                    | - Utilisation correcte de Git          |        |         |
|                    | - Qualité des *docstrings*             |        |         |
| Tâche 2            | - Qualité de la requête d'intégration  | 26     | 30      |
|                    | - Qualité du changement de code        |        |         |
|                    | - Tests automatisés                    |        |         |
|                    |                                        |        |         |
+--------------------+----------------------------------------+--------+---------+
|                    |                                        |        |         |
|                    | - Utilisation correcte de Git          |        |         |
|                    | - Qualité des *docstrings*             |        |         |
| Tâche 3            | - Qualité de la requête d'intégration  | 44     | 50      |
|                    | - Qualité du changement de code        |        |         |
|                    | - Tests automatisés                    |        |         |
|                    |                                        |        |         |
+--------------------+----------------------------------------+--------+---------+
| **Total**                                                   | **87** | **100** |
+--------------------+----------------------------------------+--------+---------+

Commentaires
============

Généraux
--------

- Excellente utilisation de Git;
- Messages de *commit* impeccables et fidèles au format demandé;
- La topologie demandée est respectée;
- Les requêtes d'intégration sont descriptives. Elles pourraient cependant
  mieux exploiter le format Markdown, notamment les bouts de code. Aussi,
  il faut mettre des exemples (c'est une des parties les plus importantes) qui
  illustrent le comportement avant/après du programme. Voir `la tâche 0
  <https://gitlab.com/ablondin/inf3135-aut2017-tp2/merge_requests/1>`__ pour un
  exemple de requête d'intégration de bonne qualité.
- Attention aux espaces superflues dans le code modifié (on les voit en rouge
  quand on fait ``git diff``);

Tâche 1
-------

- La *docstring* ne décrit pas réellement ce que fait la fonction. La valeur
  résultante est placée dans un entier non signé, pas dans une chaîne de
  caractères.
- Éviter d'utiliser une majuscule sans raison (``Integer``). Ce n'est pas du
  Java, il n'y a pas de classe ``Integer``.

Tâche 2
-------

- Fonctionnel avec tests à l'appui.
- Graphviz n'est pas une dépendance du projet, qui peut fonctionner sans le
  logiciel.
- Beaucoup d'espaces superflues.

Tâche 3
-------

- Fonctionnel, avec tests à l'appui.
- La fonction ``getJson`` est beaucoup, beaucoup trop longue. Il aurait fallu
  la scinder et mieux factoriser (beaucoup de redondance).
- Même commentaire sur les espaces superflues.

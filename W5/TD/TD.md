# Interaction Matériel et Appels Système en C

Ce document vise à expliquer comment un programme en langage C interagit avec le matériel en utilisant des appels système, qui sont des fonctions du noyau du système d'exploitation.

## 1. Affichage avec printf()

L'instruction `printf()` implique un appel système (`write()`) pour écrire dans la console (`stdout`). Cependant, les appels système sont coûteux, donc il est recommandé de minimiser leur utilisation. Une solution efficace consiste à utiliser un buffer temporaire pour regrouper plusieurs appels `printf()` avant d'effectuer un seul appel à la fonction système `write()`. Notons que le noyau traite `STDOUT`, `STDIN`, `STDERR`, etc. comme des fichiers.

## 2. Gestion de la Mémoire avec malloc()
La fonction `malloc()` utilise un appel système (`brk()`) pour augmenter la taille de la heap lorsque nécessaire. Pour minimiser le nombre d'appels système coûteux, il est préférable d'utiliser des buffers temporaires pour regrouper plusieurs opérations `malloc()` avant d'effectuer un seul appel à `brk()`. On peut apercevoir que pour un appel `brk()`, la heap augmente d'une taille de `135.000`, ce qui est largement supérieur à ce qui est demandé ! C'est également pour minimiser le nombre d'appels système à brk(). C'est le même principe pour les appels `free()`, utilisation d'un buffer pour stocker puis `grosse baisse` de mémoire avec un unique appel à `brk()`.

## 3. Manipulation de Fichiers
Différents appels système sont impliqués lors de la manipulation de fichiers :

`openat()` est utilisé dans `fopen()` pour ouvrir un fichier.
`write()` est appelé dans `(s)printf()` pour écrire dans un fichier.
`read()` est employé dans `fread()` pour lire depuis un fichier.
`lseek()` est utilisé dans `fseek()` pour déplacer le curseur du fichier.

## 4. Ligne de Commande
Lors de l'exécution du programme avec `strace`, il y a un blocage dû à l'attente `d'input` depuis `STDIN`.
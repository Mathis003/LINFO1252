/*
En programmation fonctionnelle, les fonctions d'ordre supérieur map et fold sont souvent utilisées.

Elles ont la sémantique suivante :

map sert à appliquer une fonction sur chaque élément d'un tableau. Elle prend deux arguments en entrée :

        Un tableau d'éléments
        Une fonction unaire (qui prend un seul argument, et retourne un seul argument; ici on considèrera que les arguments sont des int)

Elle retourne un nouveau tableau, dont chaque élément est le résultat de l'exécution de la fonction sur l'élément correspondant du tableau en entrée.

fold permet d'agréger les valeurs d'un tableau avec une fonction d'agrégation. Elle prend donc en entrée trois arguments :

        Un tableau d'éléments à traiter
        Une valeur initiale du résultat agrégé
        Une fonction à appliquer à chaque élément combiné à la valeur de l'agrégateur actuel

Elle retourne la valeur agrégée sur tout le tableau.

Par exemple, l'application de la fonction "mise au carré" sur le tableau [1, 2, 3] avec map est [1, 4, 9]. L'application de ce tableau résultat, de la fonction * et de la valeur de départ 2 avec fold donne la valeur 72 ( = 2*1*4*9).

Il vous est dans un premier temps demandé de remplir la signature correcte pour ces fonctions (sans le point virgule). Une fois les signatures correctes, vous pourrez implémenter le corps des fonctions.

On considére que les tableaux contiennent toujours des int (signés) et que le fold se fait de gauche à droite (donc dans l'ordre naturel des éléments du tableau).
*/

#include <stdio.h>
#include <stdlib.h>

void display_array(int array[], int size)
{
    printf("[");
    for (int i = 0; i < size - 1; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("%d]\n", array[size - 1]);
    
}

int *map(int *array, size_t size, int (*f_map) (int))
{
    int *new_array = (int *) malloc(size * sizeof(int));
    if (new_array == NULL)
    {
        printf("Error : malloc()");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        new_array[i] = f_map(array[i]);
    }
    return new_array;
}

int fold(int *array, int acc, size_t size, int (*f_fold) (int, int))
{
    for (int i = 0; i < size; i++)
    {
        acc = f_fold(acc, array[i]);
    }
    return acc;
}

int double_element(int elem) {return 2 * elem;}

int fold_funct(int acc, int elem_array) {return acc * elem_array;}

int main(int argc, char **argv)
{
    int array[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Initial array : ");
    display_array(array, size); // [1, 2, 3, 4, 5, 6]

    int *mapped_array = map(array, size, double_element);

    printf("Mapped array : ");
    display_array(mapped_array, size); // [2, 4, 6, 8, 10, 12]
    free(mapped_array);

    int acc = fold(array, 2, size, fold_funct);
    printf("acc = %d\n", acc); // 2 * 1 * 2 * 3 * 4 * 5 * 6 = 2 * 6! = 1440
}
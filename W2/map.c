/*
map sert à appliquer une fonction sur chaque élément d'un tableau. Elle prend deux arguments en entrée :

        Un tableau d'éléments
        Une fonction unaire (qui prend un seul argument, et retourne un seul argument; ici on considèrera que les arguments sont des int)

Elle retourne un nouveau tableau, dont chaque élément est le résultat de l'exécution de la fonction sur l'élément correspondant du tableau en entrée.
*/

#include <stdio.h>
#include <stdlib.h>

int *map(int *array, int size, int (*map_funct) (int))
{
    int *new_array = malloc(sizeof(int) * size);
    if (new_array == NULL)
    {
        printf("Error : malloc()");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        new_array[i] = map_funct(array[i]);
    }
    return new_array;
}

int *fold(int *array, int size, int (*fold_funct) (int))
{
    int *new_array = malloc(sizeof(int) * size);
    if (new_array == NULL)
    {
        printf("Error : malloc()");
        return NULL;
    }
    int idx = 0;
    for (int i = 0; i < size; i++)
    {
        if (fold_funct(array[i]))
        {
            new_array[idx] = array[i];
            idx++;
        }
    }
    return new_array;
}

void display_array(int array[], int size)
{
    printf("[");
    for (int i = 0; i < size - 1; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("%d]\n", array[size - 1]);
    
}

int double_element(int elem) {return 2 * elem;}

int pair_int(int number) {return (number % 2) == 0;}

int main(int argc, char **argv)
{
    int array[] = {0, 1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Initial array : ");
    display_array(array, size);

    int *mapped_array = map(array, size, double_element);

    printf("Mapped array : ");
    display_array(mapped_array, size);

    int *folded_array = fold(array, size, pair_int);

    printf("Folded array : ");
    display_array(folded_array, size);
}
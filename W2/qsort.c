/*
Voici la signature de sort, basée sur la fonction standard qsort qui a servi d'exemple dans le cours.

sort est une fonction de tri généraliste. Elle prend quatre arguements:

    Un pointeur vers la zone mémoire à trier == le premier élément d'un tableau
    Le nombre d'éléments de ce tableau
    La taille en octets de chacun de ces éléments
    Une fonction de comparaison

void sort(void *base, size_t nel, size_t width, int (*compare)(const void *, const void *));

Dans un premier temps, il vous est demandé de coder une fonction de comparaison compare mettant en œuvre le tri alphabétique de caractères ASCII, non sensible à la casse (e.g. "laura < Laure", "Rob" < "robert"), de sorte à ce qu'elle puisse être passée en argument à qsort.

Dans un deuxième temps, vous allez vous-mêmes coder la fonction sort avec la signature ci-dessus. Votre fonction doit vérifier que les arguments sont valides et trier le tableau (avec l'algorithme de tri de votre choix de complexité maximum O(N²), n'hésitez pas à ressortir votre bouquin du cours d'algo !).

Si les arguments fournis ne sont pas corrects, votre sort doit afficher un message d'erreur, retourner sans effet et ne pas planter.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void sort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
    if (base == NULL || nel <= 1 || width == 0 || compar == NULL) {return;}

    char **ptr_array = (char **) base;

    // Brute force
    for (size_t i = 0; i < nel - 1; i++)
    {
        for (size_t j = 0; j < nel - i - 1; j++)
        {
            if (compar(ptr_array[j], ptr_array[j + 1]) > 0)
            {
                char *temp = ptr_array[j];
                ptr_array[j] = ptr_array[j + 1];
                ptr_array[j + 1] = temp;
            }
        }
    }
}


int compare(const void *element1, const void *element2)
{
    const char *str1 = (const char *) element1;
    const char *str2 = (const char *) element2;

    int i = 0;
    while ((*(str1 + i) != '\0') && (*(str2 + i) != '\0'))
    {
        char char1_lowercase = *(str1 + i);
        if ('A' <= char1_lowercase && char1_lowercase <= 'Z') {char1_lowercase += ('a' - 'A');}

        char char2_lowercase = *(str2 + i);
        if ('A' <= char2_lowercase && char2_lowercase <= 'Z') {char2_lowercase += ('a' - 'A');}

        if (char1_lowercase != char2_lowercase) {return (char1_lowercase - char2_lowercase);}
        i++;
    }

    if (*(str1 + i) == '\0')
    {
        if (*(str2 + i) == '\0') {return 0;}
        return -1;
    }
    return 1;
}

void display_array(char *array[], int size)
{
    printf("[");
    for (int i = 0; i < size - 1; i++) {printf("%s, ", array[i]);}
    printf("%s]\n", array[size - 1]);
}

int main(int argc, char **argv)
{
    char **array_name = malloc(7 * sizeof(char *));
    array_name[0] = "HOmE";
    array_name[1] = "SkY";
    array_name[2] = "ShaDOW";
    array_name[3] = "pacK";
    array_name[4] = "Book";
    array_name[5] = "gIrl";
    array_name[6] = "boy";

    display_array(array_name, 7);
    printf("\n");

    sort(array_name, 7, sizeof(char *), &compare);

    display_array(array_name, 7);
    printf("\n");

    free(array_name);
    return 0;
}
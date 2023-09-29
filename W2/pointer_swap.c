/*
Considérons le code suivant :

int x = 3;
int y = 4;

int * a = &x ;
int * b = &y ;

....

// Before: a contains the address of x ; b contains the address of y
exchange_pointers( ... );
// After: b contains the address of x ; a contains the address of y

La fonction exchange_pointers sert à échanger les adresses contenues dans deux pointeurs, ici a et b.

Il vous est demandé d'appeler correctement cette fonction en remplaçant la ligne entre commentaires.

Vous devez également implémenter la fonction.
*/

#include <stdio.h>

void exchange_pointers(int **x, int **y)
{
    int *adress_tmp_x = *x;
    *x = *y;
    *y = adress_tmp_x;
}

int main(int argc, char **argv)
{
    int x = 3;
    int y = 4;

    int *a = &x;
    int *b = &y;

    printf("Adresse de a : %p\nAdresse de b : %p\n", a, b);

    exchange_pointers(&a, &b);
    printf("\n");
    
    printf("Adresse de a : %p\nAdresse de b : %p\n", a, b);
}
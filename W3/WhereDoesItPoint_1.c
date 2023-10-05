/*
Cet exercice mettra à l'épreuve votre compréhension de la gestion de la mémoire.
Différents snipets de codes vont vous être proposés.
Dans chaque snipet, différentes variables vont être sélectionnées.
A vous de trouver dans quelle partie de la mémoire est stockée/pointe la variable demandée.
*/

#include <stdio.h>
#include <stdlib.h>

short level = 5;
char success;
char host[] = "my_awesome_computer";

void print_coucou(char *str)
{
    printf("Coucou %s\n", str);
}

int main(int argc, char **argv)
{
    void (* my_func)(char *) = print_coucou;
    char *name = malloc(60 * sizeof(char)) ;
    int access = 5;
}

/*
level => segment des données initialisées
success => segment des données non initialisées
host => segment des données initialisées
my_func => sur la stack et pointe dans le segment text
name => sur la stack et pointe sur la heap
access => sur la stack
*/
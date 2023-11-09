/*
Dans cet exercice, vous allez implémenter une fonction qui calcule le nombre de secondes écoulées depuis un instant dans le passé.
Pour ce faire, la fonction à implémenter time_since reçoit un pointeur vers une struct timeval qui représente cet instant dans le passé.
Vous devez sélectionner une fonction de la librairie standard qui utilise un appel système permettant de consulter l'horloge de la
machine avec une précision jusqu'à la seconde au moins. Ensuite, calculez le nombre de secondes écoulées.

Vous devez importer les entêtes qui vous permettront d'utiliser les types représentant le temps et l'appel système de votre choix.
Un bon début est de se renseigner sur les types struct timeval et time_t.
*/

#include <stdio.h>
#include <sys/time.h>

/*
 * @pre: past_instant est un pointeur vers une structure timeval
 *       représentant un instant dans le passé.
 * @post: retourne le nombre de secondes écoulées depuis past_instant.
 */
time_t time_since(struct timeval *past_instant)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec - past_instant->tv_sec);
}

int main(int argc, char **argv)
{
    return 0;
}
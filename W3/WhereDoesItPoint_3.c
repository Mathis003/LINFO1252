/*
Cet exercice mettra à l'épreuve votre compréhension de la gestion de la mémoire.
Différents snipets de codes vont vous être proposés.
Dans chaque snipet, différentes variables vont être sélectionnées.
A vous de trouver dans quelle partie de la mémoire est stockée/pointe la variable demandée.
*/

int static counter = 5;
int static success;

int main(int argc,  char **argv)
{
    int static attempt = 10;
    int attempt_left = attempt - counter;
    int *ptr_attempt = &attempt;

    if (attempt_left > 0)
    {
        success = ask_questions();
    }
}

/*
counter => segment des données initialisées
success => segment des données non initialisées
attempt => segment des données initialisées
attempt_left => sur la stack
ptr_attempt => sur la stack et pointe dans le segment des données initialisées
*/
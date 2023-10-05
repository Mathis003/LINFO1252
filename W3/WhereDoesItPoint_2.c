/*
Cet exercice mettra à l'épreuve votre compréhension de la gestion de la mémoire.
Différents snipets de codes vont vous être proposés.
Dans chaque snipet, différentes variables vont être sélectionnées.
A vous de trouver dans quelle partie de la mémoire est stockée/pointe la variable demandée.
*/

void birthday(int *age, char *name)
{
    int new_age = *age + 1;
    *age = *age + 1;
    char *dummy_variable = name;
    printf("Joyeux anniversaire %s, %d ans déjà !\n", dummy_variable, new_age);
}

int main(int argc, char **argv)
{
    char *my_name = malloc(60 * sizeof(char));
    int age_Bob = 42;
    strcpy(my_name, "Bob");
    birthday(&age_Bob, my_name);
}


/*
age_Bob => sur la stack
age => pointe sur la stack
name => sur la stack et pointe sur la heap
dummy_variable => sur la stack et pointe sur la heap
*/
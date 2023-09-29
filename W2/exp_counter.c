#include <stdio.h>

unsigned int stexp()
{
    static unsigned int exp_counter = 1;
    static int isFirstCall = 1;

    if (isFirstCall)
    {
        exp_counter = 1;
        isFirstCall = 0;
    } else
    {
        if (exp_counter == 4096)
        {
            exp_counter = 1;
        } else
        {
            exp_counter *= 2;
        }
    }

    // Augmente de manière exponentielle avec les appels de la fonction
    printf("exp_counter = %u\n");
    return exp_counter;
}

int main(int argc, char **argv)
{
    for (int i = 0; i < 20; i++) stexp();
    
    return 0;
}
/*
A variable declared inside a function with the keyword static implies that the value of this variable will be kept across the different calls to this function.

For example, the first call to your function should return 1. The next call 2, then 4, ..., 4096, 1, ...

Static counter
Write the body of the function stexp which returns at its *n*th call the value 2^(n-1). Once it has returned the value 4096, the next return should go back to 1.

You have to use a static variable.
*/

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
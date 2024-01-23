#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
Helper function to display binary number
*/

char *get_str_bin(const unsigned int n, const short nbBits )
{
    unsigned bit = 0 ;
    unsigned mask = 1 ;
    char *buffer = malloc((nbBits + 3) * sizeof(char));
    if (buffer == NULL)
    {
        printf("Error : malloc()\n");
        return NULL;
    }
    buffer[0] = '0';
    buffer[1] = 'b';

    for (int i = 2 ; i < nbBits + 2 ; i++)
    {
        bit = (n & mask) >> (i - 2);
        buffer[nbBits + 3 - i] = (char) ('0' + bit);
        mask <<= 1 ;
    }
    buffer[nbBits + 2] = '\0';
    return buffer;
}

/*
Write the body of a function get_3_leftmost_bits that returns the 3 high order bits of x.

For instance, if x=0b11011001..., the function should return a uint8_t containing 0b00000110.

If x=0b01100001..., the function should return a uint8_t containing 0b00000011.
*/
uint8_t get_3_leftmost_bits(uint32_t x)
{
    return x >> 29;
}


/*
Write the body of a function get_4_rightmost_bits that returns the 4 low order bits of x.

For instance, if x=0b...11011001, the function should return a uint8_t containing 0b00001001.

If x=0b...11011101, your function should return 0b00001101
*/
uint8_t get_4_rightmost_bits(uint32_t x)
{
    // 0xF = 15 = 0b00...001111
    // On créé un masque 0xF pour récupérer uniquement les 4 bits de poids faible.
    return x & 0xF;
}


/*
Write the body of a function cycle_bits, which cycles all bits from n places to the left, according to the formula x[(i+n)%32] = x[i], where x[i] is the i-iest bit of x.

Here is a simple example with bytes. Consider byte 0b01101011. If n is set to 1, then cycle_bits would return 0b11010110.

If n is set to 4, then cycle_bits would return 0b10110110.
*/
uint32_t cycle_bits(uint32_t x, uint8_t n)
{
    return (x << n) | (x >> (32 - n)); 
}


/*
Write the body of a function that counts the number of bits set to 1 in its parameter :

For example, with bytes you should obtain the following results:

nbits(0b00000100) == 1;
nbits(0b00000111) == 3;
nbits(0b00001010) == 2;
*/

uint8_t nbits(uint32_t n)
{
    uint8_t count = 0;
    uint32_t mask = 1;

    for (int i = 0; i < 32; i++)
    {
        if ((n & mask) != 0) {count++;}
        mask <<= 1;
    }
    return count;
}

/*
Write the body of a function reset_highestorder_bit, which sets to 0 the highest bit set to 1 it finds, and does nothing if there's no bit set to 1.

For example, with bytes, reset_highestorder_bit(0b000111010101010) would return 0b000011010101010 and reset_highestorder_bit(0b100111010101010) would return 0b000111010101010

To write this function, you first need to determine the position of the highest order bit that is set to 1 and then reset its value.
*/
uint32_t reset_highestorder_strong_bit(uint32_t x)
{
    uint32_t mask = 1 << 31;

    for (int i = 31; i >= 0; i--)
    {
        if ((x & mask) != 0) {return x - mask;}
        mask >>= 1;
    }
    return x;
}

void display_function(char *name_function)
{
    printf("=== Function : %s ===\n", name_function);
}

int main(int argc, char **argv) {

    uint32_t nbers1 = 0b11001101001110001001001110011100;
    uint32_t nbers2 = 0b00001101001110001001001110011010;

    display_function("get_3_leftmost_bits()");
    printf("Input :  %s\nOutput : %s\n", get_str_bin(nbers1, 32), get_str_bin(get_3_leftmost_bits(nbers1), 8));
    printf("Input :  %s\nOutput : %s\n", get_str_bin(nbers2, 32), get_str_bin(get_3_leftmost_bits(nbers2), 8));

    printf("\n");

    display_function("get_4_rightmost_bits()");
    printf("Input :  %s\nOutput : %s\n", get_str_bin(nbers1, 32), get_str_bin(get_4_rightmost_bits(nbers1), 8));
    printf("Input :  %s\nOutput : %s\n", get_str_bin(nbers2, 32), get_str_bin(get_4_rightmost_bits(nbers2), 8));

    printf("\n");

    display_function("cycle_bits()");
    printf("Input :  %s\nOutput : %s\n", get_str_bin(nbers1, 32), get_str_bin(cycle_bits(nbers1, 2), 32));
    printf("Input :  %s\nOutput : %s\n", get_str_bin(nbers2, 32), get_str_bin(cycle_bits(nbers2, 12), 32));
    printf("Input :  %s\nOutput : %s\n", get_str_bin(nbers1, 32), get_str_bin(cycle_bits(nbers1, 33), 32));

    printf("\n");

    display_function("nbits()");
    printf("Input :  %s\nOutput : %d\n", get_str_bin(nbers1, 32), nbits(nbers1));
    printf("Input :  %s\nOutput : %d\n", get_str_bin(nbers2, 32), nbits(nbers2));

    printf("\n");
    
    display_function("reset_highestorder_strong_bit()");
    printf("Input :  %s\nOutput : %s\n", get_str_bin(nbers1, 32), get_str_bin(reset_highestorder_strong_bit(nbers1), 32));
    printf("Input :  %s\nOutput : %s\n", get_str_bin(nbers2, 32), get_str_bin(reset_highestorder_strong_bit(nbers2), 32));

    return 0;
}
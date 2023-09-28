#include <stdint.h>

/*
Write the body of a function get_3_leftmost_bits that returns the 3 high order bits of x.

For instance, if x=0b11011001..., the function should return a uint8_t containing 0b00000110.

If x=0b01100001..., the function should return a uint8_t containing 0b00000011.
*/

uint32_t get_3_leftmost_bits(uint32_t x) {
    /*
    On décale vers la droite les bits de 29.
    29 car x est un nombre encodé sur 32 bits et il faut garder les 3 bits de poids fort.
    */
    return x >> (32 - 3);
}


/*
Write the body of a function get_4_rightmost_bits that returns the 4 low order bits of x.

For instance, if x=0b...11011001, the function should return a uint8_t containing 0b00001001.

If x=0b...11011101, your function should return 0b00001101
*/

uint8_t get_4_rightmost_bits(uint32_t x) {
    // 0xF = 15 = 0b00...001111
    // On créé un masque 0xF pour récupérer uniquement les 4 bits de poids faible.
    return x & 0xF;
}


/*
Write the body of a function cycle_bits, which cycles all bits from n places to the left, according to the formula x[(i+n)%32] = x[i], where x[i] is the i-iest bit of x.

Here is a simple example with bytes. Consider byte 0b01101011. If n is set to 1, then cycle_bits would return 0b11010110.

If n is set to 4, then cycle_bits would return 0b10110110.
*/

uint32_t cycle_bits(uint32_t x, uint8_t n) {
    uint32_t tmp_x = x;
    uint32_t left_part = x << n;
    uint32_t right_part = tmp_x >> (32 - n);
    return left_part | right_part; 
}


/*
Write the body of a function that counts the number of bits set to 1 in its parameter :

For example, with bytes you should obtain the following results:

nbits(0b00000100) == 1;
nbits(0b00000111) == 3;
nbits(0b00001010) == 2;
*/

uint8_t nbits(uint32_t n) {
    uint8_t count = 0;
    uint32_t bit_indexed = 1;

    for (int i = 0; i < 32; i++) {
        if ((n & bit_indexed) != 0) {
            count++;
        }
        bit_indexed <<= 1;
    }

    return count;
}

/*
Write the body of a function reset_highestorder_bit, which sets to 0 the highest bit set to 1 it finds, and does nothing if there's no bit set to 1.

For example, with bytes, reset_highestorder_bit(0b000111010101010) would return 0b000011010101010 and reset_highestorder_bit(0b100111010101010) would return 0b000111010101010

To write this function, you first need to determine the position of the highest order bit that is set to 1 and then reset its value.
*/

uint32_t reset_highestorder_strong_bit(uint32_t x) {
    // Pouvait faire une boucle de droite à gauche (plus efficace pour les petits nombres)
    // Ma fonction est plus efficace pour de très grand nombre.
    uint32_t bit_indexed = 1 << 31;
    for (int i = 31; i >= 0; i--) {
        if ((x & bit_indexed) != 0) {
            return x - bit_indexed;
        }
        bit_indexed >>= 1;
    }
    return x;
}
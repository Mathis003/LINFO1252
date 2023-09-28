#include <stdint.h>

/*
Write the body of a function get_3_leftmost_bits that returns the 3 high order bits of x.

For instance, if x=0b11011001..., the function should return a uint8_t containing 0b00000110.

If x=0b01100001..., the function should return a uint8_t containing 0b00000011.
*/

uint8_t get_3_leftmost_bits(uint32_t x) {
    /*
    On décale vers la droite les bits de 29.
    29 car x est un nombre encodé sur 32 bits et il faut garder les 3 bits de poids fort.
    */
    return x >> (32 - 3);
}
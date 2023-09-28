#include "bits_functions.c"
#include <stdio.h>

int main(int argc, char **argv) {

    // 0xAB4D = D + 4 * 16 + B * 16^2 + A * 16^3 = 43853
    uint32_t hexa_nbers = 0xAB4D;

    // Display 0xAB4 = 2740
    uint32_t leftmost_3bits = get_3_leftmost_bits(hexa_nbers);
    printf("%d\n", leftmost_3bits);
    printf("%d", 0xAB4D >> 4);
}
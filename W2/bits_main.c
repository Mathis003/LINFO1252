#include "bits_functions.c"

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
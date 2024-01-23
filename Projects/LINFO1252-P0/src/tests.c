#include "../headers/tests.h"

void print_HEAP()
{
    printf("==== PRINT THE HEAP ====\n");

    uint16_t loc = 2;
    uint16_t size;

    printf("nextfit offset\t");
    printf("adress: %d\t", 0);
    printf("size: %d \t", 2);
    printf("value: %d\n", 2 * ((MY_HEAP[0] & 0xFF) + (MY_HEAP[1] << 8)));

    while (loc < HEAP_SIZE)
    {
        size = (MY_HEAP[loc] & 0xFE) + (MY_HEAP[loc + 1] << 8);

        if (!(MY_HEAP[loc] & 0x1)) printf("free    \t");
        else printf("allocated\t");

        printf("adress: %d\t", loc);
        printf("size: %d \t", size);
        printf("value: [ ");

        if (!(MY_HEAP[loc] & 0x1)) printf("... ");
        else
        {
            uint16_t zero_counter = 0;
            for (uint16_t i = loc + SIZE_HEADER; i < loc + size + SIZE_HEADER; i++)
            {
                if (MY_HEAP[i] == 0) zero_counter++;                
                else
                {
                    if (zero_counter > 0) printf("0*%d ", zero_counter);
                    zero_counter = 0;
                    printf("%x ", MY_HEAP[i]);
                }
            }
            if (zero_counter > 0) printf("0*%d ", zero_counter);
        }
        printf("]\n");
        loc += size + SIZE_HEADER;
    }
    printf("\n");
}

void emptyHEAP()
{
    printf("Empty HEAP:\n");
    init();
    print_HEAP();
}

void test1()
{
    init();
    
    //** Invalid Argument Malloc **//
    printf("Invalid Argument Malloc:\n");
    void *invalid_malloc1 = my_malloc(0);
    void *invalid_malloc2 = my_malloc(-2);
    void *invalid_malloc3 = my_malloc(64000);
    void *invalid_malloc4 = my_malloc(63999);
    if (invalid_malloc1 != NULL) printf("Error!");
    if (invalid_malloc2 != NULL) printf("Error!");
    if (invalid_malloc3 != NULL) printf("Error!");
    if (invalid_malloc4 != NULL) printf("Error!");
    print_HEAP();


    //** Simple Malloc **//
    printf("Simple Malloc:\n");
    uint8_t *simple_malloc = (uint8_t *) my_malloc(4);
    if (simple_malloc == NULL) printf("Error: malloc return NULL\n");
    *simple_malloc = 130;
    if (*simple_malloc != 130) printf("Error: the value is not the expected one\n");
    print_HEAP();
    

    void *other_malloc = my_malloc(100);
    print_HEAP();

    //** Simple Free **//
    printf("Simple Free:\n");
    my_free(simple_malloc);
    print_HEAP();

    //** Free With Merged Next Block (Only One) **//
    printf("Free With Merged Next Block (Only One):\n");
    my_free(other_malloc);
    print_HEAP();
}

void test2()
{
    init();

    //** Multiple Big Malloc **//
    printf("Multiple Big Malloc:\n");
    void *big_malloc1 = my_malloc(20000);
    void *big_malloc2 = my_malloc(10000);
    void *big_malloc3 = my_malloc(10000);
    void *big_malloc4 = my_malloc(20000);
    void *big_malloc5 = my_malloc(3988);
    print_HEAP();


    //** HEAP Full **//
    printf("HEAP Full:\n");
    void *full_malloc1 = my_malloc(20000);
    void *full_malloc2 = my_malloc(1);
    void *full_malloc3 = my_malloc(0);
    void *full_malloc4 = my_malloc(-2);
    if (full_malloc1 != NULL) printf("Error!");
    if (full_malloc2 != NULL) printf("Error!");
    if (full_malloc3 != NULL) printf("Error!");
    if (full_malloc4 != NULL) printf("Error!");
    print_HEAP();


    //** Free With Merged Next Block (Multiple) **//
    printf("Free With Merged Next Block (Multiple):\n");
    my_free(big_malloc3);
    my_free(big_malloc4);
    print_HEAP();
    my_free(big_malloc2);
    print_HEAP();
}

void test3()
{
    init();

    void *first = my_malloc(10000);
    void *second = my_malloc(20000);
    void *third = my_malloc(15000);
    void *fourth = my_malloc(4);
    void *fifth = my_malloc(10);
    void *sixth = my_malloc(12);
    void *seventh = my_malloc(52);
    void *eight = my_malloc(10000);
    void *ninth = my_malloc(10000);
    void *ten = my_malloc(8902);
    my_free(fourth);
    my_free(fifth);
    my_free(sixth);
    my_free(seventh);

    //** Malloc but no available size **//
    printf("Malloc but no available size\n");
    print_HEAP();
    void *no_size = my_malloc(52 + 12 + 10 + 4 + 8);
    if (no_size != NULL) printf("Error!\n");
    print_HEAP();
}

void test4()
{
    init();
    
    void *un = my_malloc(10000);
    void *deux = my_malloc(20000);
    void *trois = my_malloc(15000);
    void *quatres = my_malloc(4);
    void *cinq = my_malloc(10);
    void *six = my_malloc(12);
    void *sept = my_malloc(52);
    void *huit = my_malloc(10000);
    void *neuf = my_malloc(10000);
    void *dix = my_malloc(8902);
    my_free(quatres);
    my_free(cinq);
    my_free(six);
    my_free(sept);

    //** Malloc but available size if merged 4 blocks **//
    printf("Malloc but available size if merged 4 blocks\n");
    print_HEAP();
    my_malloc(84);
    print_HEAP();
}


int main(int argc, char *argv[])
{
    emptyHEAP();
    test1();
    test2();
    test3();
    test4();
}
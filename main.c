//Helen Ngo
//September 17, 2024 
//Collatz conjecture, LRU & LFU cached

#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

int main (int argc, char *argv[]) {

    unsigned long int num_of_values = atoi(argv[1]);
    unsigned long int MIN = atoi(argv[2]);
    unsigned long int MAX = atoi(argv[3]);

    FILE *file = fopen("collatz.csv", "w");

    fprintf(file, "Random Number,Steps\n");
    for (unsigned long int ix = 0; ix < num_of_values; ix++) {
        unsigned long int random_num = MIN + rand() % (MAX - MIN + 1);
        unsigned long int steps = collatz_conjecture(random_num);
        fprintf(file, "%lu,%lu\n", random_num, steps);
    }
    fclose(file);
    return 0;
}
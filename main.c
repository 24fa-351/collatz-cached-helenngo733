//Helen Ngo
//September 17, 2024 
//Collatz conjecture, LRU & MRU cached

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cache.h"

int main (int argc, char *argv[]) {
    if (argc < 6 ) {
        fprintf(stderr, "Run: %s <num_of_values> <min> <min> <cache_policy> <cache_size>\n", argv[0]);
        return 1;
    }

    unsigned long int num_of_values = strtoul(argv[1], NULL, 10);
    unsigned long int MIN = strtoul(argv[2], NULL, 10);
    unsigned long int MAX = strtoul(argv[3], NULL, 10);
    int cache_policy = atoi(argv[4]);
    unsigned long int cache_size = strtoul(argv[5], NULL, 10);

    initialize_cache(cache_size);
    collatz_func_ptr provider = collatz_conjecture_provider;

    srand(time(NULL));

    FILE *file = fopen("collatz.csv", "w");

    fprintf(file, "Random Number,Steps\n");
    for (unsigned long int ix = 0; ix < num_of_values; ix++) {
        unsigned long int random_num = MIN + rand() % (MAX - MIN + 1);
        unsigned long int steps = collatz_conjecture(random_num, cache_policy, provider);
        fprintf(file, "%lu,%lu\n", random_num, steps);
    }
    fclose(file);

    double cache_hit_percentage = calculate_cache();
    printf("Cache Hit Percentage: %.2f%%\n", cache_hit_percentage);

    free_cache();

    return 0;
}
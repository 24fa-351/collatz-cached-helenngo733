#include <stdio.h>
#include <stdlib.h>

#include "cache.h"

//not sure if its safe to use static but it works for now
static CacheEntry *cache = NULL; 
static int cache_size = 0;  
static int counter = 0;

static unsigned long int cache_hits = 0;
static unsigned long int cache_misses = 0;

void initialize_cache(unsigned long int size) {
    cache_size = size;
    cache = (CacheEntry *)  malloc(cache_size * sizeof(CacheEntry));
    for (int ix = 0; ix < cache_size; ix++) {
        cache[ix].num = 0;
        cache[ix].steps =  0;
        cache[ix].frequency = 0;
        cache[ix].recent = 0;
        cache[ix].valid_entry = false;
    }
}

unsigned long int lookup(unsigned long int num) {
    for (int ix = 0; ix < cache_size;  ix++) {
        if (cache[ix].num == num && cache[ix].valid_entry) {
            cache_hits++;
            cache[ix].recent =  counter++;
            cache[ix].frequency++;
            return cache[ix].steps;
        }
    }
    cache_misses++;
    return 0; //entry not found
}

void insert(unsigned long int num, unsigned long int steps, int cache_policy) {
    CacheEntry *entry = findEntryToEvict(cache_policy);
    entry->num = num;
    entry ->steps = steps; 
    entry ->valid_entry = true;
    
    if (cache_policy == LFU) {
        entry->frequency = 1;
    }
    if (cache_policy == LRU) {
        entry->recent = counter++; 
    }
}

void evict(CacheEntry *entry) {
    entry->valid_entry = false;
}

CacheEntry *findEntryToEvict(int cache_policy) {
    CacheEntry *evict = NULL;
    for ( int ix = 0; ix < cache_size; ix++ ) { 
        if (!cache[ix].valid_entry) {
            return &cache[ix]; 
        }
        if (evict == NULL) {
            evict = &cache[ix];
        } 
        if (cache_policy == LRU && cache[ix].recent < evict->recent) {
            evict = &cache[ix];
        } else if (cache_policy == LFU && cache[ix].frequency < evict->frequency) {
            evict= &cache[ix];
        }
    }
    return evict;
}

unsigned long int collatz_conjecture_provider(unsigned long int num) {
    unsigned long int steps = 0;
    while (num != 1) {
        if (num % 2 == 0) {
            num = num / 2;
        } else {
            num = 3 * num + 1;
        }
        steps++;
    }
    return steps;
}

unsigned long int collatz_conjecture(unsigned long int num,int cache_policy, collatz_func_ptr provider) {
    unsigned long int steps = lookup(num);
    if (steps == 0) {
        steps = provider(num);
        insert(num, steps, cache_policy);
    }
    return steps;
}

double calculate_cache() {
    return (double)cache_hits / (cache_hits + cache_misses) * 100;
}

void free_cache() {
    free(cache);
} 
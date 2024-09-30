#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>

#define NONE 0
#define LRU 1
#define MRU 2

typedef struct {
    unsigned long int num;
    unsigned long int steps;
    unsigned long int recent;  // For LRU & MRU
    bool valid_entry; 
} CacheEntry;

typedef unsigned long int (*collatz_func_ptr) (unsigned long int);

void initialize_cache(unsigned long int size);
unsigned long int lookup(unsigned long int num);
void insert(unsigned long num, unsigned long int steps, int cache_policy);
void evict (CacheEntry *entry); 
CacheEntry *findEntryToEvict(int cache_policy); 

unsigned long int collatz_conjecture_provider(unsigned long int num);
unsigned long int collatz_conjecture(unsigned long int num, int cache_policy, collatz_func_ptr provider);

double calculate_cache();
void free_cache();

#endif
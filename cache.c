//Helen Ngo
//September 17, 2024 
//Collatz conjecture, LRU & LFU cached

#include <stdio.h>
#include <stdlib.h>

#include "cache.h"

unsigned long int collatz_conjecture(unsigned long int num) {
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

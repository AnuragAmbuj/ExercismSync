#ifndef KNAPSACK_H
#define KNAPSACK_H

#define MAX(a,b) ((a) > (b) ? (a) : (b)

#include <stddef.h>
typedef struct {
   unsigned int weight;
   unsigned int value;
} item_t;

int maximum_value(unsigned int maximum_weight,item_t *items , size_t item_count);

#endif

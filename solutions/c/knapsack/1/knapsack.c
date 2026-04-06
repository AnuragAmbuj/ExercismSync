#include "knapsack.h"

int maximum_value(unsigned int maximum_weight, item_t *items, size_t item_count){
    unsigned int i, w;
    unsigned int K[item_count + 1][maximum_weight + 1];
    for (i = 0; i <= item_count; i++){
        for (w = 0; w <= maximum_weight; w++){
            if (i == 0 || w == 0){
                K[i][w] = 0;
            } else if (items[i - 1].weight <= w){
                K[i][w] = MAX(items[i - 1].value + K[i - 1][w - items[i - 1].weight], K[i - 1][w]));
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }
    return K[item_count][maximum_weight];
}

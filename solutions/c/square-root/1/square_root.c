#include "square_root.h"

double square_root(double number){
    double x = number;
    double y = 1;
    double e = 0.000001;
    while (x - y > e){
        x = (x + y) / 2;
        y = number / x;
    }
    return x;
}

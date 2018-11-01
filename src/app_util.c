#include "../inc/app_util.h"

void util_increase(uint16_t *src,uint8_t step,uint16_t max) {
    
    if((*src) + step < max) {
        (*src) += step;
    } else {
        (*src) = max;
    }
}
void util_decrease(uint16_t *src,uint8_t step,uint16_t min) {
    
    if((*src) > min + step) {
        (*src) -= step;
    } else {
        (*src) = min;
    }
}
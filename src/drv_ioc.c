#include "../inc/drv_ioc.h"

ioc_isr_cb_t ioc_isr_cb;
void ioc_init(ioc_isr_cb_t cb) {
    
    IOCBPbits.IOCBP7 = 1;
    IOCBNbits.IOCBN7 = 1;
    IOCBFbits.IOCBF7 = 0;
    
    ioc_isr_cb = cb;
}
void ioc_enabled_isr() {
    
    PIE0bits.IOCIE = 1;
}
void ioc_disabled_isr() {
    
    PIE0bits.IOCIE = 0;
}
void ioc_isr() {
    
    IOCBFbits.IOCBF7 = 0;
    if(ioc_isr_cb != NULL) {
        ioc_isr_cb();
    }
}

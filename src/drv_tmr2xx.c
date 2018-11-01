#include "../inc/drv_tmr2xx.h"

#ifdef TMR2_ENABLED
tmr2xx_isr_cb_t tmr2_isr_cb;
void tmr2_init(tmr2xx_ckps_t ckps,tmr2xx_outps_t outps,tmr2xx_isr_cb_t cb) {
    
    T2CONbits.T2CKPS = (uint8_t)ckps;
    T2CONbits.T2OUTPS = (uint8_t)outps;
    TMR2 = 0x00;
    
    tmr2_isr_cb = cb;
}
void tmr2_reload(uint8_t value) {
    
    PR2 = value;
} 
void tmr2_starttimer() {
    
    T2CONbits.TMR2ON = 1;
}
void tmr2_stoptimer() {
    
    T2CONbits.TMR2ON = 0;
}
void tmr2_enabled_isr() {
    
    PIE1bits.TMR2IE = 1;
}
void tmr2_disabled_isr() {
    
    PIE1bits.TMR2IE = 0;
}
void tmr2_isr() {
    
    PIR1bits.TMR2IF = 0;
    if(tmr2_isr_cb != NULL) {
        tmr2_isr_cb();
    }
}
#endif
#ifdef TMR4_ENABLED
tmr2xx_isr_cb_t tmr4_isr_cb;
void tmr4_init(tmr2xx_ckps_t ckps,tmr2xx_outps_t outps,tmr2xx_isr_cb_t cb) {
    
    T4CONbits.T4CKPS = (uint8_t)ckps;
    T4CONbits.T4OUTPS = (uint8_t)outps;
    TMR4 = 0x00;
    
    tmr4_isr_cb = cb;
}
void tmr4_reload(uint8_t value) {
    
    PR4 = value;
} 
void tmr4_starttimer() {
    
    T4CONbits.TMR4ON = 1;
}
void tmr4_stoptimer() {
    
    T4CONbits.TMR4ON = 0;
}
void tmr4_enabled_isr() {
    
    PIE2bits.TMR4IE = 1;
}
void tmr4_disabled_isr() {
    
    PIE2bits.TMR4IE = 0;
}
void tmr4_isr() {
    
    PIR2bits.TMR4IF = 0;
    if(tmr4_isr_cb != NULL) {
        tmr4_isr_cb();
    }
}
#endif
#ifdef TMR6_ENABLED
tmr2xx_isr_cb_t tmr6_isr_cb;
void tmr6_init(tmr2xx_ckps_t ckps,tmr2xx_outps_t outps,tmr2xx_isr_cb_t cb) {
    
    T6CONbits.T6CKPS = (uint8_t)ckps;
    T6CONbits.T6OUTPS = (uint8_t)outps;
    TMR6 = 0x00;
    
    tmr6_isr_cb = cb;
}
void tmr6_reload(uint8_t value) {
    
    PR6 = value;
} 
void tmr6_starttimer() {
    
    T6CONbits.TMR6ON = 1;
}
void tmr6_stoptimer() {
    
    T6CONbits.TMR6ON = 0;
}
void tmr6_enabled_isr() {
    
    PIE2bits.TMR6IE = 1;
}
void tmr6_disabled_isr() {
    
    PIE2bits.TMR6IE = 0;
}
void tmr6_isr() {
    
    PIR2bits.TMR6IF = 0;
    if(tmr6_isr_cb != NULL) {
        tmr6_isr_cb();
    }
}
#endif

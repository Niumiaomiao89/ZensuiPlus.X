#include "../inc/drv_tmr1xx.h"

#if defined TMR1_ENABLED
tmr1xx_isr_cb_t tmr1_isr_cb;
void tmr1_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_isr_cb_t cb) {

    T1CONbits.TMR1CS = (uint8_t)cs;
    T1CONbits.T1CKPS = (uint8_t)ckps;
    T1GCON = 0x00;
   
    tmr1_isr_cb = cb;
}
void tmr1_writetimer(uint16_t value) {
 
    if(T1CONbits.T1SYNC == 1) {
        T1CONbits.TMR1ON = 0;
        TMR1H = value >> 8;
        TMR1L = value & 0xFF;
        T1CONbits.TMR1ON = 1;
    } else {
        TMR1H = value >> 8;
        TMR1L = value & 0xFF;
    } 
}
uint16_t tmr1_readtimer() {
    
    uint16_t readVal = 0;
    uint8_t readValHigh = 0;
    uint8_t readValLow = 0;
    
    readValHigh = TMR1H;
    readValLow = TMR1L;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;
    
    return readVal;
}
void tmr1_starttimer() {
    
    T1CONbits.TMR1ON = 1;
}
void tmr1_stoptimer() {
    
    T1CONbits.TMR1ON = 0;
}
void tmr1_enabled_isr() {
 
    PIE1bits.TMR1IE = 1;
}
void tmr1_disabled_isr() {
    
    PIE1bits.TMR1IE = 0;
}
void tmr1_isr() {
 
    PIR1bits.TMR1IF = 0;
    if(tmr1_isr_cb != NULL) {
        tmr1_isr_cb();
    }
}
#elif defined TMR1_GATE_ENABLED
tmr1xx_isr_cb_t tmr1_gate_isr_cb;
void tmr1_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_gate_src_t src,tmr1xx_isr_cb_t cb) {
    
    T1CONbits.TMR1CS = (uint8_t)cs;
    T1CONbits.T1CKPS = (uint8_t)ckps;
    
    T1GCONbits.TMR1GE = 1;
    T1GCONbits.T1GPOL = 1;
    T1GCONbits.T1GTM = 0;
    T1GCONbits.T1GSPM = 0;
    T1GCONbits.T1GGO_nDONE = 0;
    T1GCONbits.T1GSS = (uint8_t)src;
    
    tmr1_gate_isr_cb = cb;
}
void tmr1_writetimer(uint16_t value) {
 
    if(T1CONbits.T1SYNC == 1) {
        T1CONbits.TMR1ON = 0;
        TMR1H = value >> 8;
        TMR1L = value & 0xFF;
        T1CONbits.TMR1ON = 1;
    } else {
        TMR1H = value >> 8;
        TMR1L = value & 0xFF;
    } 
}
uint16_t tmr1_readtimer() {
    
    uint16_t readVal = 0;
    uint8_t readValHigh = 0;
    uint8_t readValLow = 0;
    
    readValHigh = TMR1H;
    readValLow = TMR1L;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;
    
    return readVal;
}
void tmr1_starttimer() {
    
    T1CONbits.TMR1ON = 1;
}
void tmr1_stoptimer() {
    
    T1CONbits.TMR1ON = 0;
}
void tmr1_gate_enabled_isr() {
    
    PIE1bits.TMR1GIE = 1;
}
void tmr1_gate_disabled_isr() {
    
    PIE1bits.TMR1GIE = 0;
}
void tmr1_gate_isr() {
    
    PIR1bits.TMR1GIF = 0;

    if(tmr1_gate_isr_cb != NULL) {
        tmr1_gate_isr_cb();
    }
}
#endif

#if defined TMR3_ENABLED
tmr1xx_isr_cb_t tmr3_isr_cb;
void tmr3_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_isr_cb_t cb) {

    T3CONbits.TMR3CS = (uint8_t)cs;
    T3CONbits.T3CKPS = (uint8_t)ckps;
    T3GCON = 0x00;
   
    tmr3_isr_cb = cb;
}
void tmr3_writetimer(uint16_t value) {
 
    if(T3CONbits.T3SYNC == 1) {
        T3CONbits.TMR3ON = 0;
        TMR3H = value >> 8;
        TMR3L = value & 0xFF;
        T3CONbits.TMR3ON = 1;
    } else {
        TMR3H = value >> 8;
        TMR3L = value & 0xFF;
    } 
}
uint16_t tmr3_readtimer() {
    
    uint16_t readVal = 0;
    uint8_t readValHigh = 0;
    uint8_t readValLow = 0;
    
    readValHigh = TMR3H;
    readValLow = TMR3L;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;
    
    return readVal;
}
void tmr3_starttimer() {
    
    T3CONbits.TMR3ON = 1;
}
void tmr3_stoptimer() {
    
    T3CONbits.TMR3ON = 0;
}
void tmr3_enabled_isr() {
 
    PIE3bits.TMR3IE = 1;
}
void tmr3_disabled_isr() {
    
    PIE3bits.TMR3IE = 0;
}
void tmr3_isr() {
 
    PIR3bits.TMR3IF = 0;
    if(tmr3_isr_cb != NULL) {
        tmr3_isr_cb();
    }
}
#elif defined TMR3_GATE_ENABLED
tmr1xx_isr_cb_t tmr3_gate_isr_cb;
void tmr3_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_gate_src_t src,tmr1xx_isr_cb_t cb) {
    
    T3CONbits.TMR3CS = (uint8_t)cs;
    T3CONbits.T3CKPS = (uint8_t)ckps;
    
    T3GCONbits.TMR3GE = 1;
    T3GCONbits.T3GPOL = 1;
    T3GCONbits.T3GTM = 0;
    T3GCONbits.T3GSPM = 0;
    T3GCONbits.T3GGO_nDONE = 0;
    T3GCONbits.T3GSS = (uint8_t)src;
    
    tmr3_gate_isr_cb = cb;
}
void tmr3_writetimer(uint16_t value) {
 
    if(T3CONbits.T3SYNC == 1) {
        T3CONbits.TMR3ON = 0;
        TMR3H = value >> 8;
        TMR3L = value & 0xFF;
        T3CONbits.TMR3ON = 1;
    } else {
        TMR3H = value >> 8;
        TMR3L = value & 0xFF;
    } 
}
uint16_t tmr3_readtimer() {
    
    uint16_t readVal = 0;
    uint8_t readValHigh = 0;
    uint8_t readValLow = 0;
    
    readValHigh = TMR3H;
    readValLow = TMR3L;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;
    
    return readVal;
}
void tmr3_starttimer() {
    
    T3CONbits.TMR3ON = 1;
}
void tmr3_stoptimer() {
    
    T3CONbits.TMR3ON = 0;
}
void tmr3_gate_enabled_isr() {
    
    PIE3bits.TMR3GIE = 1;
}
void tmr3_gate_disabled_isr() {
    
    PIE3bits.TMR3GIE = 0;
}
void tmr3_gate_isr() {
    
    PIR3bits.TMR3GIF = 0;

    if(tmr3_gate_isr_cb != NULL) {
        tmr3_gate_isr_cb();
    }
}
#endif

#if defined TMR5_ENABLED
tmr1xx_isr_cb_t tmr5_isr_cb;
void tmr5_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_isr_cb_t cb) {

    T5CONbits.TMR5CS = (uint8_t)cs;
    T5CONbits.T5CKPS = (uint8_t)ckps;
    T5GCON = 0x00;
   
    tmr5_isr_cb = cb;
}
void tmr5_writetimer(uint16_t value) {
 
    if(T5CONbits.T5SYNC == 1) {
        T5CONbits.TMR5ON = 0;
        TMR5H = value >> 8;
        TMR5L = value & 0xFF;
        T5CONbits.TMR5ON = 1;
    } else {
        TMR5H = value >> 8;
        TMR5L = value & 0xFF;
    } 
}
uint16_t tmr5_readtimer() {
    
    uint16_t readVal = 0;
    uint8_t readValHigh = 0;
    uint8_t readValLow = 0;
    
    readValHigh = TMR5H;
    readValLow = TMR5L;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;
    
    return readVal;
}
void tmr5_starttimer() {
    
    T5CONbits.TMR5ON = 1;
}
void tmr5_stoptimer() {
    
    T5CONbits.TMR5ON = 0;
}
void tmr5_enabled_isr() {
 
    PIE4bits.TMR5IE = 1;
}
void tmr5_disabled_isr() {
    
    PIE4bits.TMR5IE = 0;
}
void tmr5_isr() {
 
    PIR4bits.TMR5IF = 0;
    if(tmr5_isr_cb != NULL) {
        tmr5_isr_cb();
    }
}
#elif defined TMR5_GATE_ENABLED
tmr1xx_isr_cb_t tmr5_gate_isr_cb;
void tmr5_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_gate_src_t src,tmr1xx_isr_cb_t cb) {
    
    T5CONbits.TMR5CS = (uint8_t)cs;
    T5CONbits.T5CKPS = (uint8_t)ckps;
    
    T5GCONbits.TMR5GE = 1;
    T5GCONbits.T5GPOL = 1;
    T5GCONbits.T5GTM = 0;
    T5GCONbits.T5GSPM = 0;
    T5GCONbits.T5GGO_nDONE = 0;
    T5GCONbits.T5GSS = (uint8_t)src;
    
    tmr5_gate_isr_cb = cb;
}
void tmr5_writetimer(uint16_t value) {
 
    if(T5CONbits.T5SYNC == 1) {
        T5CONbits.TMR5ON = 0;
        TMR5H = value >> 8;
        TMR5L = value & 0xFF;
        T5CONbits.TMR5ON = 1;
    } else {
        TMR5H = value >> 8;
        TMR5L = value & 0xFF;
    } 
}
uint16_t tmr5_readtimer() {
    
    uint16_t readVal = 0;
    uint8_t readValHigh = 0;
    uint8_t readValLow = 0;
    
    readValHigh = TMR5H;
    readValLow = TMR5L;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;
    
    return readVal;
}
void tmr5_starttimer() {
    
    T5CONbits.TMR5ON = 1;
}
void tmr5_stoptimer() {
    
    T5CONbits.TMR5ON = 0;
}
void tmr5_gate_enabled_isr() {
    
    PIE4bits.TMR5GIE = 1;
}
void tmr5_gate_disabled_isr() {
    
    PIE4bits.TMR5GIE = 0;
}
void tmr5_gate_isr() {
    
    PIR4bits.TMR5GIF = 0;

    if(tmr5_gate_isr_cb != NULL) {
        tmr5_gate_isr_cb();
    }
}
#endif







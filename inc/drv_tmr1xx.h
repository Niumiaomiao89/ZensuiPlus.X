/* 
 * File:   drv_tmr1xx.h
 * Author: Admin
 *
 * Created on 2018年7月18日, 上午10:19
 */

#ifndef DRV_TMR1XX_H
#define	DRV_TMR1XX_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
    typedef enum tmr1xx_cs {
        TMR1XX_CS_FOSC_4 = 0,
        TMR1XX_CS_FOSC,    
        TMR1XX_CS_TxCKI_SOSC, 
        TMR1XX_CS_LFINTOSC  
    }tmr1xx_cs_t;
    
    typedef enum tmr1xx_ckps {
        TMR1XX_CKPS_1 = 0,
        TMR1XX_CKPS_2,
        TMR1XX_CKPS_4,
        TMR1XX_CKPS_8
    }tmr1xx_ckps_t;
    
    typedef enum tmr1xx_gate_src {
        TMR1XX_GATE_SRC_T1G = 0,
        TMR1XX_GATE_SRC_TMR0OVF,
        TMR1XX_GATE_SRC_C1OUT,
        TMR1XX_GATE_SRC_C2OUT
    }tmr1xx_gate_src_t;
    
    typedef void (*tmr1xx_isr_cb_t)();
    
#if defined TMR1_ENABLED
    extern void tmr1_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_isr_cb_t cb);
    extern void tmr1_writetimer(uint16_t value);
    extern uint16_t tmr1_readtimer();
    extern void tmr1_starttimer();
    extern void tmr1_stoptimer();
    extern void tmr1_enabled_isr();
    extern void tmr1_disabled_isr();
    extern void tmr1_isr();
#elif defined TMR1_GATE_ENABLED
    extern void tmr1_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_gate_src_t src,tmr1xx_isr_cb_t cb);
    extern void tmr1_writetimer(uint16_t value);
    extern uint16_t tmr1_readtimer();
    extern void tmr1_starttimer();
    extern void tmr1_stoptimer();
    extern void tmr1_gate_enabled_isr();
    extern void tmr1_gate_disabled_isr();
    extern void tmr1_gate_isr();
#endif
    
#if defined TMR3_ENABLED
    extern void tmr3_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_isr_cb_t cb);
    extern void tmr3_writetimer(uint16_t value);
    extern uint16_t tmr3_readtimer();
    extern void tmr3_starttimer();
    extern void tmr3_stoptimer();
    extern void tmr3_enabled_isr();
    extern void tmr3_disabled_isr();
    extern void tmr3_isr();
#elif defined TMR3_GATE_ENABLED
    extern void tmr3_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_gate_src_t src,tmr1xx_isr_cb_t cb);
    extern void tmr3_writetimer(uint16_t value);
    extern uint16_t tmr3_readtimer();
    extern void tmr3_starttimer();
    extern void tmr3_stoptimer();
    extern void tmr3_gate_enabled_isr();
    extern void tmr3_gate_disabled_isr();
    extern void tmr3_gate_isr();
#endif
    
#if defined TMR5_ENABLED
    extern void tmr5_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_isr_cb_t cb);
    extern void tmr5_writetimer(uint16_t value);
    extern uint16_t tmr5_readtimer();
    extern void tmr5_starttimer();
    extern void tmr5_stoptimer();
    extern void tmr5_enabled_isr();
    extern void tmr5_disabled_isr();
    extern void tmr5_isr();
#elif defined TMR5_GATE_ENABLED
    extern void tmr5_init(tmr1xx_cs_t cs,tmr1xx_ckps_t ckps,tmr1xx_gate_src_t src,tmr1xx_isr_cb_t cb);
    extern void tmr5_writetimer(uint16_t value);
    extern uint16_t tmr5_readtimer();
    extern void tmr5_starttimer();
    extern void tmr5_stoptimer();
    extern void tmr5_gate_enabled_isr();
    extern void tmr5_gate_disabled_isr();
    extern void tmr5_gate_isr();
#endif

    
#ifdef	__cplusplus
}
#endif

#endif	/* DRV_TMR1XX_H */


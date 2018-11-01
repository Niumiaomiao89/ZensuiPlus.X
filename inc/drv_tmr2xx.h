/* 
 * File:   drv_tmr2xx.h
 * Author: Admin
 *
 * Created on 2018年7月18日, 上午10:19
 */

#ifndef DRV_TMR2XX_H
#define	DRV_TMR2XX_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"

    typedef enum tmr2xx_ckps {
        TMR2XX_CKPS_1 = 0,
        TMR2XX_CKPS_4,
        TMR2XX_CKPS_16,
        TMR2XX_CKPS_64
    }tmr2xx_ckps_t;
    
    typedef enum tmr2xx_outps {
        TMR2XX_OUTPS_1 = 0,
        TMR2XX_OUTPS_2,
        TMR2XX_OUTPS_3,
        TMR2XX_OUTPS_4,
        TMR2XX_OUTPS_5,
        TMR2XX_OUTPS_6,
        TMR2XX_OUTPS_7,
        TMR2XX_OUTPS_8,
        TMR2XX_OUTPS_9,
        TMR2XX_OUTPS_10,
        TMR2XX_OUTPS_11,
        TMR2XX_OUTPS_12,
        TMR2XX_OUTPS_13,
        TMR2XX_OUTPS_14,
        TMR2XX_OUTPS_15,
        TMR2XX_OUTPS_16
    }tmr2xx_outps_t;
    
    typedef void (*tmr2xx_isr_cb_t)(void);
    
#ifdef TMR2_ENABLED
    extern void tmr2_init(tmr2xx_ckps_t ckps, tmr2xx_outps_t outps, tmr2xx_isr_cb_t cb);
    extern void tmr2_reload(uint8_t value);
    extern void tmr2_starttimer();
    extern void tmr2_stoptimer();
    extern void tmr2_enabled_isr();
    extern void tmr2_disabled_isr();
    extern void tmr2_isr();
#endif
#ifdef TMR4_ENABLED
    extern void tmr4_init(tmr2xx_ckps_t ckps, tmr2xx_outps_t outps, tmr2xx_isr_cb_t cb);
    extern void tmr4_reload(uint8_t value);
    extern void tmr4_starttimer();
    extern void tmr4_stoptimer();
    extern void tmr4_enabled_isr();
    extern void tmr4_disabled_isr();
    extern void tmr4_isr();
#endif
#ifdef TMR6_ENABLED
    extern void tmr6_init(tmr2xx_ckps_t ckps, tmr2xx_outps_t outps, tmr2xx_isr_cb_t cb);
    extern void tmr6_reload(uint8_t value);
    extern void tmr6_starttimer();
    extern void tmr6_stoptimer();
    extern void tmr6_enabled_isr();
    extern void tmr6_disabled_isr();
    extern void tmr6_isr();
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* DRV_TMR2XX_H */


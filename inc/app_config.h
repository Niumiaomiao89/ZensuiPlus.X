/* 
 * File:   app_config.h
 * Author: Admin
 *
 * Created on 2018年7月23日, 下午5:57
 */

#ifndef APP_CONFIG_H
#define	APP_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
#include "drv_gpio.h"
    
#define GlobalInterruptEnable()             (INTCONbits.GIE = 1)
#define GlobalInterruptDisable()            (INTCONbits.GIE = 0)
#define PeripheralInterruptEnable()         (INTCONbits.PEIE = 1)
#define PeripheralInterruptDisable()        (INTCONbits.PEIE = 0)
    
#define _XTAL_FREQ                          16000000
    
#define PWM1_ENABLED
#define PWM2_ENABLED
#define PWM3_ENABLED
#define PWM4_ENABLED
#define PWM5_ENABLED
//#define PWM6_ENABLED
    
#if (defined PWM1_ENABLED) || (defined PWM2_ENABLED) || (defined PWM3_ENABLED) || (defined PWM4_ENABLED) || (defined PWM5_ENABLED)
#include "drv_pwm.h"
#endif
    
//#define TMR1_ENABLED
#define TMR1_GATE_ENABLED
//#define TMR3_ENABLED
//#define TMR3_GATE_ENABLED
//#define TMR5_ENABLED
//#define TMR5_GATE_ENABLED
    
#if (defined TMR1_ENABLED) || (defined TMR1_GATE_ENABLED) || (defined TMR3_ENABLED) || (defined TMR3_GATE_ENABLED) || (defined TMR5_ENABLED) || (defined TMR5_GATE_ENABLED)
#include "drv_tmr1xx.h"
#endif
    
#define TMR2_ENABLED
//#define TMR4_ENABLED
//#define TMR6_ENABLED
    
#if (defined TMR2_ENABLED) || (defined TMR4_ENABLED) || (defined TMR6_ENABLED)
#include "drv_tmr2xx.h"
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* APP_CONFIG_H */


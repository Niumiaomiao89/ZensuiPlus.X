/* 
 * File:   drv_pwm.h
 * Author: Admin
 *
 * Created on 2018年7月18日, 上午10:17
 */

#ifndef DRV_PWM_H
#define	DRV_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
    typedef enum pwm_clk_src {
        PWM_CS_TMR2 = 1,
        PWM_CS_TMR4,     
        PWM_CS_TMR6,       
    }pwm_clk_src_t;
    
#ifdef PWM1_ENABLED
    extern void pwm1_init(gpio_port_t port, gpio_pin_t pin, pwm_clk_src_t src);
    extern void pwm1_load_duty(uint16_t duty);
#endif
#ifdef PWM2_ENABLED
    extern void pwm2_init(gpio_port_t port, gpio_pin_t pin, pwm_clk_src_t src);
    extern void pwm2_load_duty(uint16_t duty);
#endif
#ifdef PWM3_ENABLED
    extern void pwm3_init(gpio_port_t port, gpio_pin_t pin, pwm_clk_src_t src);
    extern void pwm3_load_duty(uint16_t duty);
#endif
#ifdef PWM4_ENABLED
    extern void pwm4_init(gpio_port_t port, gpio_pin_t pin, pwm_clk_src_t src);
    extern void pwm4_load_duty(uint16_t duty);
#endif
#ifdef PWM5_ENABLED
    extern void pwm5_init(gpio_port_t port, gpio_pin_t pin, pwm_clk_src_t src);
    extern void pwm5_load_duty(uint16_t duty);
#endif
#ifdef PWM6_ENABLED
    extern void pwm6_init(gpio_port_t port, gpio_pin_t pin, pwm_clk_src_t src);
    extern void pwm6_load_duty(uint16_t duty);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_PWM_H */


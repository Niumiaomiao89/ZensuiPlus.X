/* 
 * File:   drv_gpio.h
 * Author: Admin
 *
 * Created on 2018年7月18日, 上午10:16
 */

#ifndef DRV_GPIO_H
#define	DRV_GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <xc.h>

    typedef enum gpio_port {
        GPIO_PORTA = 0,
        GPIO_PORTB,
        GPIO_PORTC,
    }gpio_port_t;
    
    typedef enum gpio_pin {
        GPIO_PIN0 = 0,
        GPIO_PIN1,
        GPIO_PIN2,
        GPIO_PIN3,
        GPIO_PIN4,
        GPIO_PIN5,
        GPIO_PIN6,  
        GPIO_PIN7              
    }gpio_pin_t;
    
    typedef enum gpio_state {
        GPIO_ANALOG = 0,
        GPIO_INPUT_FLOATING,
        GPIO_INPUT_PULLUP,
        GPIO_OUTPUT_HIGH,
        GPIO_OUTPUT_LOW            
    }gpio_state_t;
    
    typedef enum gpio_outputpps {
        GPIO_OUTPUTPPS_PWM5 = 2,
        GPIO_OUTPUTPPS_PWM6,  
        GPIO_OUTPUTPPS_CLC1OUT,   
        GPIO_OUTPUTPPS_CLC2OUT, 
        GPIO_OUTPUTPPS_CLC3OUT,
        GPIO_OUTPUTPPS_CLC4OUT,
        GPIO_OUTPUTPPS_CWG1A,   
        GPIO_OUTPUTPPS_CWG1B,
        GPIO_OUTPUTPPS_CWG1C,
        GPIO_OUTPUTPPS_CWG1D,
        GPIO_OUTPUTPPS_CCP1, 
        GPIO_OUTPUTPPS_CCP2, 
        GPIO_OUTPUTPPS_CCP3, 
        GPIO_OUTPUTPPS_CCP4, 
        GPIO_OUTPUTPPS_CWG2A,   
        GPIO_OUTPUTPPS_CWG2B,
        GPIO_OUTPUTPPS_CWG2C,
        GPIO_OUTPUTPPS_CWG2D,
        GPIO_OUTPUTPPS_TX_CK,    
        GPIO_OUTPUTPPS_DT,
        GPIO_OUTPUTPPS_C1,
        GPIO_OUTPUTPPS_C2,
        GPIO_OUTPUTPPS_SCK1_SCL1,
        GPIO_OUTPUTPPS_SDO1_SDA1,
        GPIO_OUTPUTPPS_TMR0 = 28,  
        GPIO_OUTPUTPPS_NCO1,
        GPIO_OUTPUTPPS_CLKR, 
        GPIO_OUTPUTPPS_DSM          
    }gpio_outputpps_t;
    
    extern void gpio_set(gpio_port_t port,gpio_pin_t pin,gpio_state_t state);
    extern void gpio_set_outputpps(gpio_port_t port,gpio_pin_t pin,gpio_outputpps_t outputpps);
    extern uint8_t gpio_set_intputpps(gpio_port_t port,gpio_pin_t pin);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_GPIO_H */


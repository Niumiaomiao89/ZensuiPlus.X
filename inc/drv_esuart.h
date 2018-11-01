/* 
 * File:   drv_esuart.h
 * Author: Admin
 *
 * Created on 2018年7月18日, 下午2:59
 */

#ifndef DRV_ESUART_H
#define	DRV_ESUART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
#define EusartInitializeEnable()            (PIE1bits.RCIE = 1)
#define EusartInitializeDisable()           (PIE1bits.RCIE = 0) 
    typedef void (*eusart_rcv_callback_t)(uint8_t rcv);

#ifdef EUSART_ENABLED
    extern void eusart_init(gpio_port_t tx_port,gpio_pin_t tx_pin,gpio_port_t rx_port,gpio_pin_t rx_pin,eusart_rcv_callback_t callback);
    extern uint8_t eusart_write_byte(uint8_t byte);
    extern void eusart_transmit_isr();
    extern void eusart_rcv_isr();
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_ESUART_H */


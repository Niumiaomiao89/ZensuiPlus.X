/* 
 * File:   app_board.h
 * Author: Admin
 *
 * Created on 2018年7月23日, 下午5:58
 */

#ifndef APP_BOARD_H
#define	APP_BOARD_H

#include "drv_gpio.h"


#ifdef	__cplusplus
extern "C" {
#endif

#define PWM1_PORT               GPIO_PORTC
#define PWM1_PIN                GPIO_PIN5
#define PWM2_PORT               GPIO_PORTC
#define PWM2_PIN                GPIO_PIN3
#define PWM3_PORT               GPIO_PORTA
#define PWM3_PIN                GPIO_PIN2
#define PWM4_PORT               GPIO_PORTC
#define PWM4_PIN                GPIO_PIN1
#define PWM5_PORT               GPIO_PORTC
#define PWM5_PIN                GPIO_PIN7
#define IR_DAT_PORT             GPIO_PORTB
#define IR_DAT_PIN              GPIO_PIN7
    
#ifdef	__cplusplus
}
#endif

#endif	/* APP_BOARD_H */


/* 
 * File:   app_ir.h
 * Author: Admin
 *
 * Created on 2018年7月23日, 下午6:25
 */

#ifndef APP_IR_H
#define	APP_IR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
#define IR_USER_CODE        0x00FF
#define IR_USER_CODE_SWAP   0xFF00

#define KEY_ON              0x01
#define KEY_0FF             0x02
    
//#define KEY_M4              0x19
#define KEY_M1              0x05 
#define KEY_M2              0x06   
#define KEY_M3              0x07
    
#define KEY_R               0x08
#define KEYR_DOWN           0x09
#define KEYR_UP             0x0A                
#define KEY_PRESS1          0x0B
    
#define KEY_G               0x0C
#define KEYG_DOWN           0x0D
#define KEYG_UP             0x0E
#define KEY_PRESS2          0x0F
    
#define KEY_B               0x10
#define KEYB_DOWN           0x11
#define KEYB_UP             0x12
#define KEY_PRESS3          0x13
    
#define KEY_W1              0x14
#define KEYW1_DOWN          0x15
#define KEYW1_UP            0x16
#define KEY_PRESS4          0x17
    
#define KEY_W2              0x18
#define KEYW2_DOWN          0x19
#define KEYW2_UP            0x1A
#define KEY_PRESS5          0x1B 
    
#define KEY_NONE            0xFF
   
    extern void ir_tmr1_overflow_rest();
    extern void ir_decode();
    extern void ir_long_action();
    extern void ir_action();

#ifdef	__cplusplus
}
#endif

#endif	/* APP_IR_H */


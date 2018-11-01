/* 
 * File:   app_led.h
 * Author: Admin
 *
 * Created on 2018年7月23日, 下午6:26
 */

#ifndef APP_LED_H
#define	APP_LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
#define CHANNLE_COUNT               5
#define CUSTOM_COUNT                4
#define STEP_NORMAL_BRIGHT          2
#define STEP_LONG_BRIGHT            4
//#define STEP_SHORT_BRIGHT           100
   
#define STEP_SHORT_BRIGHT_RED       60
#define STEP_SHORT_BRIGHT_GREEN     60
#define STEP_SHORT_BRIGHT_BLUE      30
#define STEP_SHORT_BRIGHT_WARM      75
#define STEP_SHORT_BRIGHT_COLD      75
    
#define MAX_LED_BTIGHT_RED          600
#define MAX_LED_BRIGHT_GREEN        600
#define MAX_LED_BRIGHT_BLUE         300
#define MAX_LED_BRIGHT_WARM         750
#define MAX_LED_BRIGHT_COLD         750
#define MIN_LED_BRIGHT              0
   
#define STATE_PRESS_1               0x01
#define STATE_PRESS_2               0x02
#define STATE_PRESS_3               0x04
#define STATE_PRESS_4               0x08
    
#define LEDPARA_EEPROM_ADDR         0x7010
    
    typedef struct {
        
        unsigned    mOn         :1;
        unsigned    mState      :7;
        
        uint16_t    mBright[CHANNLE_COUNT];
        uint16_t    mCustomBirght[CUSTOM_COUNT][CHANNLE_COUNT];
    }led_para_t;
    
    typedef struct {
        unsigned    mNoticeStatus       :1;
        unsigned    mStartNotice        :1;
        unsigned    mNoticeCount        :6;
        
        uint16_t    mCurrentBright[CHANNLE_COUNT];
        uint16_t    mTargetBright[CHANNLE_COUNT];
    }led_run_para_t;
    
    extern void led_para_init();
    extern void led_init();
    extern void led_save_para();
    extern void led_set_state(uint8_t idx);
    extern void led_clear_state();
    extern bool led_get_state();
    extern bool led_get_power_state();
    extern void led_turnon_direct();
    extern void led_turnoff_direct();
    extern void led_toggle();
    extern void led_setcolour(uint8_t chn,uint16_t max);
    extern void led_set_increase_bright(uint8_t chn,uint8_t step,uint16_t max);
    extern void led_set_decrease_bright(uint8_t chn,uint8_t step,uint16_t min);
    extern void led_set_custom_bright(uint8_t chn);
    extern void led_set_custom(uint8_t chn);
    extern void led_startnotice(uint8_t cnt);
    extern void led_ramp();
    extern void led_run();

#ifdef	__cplusplus
}
#endif

#endif	/* APP_LED_H */


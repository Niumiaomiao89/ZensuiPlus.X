#include "../inc/drv_tmr1xx.h"
#include "../inc/drv_tmr2xx.h"
#include "../inc/app_ir.h"
#include "../inc/app_led.h"

#define STATE_IDLE              0
#define STATE_USER              1
#define STATE_KEY               2
#define STATE_RPT               3

#define RPT_COUNT               4

#define IR_STATE_VALUE_MAX      2750
#define IR_STATE_VALUE_MIN      1750
#define IR_HIGH_VALUE_MAX       1000
#define IR_HIGH_VALUE_MIN       720
#define IR_LOW_VALUE_MAX        400
#define IR_LOW_VALUE_MIN        220
#define IR_RPT_VALUE_MAX        1250
#define IR_RPT_VALUE_MIN        1000

#define SETTIME                 750

#define NOTICE_CUSTOM_SET       1

    typedef struct {
        unsigned    mRcvKey     :1;
        unsigned    mRptKey     :1;
        unsigned    mRsv        :6;
        uint8_t mState;
    }ir_state_t;
    
static uint8_t step_bright[CHANNLE_COUNT] = {STEP_SHORT_BRIGHT_RED,STEP_SHORT_BRIGHT_GREEN,STEP_SHORT_BRIGHT_BLUE,STEP_SHORT_BRIGHT_WARM,STEP_SHORT_BRIGHT_COLD};
static uint16_t max_bright[CHANNLE_COUNT] = {MAX_LED_BTIGHT_RED,MAX_LED_BRIGHT_GREEN,MAX_LED_BRIGHT_BLUE,MAX_LED_BRIGHT_WARM,MAX_LED_BRIGHT_COLD};    

static ir_state_t m_ir_state;
static uint8_t KeyValue;
    
static uint8_t ir_get_index(uint8_t keynum) {
    
    uint8_t index = 0xFF;
    
    switch(keynum) {
        case KEY_R:
        case KEY_M1:
        case KEYR_UP:
        case KEYR_DOWN:
        case KEY_PRESS1:
            index = 0;
            break;
        case KEY_G:
        case KEY_M2:
        case KEYG_UP:
        case KEYG_DOWN:
        case KEY_PRESS2:
            index = 1;
            break;
        case KEY_B:
        case KEY_M3:
        case KEYB_UP:
        case KEYB_DOWN:
        case KEY_PRESS3:
            index = 2;
            break;
        case KEY_W1:
        case KEYW1_UP:
        case KEYW1_DOWN:
        case KEY_PRESS4:
            index = 3;
            break;
        case KEY_W2:
        case KEYW2_UP:
        case KEYW2_DOWN:
        case KEY_PRESS5:
            index = 4;
            break;
        default:
            break;
    }
    return index;
}
void ir_tmr1_overflow_rest() {
    
    if(PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        tmr1_stoptimer();
        tmr1_writetimer(0);
        m_ir_state.mState = STATE_IDLE;
       
        if(m_ir_state.mRptKey) {
            m_ir_state.mRptKey = 0;
            switch(KeyValue) {
                case KEYR_UP:
                case KEYR_DOWN:
                case KEYG_UP:
                case KEYG_DOWN:
                case KEYB_UP:
                case KEYB_DOWN:
                case KEYW1_UP:
                case KEYW1_DOWN:
                case KEYW2_UP:
                case KEYW2_DOWN:
                case KEY_M1:
                case KEY_M2:
                case KEY_M3:
                    led_save_para();
                    break;
                default:
                    break;
            }
            KeyValue = KEY_NONE;
        } else {
            switch(KeyValue) {
                case KEYR_UP:
                case KEYR_DOWN:
                case KEYG_UP:
                case KEYG_DOWN:
                case KEYB_UP:
                case KEYB_DOWN:
                case KEYW1_UP:
                case KEYW1_DOWN:
                case KEYW2_UP:
                case KEYW2_DOWN:
                    if(!get_static_mode_state()) {
                        m_ir_state.mRcvKey = 1;
                    }
                    break;
                case KEY_M1:
                case KEY_M2:
                case KEY_M3:
                    m_ir_state.mRcvKey = 1;
                    break;
                default:
                    break;
            }
        }
        tmr2_enabled_isr();
        tmr1_starttimer();
    }
}
void ir_decode() {
    
    uint8_t keyNum = 0;
    uint8_t reKeyNum = 0;
    static uint8_t nBit = 0;
    static uint8_t rptCnt = 0;
    static uint16_t codeVal = 0;
    uint16_t hVal = tmr1_readtimer();
    tmr1_writetimer(0);
    switch(m_ir_state.mState) {
        case STATE_IDLE:
            if(hVal > IR_STATE_VALUE_MIN && hVal < IR_STATE_VALUE_MAX) {
                m_ir_state.mState = STATE_USER;
                codeVal = 0;
                nBit = 0;
                tmr2_disabled_isr();
            }
            break;
        case STATE_USER:
        case STATE_KEY:
            if(hVal > IR_LOW_VALUE_MIN && hVal < IR_LOW_VALUE_MAX) {
                nBit ++;
            } else if(hVal > IR_HIGH_VALUE_MIN && hVal < IR_HIGH_VALUE_MAX) {
                codeVal |= (1 << nBit);
                nBit ++;
            } else {
                m_ir_state.mState = STATE_IDLE;
            }
            if(nBit >= 16) {
                if(m_ir_state.mState == STATE_USER) {
                    if(codeVal == IR_USER_CODE_SWAP) {
                        m_ir_state.mState = STATE_KEY;
                    } else {
                        m_ir_state.mState = STATE_IDLE;
                    }
                } else if(m_ir_state.mState == STATE_KEY){
                    tmr2_enabled_isr();
                    keyNum = codeVal & 0xFF;
                    reKeyNum = codeVal >> 8;
                    if(keyNum ^ reKeyNum == 0xFF) {
                        KeyValue = keyNum;
                        if(led_get_power_state()) {
                            if(KeyValue == KEY_M1 || KeyValue == KEY_M2 || KeyValue == KEY_M3 || KeyValue == KEYR_UP || KeyValue == KEYR_DOWN ||
                                KeyValue == KEYG_UP || KeyValue == KEYG_DOWN || KeyValue == KEYB_UP || KeyValue == KEYB_DOWN ||
                                KeyValue == KEYW1_UP || KeyValue == KEYW1_DOWN || KeyValue == KEYW2_UP || KeyValue == KEYW2_DOWN) {
                                rptCnt = 0;
                                m_ir_state.mState = STATE_RPT;
                            } else {
                                m_ir_state.mRcvKey = 1;
                                m_ir_state.mState = STATE_IDLE;
                            }
                        } else {
                            if(KeyValue == KEY_ON) {
                                m_ir_state.mRcvKey = 1;
                                m_ir_state.mState = STATE_IDLE;
                            }
                        }
                    }
                }
                codeVal = 0;
                nBit = 0;
            }
            break;
        case STATE_RPT:
            if(hVal > IR_RPT_VALUE_MIN && hVal < IR_RPT_VALUE_MAX) {
                if(rptCnt < RPT_COUNT) {
                    rptCnt ++;
                } else {
                    m_ir_state.mRptKey = 1;
                }
            }
            break;
        default:
            break;
    }
}
void ir_long_action() {
    
    uint8_t idx = 0xFF;
    static uint8_t n = 0;
    static uint16_t cnt = 0;
    
    if(!m_ir_state.mRptKey) {
        return ;
    }
    if(get_static_mode_state()) {
        return ;
    }
    
    switch(KeyValue) {
        case KEYR_UP:
        case KEYG_UP:
        case KEYB_UP:
        case KEYW1_UP:
        case KEYW2_UP:
            cnt ++;
            if((cnt & 0x03) == 0x00) {
                cnt = 0;
                idx = ir_get_index(KeyValue);
                led_set_increase_bright(idx,STEP_LONG_BRIGHT,max_bright[idx]);
            }
            break;
        case KEYR_DOWN:
        case KEYG_DOWN:
        case KEYB_DOWN:
        case KEYW1_DOWN:
        case KEYW2_DOWN:
            cnt ++;
            if((cnt & 0x03) == 0x00) {
                cnt = 0;
                idx = ir_get_index(KeyValue);
                led_set_decrease_bright(idx,STEP_LONG_BRIGHT,MIN_LED_BRIGHT);
            }
            break;
        case KEY_M1:
        case KEY_M2:
        case KEY_M3:
            cnt ++;
            if(cnt == SETTIME) {
                cnt = 0;
                idx = ir_get_index(KeyValue);
                led_set_custom_bright(idx);
                led_startnotice(NOTICE_CUSTOM_SET);
            }
            break;
        default:
            break;
    }
}
static void ir_short_action() {
    
    uint8_t idx = 0xFF;
    
    switch(KeyValue) {
        case KEY_ON:
            led_turnon();
            led_init();
            break;
        case KEY_0FF:
            led_turnoff();
            led_init();
            break;
        case KEY_R:
        case KEY_G:
        case KEY_B:
        case KEY_W1:
        case KEY_W2:
            if(led_get_power_state()) {
                idx = ir_get_index(KeyValue);
                led_setcolour(idx,max_bright[idx]);
                led_clear_static_mode();
            }
            break;
        case KEYR_UP:
        case KEYG_UP:
        case KEYB_UP:
        case KEYW1_UP:
        case KEYW2_UP:
            if(led_get_power_state()) {
                idx = ir_get_index(KeyValue);
                led_set_increase_bright(idx,step_bright[idx],max_bright[idx]);
            }
            break;
        case KEYR_DOWN:
        case KEYG_DOWN:
        case KEYB_DOWN:
        case KEYW1_DOWN:
        case KEYW2_DOWN:
            if(led_get_power_state()) {
                idx = ir_get_index(KeyValue);
                led_set_decrease_bright(idx,step_bright[idx],MIN_LED_BRIGHT);
            }
            break;
        case KEY_PRESS1:
        case KEY_PRESS2:
        case KEY_PRESS3:
        case KEY_PRESS4:
        case KEY_PRESS5:
            idx = ir_get_index(KeyValue);
            idx = 1 << idx;
            led_set_static_mode(idx);   
            led_init();
            break;
        case KEY_M1:
        case KEY_M2:
        case KEY_M3:
            if(led_get_power_state()) {
                idx = ir_get_index(KeyValue);
                led_read_custom_bright(idx);
                led_clear_static_mode();
            }
            break;
        default:
            break;
    }
}
void ir_action() {
    
    if(m_ir_state.mRcvKey) {
        m_ir_state.mRcvKey = 0;
        ir_short_action();
        led_save_para();
        KeyValue = KEY_NONE;
    }
}

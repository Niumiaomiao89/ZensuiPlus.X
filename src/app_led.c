#include "../inc/drv_eeprom.h"
#include "../inc/app_led.h"
#include "../inc/app_util.h"
#include "../inc/app_ir.h"

typedef void (*led_load_duty_func_t)(uint16_t value);

//R G B 12000K 4000K
static led_load_duty_func_t led_load_duty[CHANNLE_COUNT] = {
    pwm2_load_duty,pwm1_load_duty,pwm3_load_duty,pwm4_load_duty,pwm5_load_duty
};

static uint16_t max_bright[CHANNLE_COUNT] = {MAX_LED_BTIGHT_RED,MAX_LED_BRIGHT_GREEN,MAX_LED_BRIGHT_BLUE,MAX_LED_BRIGHT_WARM,MAX_LED_BRIGHT_COLD}; 
static led_para_t m_led_para;
static led_run_para_t m_led_run_para;

void led_turnon_direct() {
    
    CCP1CON |= 0x80;
    CCP2CON |= 0x80;
    CCP3CON |= 0x80;
    CCP4CON |= 0x80;
    PWM5CON |= 0x80;
}
void led_turnoff_direct() {
    
    CCP1CON &= 0x7F;
    CCP2CON &= 0x7F;
    CCP3CON &= 0x7F;
    CCP4CON &= 0x7F;
    PWM5CON &= 0x7F;
}
static void led_turnon_ramp() {
    
    for(uint8_t i = 0; i < CHANNLE_COUNT; i++) {
        m_led_run_para.mTargetBright[i] = m_led_para.mBright[i];
    }
}
static void led_turnoff_ramp() {
    
    for(uint8_t i = 0; i < CHANNLE_COUNT; i++) {
        m_led_run_para.mTargetBright[i] = 0;
    }
}
void led_para_init() {
    
    eeprom_read_buffer(LEDPARA_EEPROM_ADDR,(uint8_t *)&m_led_para,sizeof(m_led_para));
    
    if((m_led_para.mState != STATE_PRESS_1) && (m_led_para.mState != STATE_PRESS_2) && (m_led_para.mState != STATE_PRESS_3) && (m_led_para.mState != STATE_PRESS_4)) {
        m_led_para.mState = 0;
    }
    
    for(uint8_t i = 0; i < CHANNLE_COUNT; i++) {
        if(m_led_para.mBright[i] > max_bright[i]) {
            m_led_para.mBright[i] = max_bright[i];
        }
    }
    
    for(uint8_t i = 0; i < CUSTOM_COUNT; i++) {
        for(uint8_t j = 0; j < CHANNLE_COUNT; j++) {
            if(m_led_para.mCustomBirght[i][j] > max_bright[j]) {
                m_led_para.mCustomBirght[i][j] = max_bright[j];
            }
        }
    }
}
void led_init() {
    
    if(m_led_para.mOn) {
        led_turnon_ramp();
        switch(m_led_para.mState) {
            case STATE_PRESS_1:
                m_led_run_para.mTargetBright[0] = 1000;
                m_led_run_para.mTargetBright[1] = 1000;
                m_led_run_para.mTargetBright[2] = 200;
                m_led_run_para.mTargetBright[3] = 300;
                m_led_run_para.mTargetBright[4] = 200;
                break;
            case STATE_PRESS_2:
                m_led_run_para.mTargetBright[0] = 700;
                m_led_run_para.mTargetBright[1] = 500;
                m_led_run_para.mTargetBright[2] = 1000;
                m_led_run_para.mTargetBright[3] = 0;
                m_led_run_para.mTargetBright[4] = 0;
                break;
            case STATE_PRESS_3:
                m_led_run_para.mTargetBright[0] = 0;
                m_led_run_para.mTargetBright[1] = 500;
                m_led_run_para.mTargetBright[2] = 0;
                m_led_run_para.mTargetBright[3] = 500;
                m_led_run_para.mTargetBright[4] = 500;
                break;
            case STATE_PRESS_4:
                m_led_run_para.mTargetBright[0] = 0;
                m_led_run_para.mTargetBright[1] = 0;
                m_led_run_para.mTargetBright[2] = 1000;
                m_led_run_para.mTargetBright[3] = 500;
                m_led_run_para.mTargetBright[4] = 0;
                break;
            default:
                break;
        }
    } else {
        led_turnoff_ramp();
    }
}
void led_save_para() {
    
    eeprom_write_buffer(LEDPARA_EEPROM_ADDR,(uint8_t *)&m_led_para,sizeof(m_led_para));
}
void led_set_state(uint8_t idx) {
    
    m_led_para.mState = idx;
}
void led_clear_state() {
    
    m_led_para.mState = 0;
}
bool led_get_state() {
    
    if(m_led_para.mState == STATE_PRESS_1 || m_led_para.mState == STATE_PRESS_2 || m_led_para.mState == STATE_PRESS_3 ||
            m_led_para.mState == STATE_PRESS_4) {
        return true;
    }
    return false;
}
bool led_get_power_state() {
    
    return m_led_para.mOn;
}
void led_toggle() {
    
    m_led_para.mOn = !m_led_para.mOn;
}
void led_setcolour(uint8_t chn,uint16_t max) {
    
    for(uint8_t i = 0; i < CHANNLE_COUNT; i++) {
        m_led_para.mBright[i] = 0;
        m_led_run_para.mTargetBright[i] = 0;
    }
    m_led_para.mBright[chn] = max;
    m_led_run_para.mTargetBright[chn] = m_led_para.mBright[chn];
}
void led_set_increase_bright(uint8_t chn,uint8_t step,uint16_t max) {
    
    util_increase(&m_led_para.mBright[chn],step,max);
    m_led_run_para.mTargetBright[chn] = m_led_para.mBright[chn];
}
void led_set_decrease_bright(uint8_t chn,uint8_t step,uint16_t min) {
    
    util_decrease(&m_led_para.mBright[chn],step,min);
    m_led_run_para.mTargetBright[chn] = m_led_para.mBright[chn];
}
void led_set_custom_bright(uint8_t chn) {
    
    for(uint8_t i = 0; i < CHANNLE_COUNT; i++) {
        m_led_para.mBright[i] = m_led_para.mCustomBirght[chn][i];
        m_led_run_para.mTargetBright[i] = m_led_para.mBright[i];
    }
}
void led_set_custom(uint8_t chn) {
    
    for(uint8_t i = 0; i < CHANNLE_COUNT; i++) {
        m_led_para.mCustomBirght[chn][i] =  m_led_para.mBright[i];
    }
}
void led_startnotice(uint8_t cnt) {
    
    m_led_run_para.mNoticeCount = cnt;
    m_led_run_para.mStartNotice = 1;
}
static void led_notice() {
    
    static uint16_t cnt = 0;
    
    if(m_led_run_para.mNoticeCount) {
        cnt ++;
        if((cnt & 0x1FF) == 0x00) {
            if(m_led_run_para.mNoticeStatus) {
                led_turnon_direct();
                m_led_run_para.mNoticeCount --;
                m_led_run_para.mNoticeStatus = 0;
            } else {
                led_turnoff_direct();
                m_led_run_para.mNoticeStatus = 1;
            }
        }
    } else {
        m_led_run_para.mStartNotice = 0;
        cnt = 0;
    }
}
void led_ramp() {
    
    for(uint8_t i = 0; i < CHANNLE_COUNT; i++) {
        if(m_led_run_para.mCurrentBright[i] + STEP_NORMAL_BRIGHT < m_led_run_para.mTargetBright[i]) {
            m_led_run_para.mCurrentBright[i] += STEP_NORMAL_BRIGHT;
        } else if(m_led_run_para.mCurrentBright[i] > m_led_run_para.mTargetBright[i] + STEP_NORMAL_BRIGHT) {
            m_led_run_para.mCurrentBright[i] -= STEP_NORMAL_BRIGHT;
        } else {
            m_led_run_para.mCurrentBright[i] = m_led_run_para.mTargetBright[i];
        }
        led_load_duty[i](m_led_run_para.mCurrentBright[i]);
    }
}
void led_run() {
    
    static uint8_t cnt = 0;
    
    if(m_led_run_para.mStartNotice) {
        led_notice();
    } else {
        cnt ++;
        if((cnt & 0x03) == 0x00) {
            cnt = 0;
            ir_long_action();
        }
        led_ramp();
    }
}

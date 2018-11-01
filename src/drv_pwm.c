#include "../inc/drv_pwm.h"

#ifdef PWM1_ENABLED
void pwm1_init(gpio_port_t port,gpio_pin_t pin,pwm_clk_src_t src) {
    
    gpio_set(port,pin,GPIO_OUTPUT_LOW);
    gpio_set_outputpps(port,pin,GPIO_OUTPUTPPS_CCP1);
    CCP1CONbits.CCP1EN = 1;
    CCP1CONbits.CCP1FMT = 1;
    CCP1CONbits.CCP1MODE = 0x0F;
    CCPTMRSbits.C1TSEL = (uint8_t)src;
    CCPR1H = 0x00;
    CCPR1L = 0x00;
}
void pwm1_load_duty(uint16_t duty) {
    
    CCPR1H = duty >> 2;
    CCPR1L = (duty & 0x03) << 6;
}
#endif
#ifdef PWM2_ENABLED
void pwm2_init(gpio_port_t port,gpio_pin_t pin,pwm_clk_src_t src) {
    
    gpio_set(port,pin,GPIO_OUTPUT_LOW);
    gpio_set_outputpps(port,pin,GPIO_OUTPUTPPS_CCP2);
    CCP2CONbits.CCP2EN = 1;
    CCP2CONbits.CCP2FMT = 1;
    CCP2CONbits.CCP2MODE = 0x0F;
    CCPTMRSbits.C2TSEL = (uint8_t)src;
    CCPR2H = 0x00;
    CCPR2L = 0x00;
}
void pwm2_load_duty(uint16_t duty) {
    
    CCPR2H = duty >> 2;
    CCPR2L = (duty & 0x03) << 6;
}
#endif
#ifdef PWM3_ENABLED
void pwm3_init(gpio_port_t port,gpio_pin_t pin,pwm_clk_src_t src) {
    
    gpio_set(port,pin,GPIO_OUTPUT_LOW);
    gpio_set_outputpps(port,pin,GPIO_OUTPUTPPS_CCP3);
    CCP3CONbits.CCP3EN = 1;
    CCP3CONbits.CCP3FMT = 1;
    CCP3CONbits.CCP3MODE = 0x0F;
    CCPTMRSbits.C3TSEL = (uint8_t)src;
    CCPR3H = 0x00;
    CCPR3L = 0x00;
}
void pwm3_load_duty(uint16_t duty) {
    
    CCPR3H = duty >> 2;
    CCPR3L = (duty & 0x03) << 6;
}
#endif
#ifdef PWM4_ENABLED
void pwm4_init(gpio_port_t port,gpio_pin_t pin,pwm_clk_src_t src) {
    
    gpio_set(port,pin,GPIO_OUTPUT_LOW);
    gpio_set_outputpps(port,pin,GPIO_OUTPUTPPS_CCP4);
    CCP4CONbits.CCP4EN = 1;
    CCP4CONbits.CCP4FMT = 1;
    CCP4CONbits.CCP4MODE = 0x0F;
    CCPTMRSbits.C4TSEL = (uint8_t)src;
    CCPR4H = 0x00;
    CCPR4L = 0x00;
}
void pwm4_load_duty(uint16_t duty) {
    
    CCPR4H = duty >> 2;
    CCPR4L = (duty & 0x03) << 6;
}
#endif
#ifdef PWM5_ENABLED
void pwm5_init(gpio_port_t port,gpio_pin_t pin,pwm_clk_src_t src) {
    
    gpio_set(port,pin,GPIO_OUTPUT_LOW);
    gpio_set_outputpps(port,pin,GPIO_OUTPUTPPS_PWM5);
    PWM5CONbits.PWM5EN = 1;
    PWMTMRSbits.P5TSEL = (uint8_t)src;
    PWM5DCH = 0x00;
    PWM5DCL = 0x00;
}
void pwm5_load_duty(uint16_t duty) {
    
    PWM5DCH = duty >> 2;
    PWM5DCL = (duty & 0x03) >> 6;
}
#endif
#ifdef PWM6_ENABLED
void pwm6_init(gpio_port_t port,gpio_pin_t pin,pwm_clk_src_t src) {
    
    gpio_set(port,pin,GPIO_OUTPUT_LOW);
    gpio_set_outputpps(port,pin,GPIO_OUTPUTPPS_PWM6);
    PWM6CONbits.PWM6EN = 1;
    PWMTMRSbits.P6TSEL = (uint8_t)src;
    PWM6DCH = 0x00;
    PWM6DCL = 0x00;
}
void pwm6_load_duty(uint16_t duty) {
    
    PWM6DCH = duty >> 2;
    PWM6DCL = (duty & 0x03) >> 6;
}
#endif
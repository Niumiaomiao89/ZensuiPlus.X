/*
 * File:   app_main.c
 * Author: Niumiaomiao
 *
 * Created on 2018年7月23日, 下午5:56
 */

#include "../inc/drv_osc.h"
#include "../inc/drv_ioc.h"
#include "../inc/app_board.h"
#include "../inc/app_ir.h"
#include "../inc/app_led.h"

// CONFIG1
#pragma config FEXTOSC = OFF    // FEXTOSC External Oscillator mode Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINT1    // Power-up default value for COSC bits->HFINTOSC
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; I/O or oscillator function on OSC2
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is disabled

// CONFIG2
#pragma config MCLRE = ON    // Master Clear Enable bit->MCLR/VPP pin function is MCLR; Weak pull-up enabled
#pragma config PWRTE = ON    // Power-up Timer Enable bit->PWRT enabled
#pragma config WDTE = ON    // Watchdog Timer Enable bits->WDT enabled, SWDTEN is ignored
#pragma config LPBOREN = OFF    // Low-power BOR enable bit->ULPBOR disabled
#pragma config BOREN = OFF    // Brown-out Reset Enable bits->Brown-out Reset disabled
#pragma config BORV = HIGH    // Brown-out Reset Voltage selection bit->Brown-out voltage (Vbor) set to 2.7V
#pragma config PPS1WAY = ON    // PPSLOCK bit One-Way Set Enable bit->The PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a Reset
#pragma config DEBUG = OFF    // Debugger enable bit->Background debugger disabled

// CONFIG3
#pragma config WRT = OFF    // User NVM self-write protection bits->Write protection off
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored.

// CONFIG4
#pragma config CP = OFF    // User NVM Program Memory Code Protection bit->User NVM code protection disabled
#pragma config CPD = OFF    // Data NVM Memory Code Protection bit->Data NVM code protection disabled

void app_init();

void main(void) {
    
    app_init();
    
    GlobalInterruptEnable();
    PeripheralInterruptEnable();
    
    led_para_init();
    led_init();
    
    while(1) {
        CLRWDT();
        
        ir_tmr1_overflow_rest();
        ir_action();
    }
}
void interrupt ISR() {

    if(PIE1bits.TMR1GIE && PIR1bits.TMR1GIF) {
        tmr1_gate_isr();
    } else if(PIE1bits.TMR2IE && PIR1bits.TMR2IF) {
        tmr2_isr();
    }
}
void app_init() {
    
    osc_init();
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0;
    
    pwm1_init(PWM1_PORT,PWM1_PIN,PWM_CS_TMR2);
    pwm2_init(PWM2_PORT,PWM2_PIN,PWM_CS_TMR2);
    pwm3_init(PWM3_PORT,PWM3_PIN,PWM_CS_TMR2);
    pwm4_init(PWM4_PORT,PWM4_PIN,PWM_CS_TMR2);
    pwm5_init(PWM5_PORT,PWM5_PIN,PWM_CS_TMR2);
    gpio_set(IR_DAT_PORT,IR_DAT_PIN,GPIO_INPUT_FLOATING);
    T1GPPS = gpio_set_intputpps(IR_DAT_PORT,IR_DAT_PIN);
    tmr1_init(TMR1XX_CS_FOSC_4,TMR1XX_CKPS_8,TMR1XX_GATE_SRC_T1G,ir_decode);
    tmr1_writetimer(0);
    tmr1_starttimer();
    tmr1_gate_enabled_isr();

    tmr2_init(TMR2XX_CKPS_1,TMR2XX_OUTPS_16,led_run);
    tmr2_reload(249);
    tmr2_starttimer();
    tmr2_enabled_isr();
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 1;
}

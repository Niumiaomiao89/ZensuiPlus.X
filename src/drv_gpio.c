#include "../inc/drv_gpio.h"

void gpio_set(gpio_port_t port,gpio_pin_t pin,gpio_state_t state) {
    
    uint8_t offset = port - GPIO_PORTA;
    uint8_t mask = 1 << (pin - GPIO_PIN0);
    
    switch(state) {
        case GPIO_ANALOG:
            *( ( &ANSELA + offset ) ) |= mask;
            *( ( &TRISA + offset ) ) |= mask; 
            break;
        case GPIO_INPUT_FLOATING:
            *( ( &ANSELA + offset ) ) &= ~mask;
            *( ( &TRISA + offset ) ) |= mask; 
            *( ( &WPUA + offset) ) &= ~mask;
            break;
        case GPIO_INPUT_PULLUP:
            *( ( &ANSELA + offset ) ) &= ~mask;
            *( ( &TRISA + offset ) ) |= mask; 
            *( ( &WPUA + offset) ) |= mask;
            break;
        case GPIO_OUTPUT_HIGH:
            *( ( &ANSELA + offset ) ) &= ~mask;
            *( ( &TRISA + offset ) ) &= ~mask; 
            *( ( &LATA + offset) ) |= mask;
            break;
        case GPIO_OUTPUT_LOW:
            *( ( &ANSELA + offset ) ) &= ~mask;
            *( ( &TRISA + offset ) ) &= ~mask; 
            *( ( &LATA + offset) ) &= ~mask;
            break;
        default:
            break;
    }
}
void gpio_set_outputpps(gpio_port_t port,gpio_pin_t pin,gpio_outputpps_t outputpps) {
    
    switch(port) {
        case GPIO_PORTA:
            *( ( &RA0PPS ) + pin ) = (uint8_t)outputpps;
            break;
        case GPIO_PORTB:
            *( ( &RB4PPS ) + pin - GPIO_PIN4) = (uint8_t)outputpps;
            break;
        case GPIO_PORTC:
            *( ( &RC0PPS ) + pin ) = (uint8_t)outputpps;
            break;
        default:
            break;
    }
}
uint8_t gpio_set_intputpps(gpio_port_t port,gpio_pin_t pin) {
    
    return (port << 3 | pin);
}

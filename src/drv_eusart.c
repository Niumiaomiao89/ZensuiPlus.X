#include "../inc/drv_esuart.h"

#ifndef EUSART_TX_BUFFER_SIZE
#define EUSART_TX_BUFFER_SIZE          128
#endif

#if ((defined _XTAL_FREQ) && (defined EUSART_BAUDRATE))
#define EUSART_BRG_VALUE           ((uint16_t)(_XTAL_FREQ/4/EUSART_BAUDRATE - 1))    
#else
#define EUSART_BRG_VALUE           51                       //76800
#endif

uint8_t tx_buffer[EUSART_TX_BUFFER_SIZE] = {0};
uint8_t tx_head;
uint8_t tx_tail;
uint8_t tx_remain;

eusart_rcv_callback_t eusart_rcv_cb;

void eusart_init(gpio_port_t tx_port,gpio_pin_t tx_pin,gpio_port_t rx_port,gpio_pin_t rx_pin,eusart_rcv_callback_t callback) {
    
    gpio_set(tx_port,tx_pin,GPIO_OUTPUT_HIGH);
    gpio_set_outputpps(tx_port,tx_pin,GPIO_OUTPUTPPS_TX_CK);
    gpio_set(rx_port,rx_pin,GPIO_INPUT_FLOATING);
    RXPPS = gpio_set_intputpps(rx_port,rx_pin);
    
    PIE1bits.TXIE = 0;
    PIE1bits.RCIE = 0;
    //TX1STA
    TX1STAbits.TX9 = 0;
    TX1STAbits.TXEN = 1;
    TX1STAbits.SYNC = 0;
    TX1STAbits.SENDB = 0;
    TX1STAbits.BRGH = 1;
    //RC1STA
    RC1STAbits.SPEN = 1;
    RC1STAbits.RX9 = 0;
    RC1STAbits.CREN = 1;
    //BAUD1CON
    BAUD1CONbits.SCKP = 0;
    BAUD1CONbits.BRG16 = 1;
    BAUD1CONbits.ABDEN = 0;
    SP1BRG = EUSART_BRG_VALUE;
    
    tx_head = 0;
    tx_tail = 0;
    tx_remain = sizeof(tx_buffer);
    
    eusart_rcv_cb = callback;
}
void putch(char c) {
    
    while(tx_remain == 0);
    if(PIE1bits.TXIE == 0) {
        TX1REG = c;
    } else {
        PIE1bits.TXIE = 0;
        tx_buffer[tx_head++] = c;
        if(tx_head >= sizeof(tx_buffer)) {
            tx_head = 0;
        }
        tx_remain --;
    }
    PIE1bits.TXIE = 1;
}
uint8_t eusart_write_byte(uint8_t byte) {
    
    putch(byte);
    return byte;
}
void eusart_transmit_isr() {
    
    if(tx_remain < sizeof(tx_buffer)) {
        TX1REG = tx_buffer[tx_tail++];
        if(tx_tail >= sizeof(tx_buffer)) {
            tx_tail = 0;
        }
        tx_remain ++;
    } else {
        PIE1bits.TXIE = 0;
    }
}
void eusart_rcv_isr() {
    
    uint8_t rcv = RCREG;
    if(eusart_rcv_cb != NULL) {
        eusart_rcv_cb(rcv);
    }
} 

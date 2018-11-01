#include "../inc/drv_eeprom.h"

void eeprom_write_byte(uint16_t addr,uint8_t byte) {
    
    uint8_t state = INTCONbits.GIE;
    
    NVMADRH = addr >> 8;
    NVMADRL = addr & 0xFF;
    NVMDATL = byte;
    NVMCON1bits.NVMREGS = 1;
    NVMCON1bits.WREN = 1;
    INTCONbits.GIE = 0;
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
    while(NVMCON1bits.WR);
    
    NVMCON1bits.WREN = 0;
    INTCONbits.GIE = state;

}
uint8_t eeprom_read_byte(uint16_t addr) {
    
    NVMADRH = addr >> 8;
    NVMADRL = addr & 0xFF;
    NVMCON1bits.NVMREGS = 1;
    NVMCON1bits.RD = 1;
    NOP();
    NOP();
    
    return NVMDATL;
}
void eeprom_write_buffer(uint16_t addr,uint8_t *pbuf,uint8_t len) {
    
	for ( uint8_t i = len; i != 0; i-- ) {
		eeprom_write_byte(addr++,*pbuf++ );
	}
}
void eeprom_read_buffer(uint16_t addr,uint8_t *pbuf,uint8_t len) {
    
	for ( uint8_t i = len; i != 0; i-- ) {
		*pbuf++ = eeprom_read_byte(addr++);
	}
}

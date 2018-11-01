#include "../inc/drv_osc.h"

void osc_init() {
    
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1bits.NOSC = OSC_NOSC_COSC_HFINTOSC;
    OSCCON1bits.NDIV = OSC_NDIV_CDIV_1;
    // CSWHOLD may proceed; SOSCPWR Low power; SOSCBE crystal oscillator; 
    OSCCON3 = 0x00;
    //EXTOEN disabled; HFOEN enabled, LFOEN disabled; ADOEN disabled; SOSCEN enabled; 
    OSCENbits.EXTOEN = 0;
    OSCENbits.HFOEN = 1;
    OSCENbits.LFOEN = 0;
    OSCENbits.SOSCEN = 1;
    OSCENbits.ADOEN = 0;
	// HFFRQ 16_MHz; 
    OSCFRQbits.HFFRQ = 0x06;
    //The oscillator module operates at a calibrated frequency
    OSCTUNEbits.HFTUN = 0x00;  
}
/* 
 * File:   drv_osc.h
 * Author: Admin
 *
 * Created on 2018年7月18日, 上午10:17
 */

#ifndef DRV_OSC_H
#define	DRV_OSC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
    typedef enum osc_nosc_cosc {
        OSC_NOSC_COSC_HFINTOSC_2PLL = 0,
        OSC_NOSC_COSC_EXTOSC_4PLL,
        OSC_NOSC_COSC_SOSC = 3,
        OSC_NOSC_COSC_LFINTOSC,
        OSC_NOSC_COSC_HFINTOSC = 6,
        OSC_NOSC_COSC_EXTOSC
    }osc_nosc_cosc_t;
    
    typedef enum osc_ndiv_cdiv {
        OSC_NDIV_CDIV_1 = 0,
        OSC_NDIV_CDIV_2,
        OSC_NDIV_CDIV_4,
        OSC_NDIV_CDIV_8,
        OSC_NDIV_CDIV_16,
        OSC_NDIV_CDIV_32,
        OSC_NDIV_CDIV_64,
        OSC_NDIV_CDIV_128,
        OSC_NDIV_CDIV_256,
        OSC_NDIV_CDIV_512
    }osc_ndiv_cdiv_t;
    
    extern void osc_init();
    
#ifdef	__cplusplus
}
#endif

#endif	/* DRV_OSC_H */


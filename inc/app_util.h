/* 
 * File:   app_util.h
 * Author: Admin
 *
 * Created on 2018年7月24日, 下午3:06
 */

#ifndef APP_UTIL_H
#define	APP_UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"

    extern void util_increase(uint16_t *src,uint8_t step,uint16_t max);
    extern void util_decrease(uint16_t *src,uint8_t step,uint16_t min);
    
#ifdef	__cplusplus
}
#endif

#endif	/* APP_UTIL_H */


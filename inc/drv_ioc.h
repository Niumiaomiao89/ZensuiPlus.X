/* 
 * File:   drv_ioc.h
 * Author: Admin
 *
 * Created on 2018年7月24日, 上午11:20
 */

#ifndef DRV_IOC_H
#define	DRV_IOC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
    typedef void(*ioc_isr_cb_t)();
    
    extern void ioc_init(ioc_isr_cb_t cb);
    extern void ioc_enabled_isr();
    extern void ioc_disabled_isr();
    extern void ioc_isr();

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_IOC_H */


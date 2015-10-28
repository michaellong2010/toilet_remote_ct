/* 
 * File:   remote_control.h
 * Author: Administrator
 *
 * Created on 2015?10?28?, ?? 1:44
 */

#ifndef REMOTE_CONTROL_H
#define	REMOTE_CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "mcc_generated_files/pin_manager.h"
#include "stdint.h"
//switch button
#define SW1_water_tank_temp 0
#define SW2_toilet_seat_temp 1
#define SW3_washing 2
#define SW4_spraying 3
#define SW5_stop_all 4
#define SW6_decrease 5
#define SW7_increase 6
#define SW8_blowing 7

typedef enum {
    TOIET_DUMMY_STATE = 0
    } TOIET_STATE;
    
#ifdef	__cplusplus
}
#endif

#endif	/* REMOTE_CONTROL_H */


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
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/i2c2.h" 
#include "LCD_xxx.h"
#include "mcc_generated_files/mcc.h"
#include "A7105reg.h"
//switch button
#define SW1_water_tank_temp 0
#define SW2_toilet_seat_temp 1
#define SW3_washing 2
#define SW4_spraying 3
#define SW5_stop_all 4
#define SW6_decrease 5
#define SW7_increase 6
#define SW8_fan_speed_temp 7

#define FAN_OFF 0
#define FAN_ON 1
#define INCREASE_LEVEL 0
#define DECREASE_LEVEL 0x80
#define LEVEL_DIR_MASK ( 1 << 7 )
 
 //LCD display backlight
#define DISPLAY_ON() backlight_SetHigh()
#define DISPLAY_OFF() backlight_SetLow()
#define DISPLAY_OFF_IDLE_SECONDS 15
#define DISPLAY_OFF_TIMER_OVERFLOW_COUNT ( 1000 * DISPLAY_OFF_IDLE_SECONDS ) / 262
#define I2C_HT16C21_ADDRESS ( 0x70 >> 1 )
#define I2C_HT16C21_CMD_DISPLAY_DATA 0x80
#define I2C_HT16C21_CMD_DRIVE_MODE 0x82
#define I2C_HT16C21_CMD_SYSTEM_MODE 0x84
#define I2C_HT16C21_CMD_FRAME_RATE 0x86
#define DUTY_BIT_POS 1
#define BIAS_BIT_POS 0
#define SYSOSC_BIT_POS 1
#define LCD_BIT_POS 0    

//define macro for debug use
#define debug_HT16C21 1  //debug step1
typedef enum {
    TOIET_DUMMY_STATE,
    TOIET_WATER_TEMP_STATE,
    TOIET_SEAT_TEMP_STATE,
    TOIET_WASHING_STATE,
    TOIET_SPRAYING_STATE,
    TOIET_FAN_SPEED_TEMP_STATE
} TOIET_STATE;

uint8_t water_T_level [] = { 'N', 35, 37, 39 };
uint8_t toilet_seat_T_level [] = { 'N', 35, 37, 39 };
uint8_t fan_T_S_level [][4] = { 'N', 40, 45, 50,  //fan speed1 temperature
                                   'N', 40, 45, 50 };  //fan speed2 temperature
uint8_t washing_F_level [] = { 'N', 1, 2, 3 };  //washing force level
uint8_t spraying_F_level [] = { 'N', 1, 2, 3 };
typedef struct {
    uint8_t water_T_index;  //water temperature
    uint8_t toilet_seat_T_index;  //toilet seat temperature
    uint8_t fan_on_off;
    uint8_t fan_S_index;  //fan speed & air volume
    uint8_t fan_T_index;  //fan temperature
    uint8_t washing_F_index;  //washing force level
    uint8_t spraying_F_index;
    uint16_t X_coord_val, Y_coord_val;
    TOIET_STATE toilet_state;
} Toilet_Ctl_Data_t;
Toilet_Ctl_Data_t toilet_ctrl_data = { 0, 0, FAN_OFF, 0, 0, 0, 0, TOIET_DUMMY_STATE };
extern volatile TOIET_STATE toilet_cur_state,toilet_last_state, toilet_next_state;
extern volatile uint8_t lock;
extern double Env_T;  //enviroment temperature;
uint8_t disp_ram_map_data [ 10 ] = { 0 };  //display scanning map for HT16C21

uint16_t key_scanning ( void );
void issue_key_scanning ( void );  //ISR for timer overflow,currently overflow period about 262ms
void toilet_state_action ( void );
uint8_t transmit_remote_data ( Toilet_Ctl_Data_t toilet_data );  //transmit toilet control data to host via RF 
void remote_control_init ( void );
void show_display_segment ( uint8_t *disp_seg, uint8_t len, bool is_show );
void show_display_segment1 ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* REMOTE_CONTROL_H */


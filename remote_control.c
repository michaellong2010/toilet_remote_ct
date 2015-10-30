
#include "remote_control.h"
#include <stdbool.h>
//define macro for debug use
#define debug_HT16C21 1

volatile TOIET_STATE toilet_cur_state = TOIET_DUMMY_STATE,toilet_last_state = TOIET_DUMMY_STATE, toilet_next_state = TOIET_DUMMY_STATE;
volatile uint8_t lock = 0;
double Env_T = 0.0, BAT_voltage1 = 0.0 , BAT_voltage2 = 0.0;  //enviroment temperature;

uint8_t transmit_remote_data ( Toilet_Ctl_Data_t toilet_data ) {
    return 0;
}

/* refresh toilet state, refresh remote display, monitor rocker lock on/off and fetch ADC
 * pass toilet_ctrl_data to host via RF TX */
void toilet_state_action ( void ) {
    bool is_need_refresh = false;
    
    if ( toilet_cur_state !=  toilet_next_state) {
        toilet_last_state = toilet_cur_state;
        toilet_cur_state = toilet_next_state;
        toilet_ctrl_data.toilet_state = toilet_cur_state;
        is_need_refresh = true;
    }
    
    if ( toilet_cur_state == TOIET_WASHING_STATE || toilet_cur_state == TOIET_SPRAYING_STATE || toilet_cur_state == TOIET_FAN_SPEED_TEMP_STATE  ) {
        if ( !lock ) {
            /*fetch X & Y ADC*/
            toilet_ctrl_data.X_coord_val = ADC_GetConversion( channel_AN0 );
            toilet_ctrl_data.Y_coord_val = ADC_GetConversion( channel_AN1 );
            is_need_refresh = true;
        }
        else {
        }
    }
    
    if ( is_need_refresh ) {
        /* do RF TX to transfer `toilet_ctrl_data` to host and refresh display */
    }
    Env_T = (double) ADC_GetConversion( channel_AN2 );
    BAT_voltage1 = (double) ADC_GetConversion( channel_AN3 );
}

void toggle_lock ( void ) {
    if ( lock )
        lock = 0;
    else
        lock = 1;
}

/* timer ISR to issue key scanning */
void issue_key_scanning ( void ) {
    //static TOIET_STATE toilet_cur_state = TOIET_DUMMY_STATE, toilet_last_state, toilet_next_state;
    static uint16_t newest_press_key = 0, n_timer_ov_count = 0;
   
   //if ( toilet_last_state != toilet_cur_state )
        //toilet_last_state = toilet_cur_state;
    //toilet_next_state = toilet_cur_state;
    newest_press_key = key_scanning ();
    
    if ( !newest_press_key ) {
        n_timer_ov_count++;
        if ( n_timer_ov_count == DISPLAY_OFF_TIMER_OVERFLOW_COUNT )
            DISPLAY_OFF ();
        return;
    }
    else {
        DISPLAY_ON ();
        n_timer_ov_count = 0;
    }
    if ( toilet_cur_state  <= TOIET_FAN_SPEED_TEMP_STATE ) {

            if ( newest_press_key & ( 1 << SW1_water_tank_temp ) ) {
                toilet_next_state = TOIET_WATER_TEMP_STATE;
                if ( ( toilet_ctrl_data.water_T_index & LEVEL_DIR_MASK  ) == INCREASE_LEVEL ) {
                    if ( ( toilet_ctrl_data.water_T_index + 1 ) == ( sizeof ( water_T_level ) / sizeof ( uint8_t ) ) ) {
                        toilet_ctrl_data.water_T_index--;
                        toilet_ctrl_data.water_T_index |= LEVEL_DIR_MASK;
                    }
                    else
                        toilet_ctrl_data.water_T_index++;
                }
                else {
                    if ( !( toilet_ctrl_data.water_T_index & ~LEVEL_DIR_MASK  ) ) {
                        toilet_ctrl_data.water_T_index ^= LEVEL_DIR_MASK;
                        toilet_ctrl_data.water_T_index++;
                    }
                    else
                        toilet_ctrl_data.water_T_index--;
                }
            }
            else
                if ( newest_press_key & ( 1 << SW2_toilet_seat_temp ) ) {
                    toilet_next_state = TOIET_SEAT_TEMP_STATE;
                    if ( ( toilet_ctrl_data.toilet_seat_T_index & LEVEL_DIR_MASK  ) == INCREASE_LEVEL ) {
                      if ( ( toilet_ctrl_data.toilet_seat_T_index + 1 ) == ( sizeof ( toilet_seat_T_level ) / sizeof ( uint8_t ) ) ) {
                        toilet_ctrl_data.toilet_seat_T_index--;
                        toilet_ctrl_data.toilet_seat_T_index |= LEVEL_DIR_MASK;
                      }
                      else
                        toilet_ctrl_data.toilet_seat_T_index++;
                    }
                    else {
                        if ( !( toilet_ctrl_data.toilet_seat_T_index & ~LEVEL_DIR_MASK  ) ) {
                            toilet_ctrl_data.toilet_seat_T_index ^= LEVEL_DIR_MASK;
                            toilet_ctrl_data.toilet_seat_T_index++;
                        }
                        else
                            toilet_ctrl_data.toilet_seat_T_index--;
                    }
                }
                else
                   if ( newest_press_key & ( 1 << SW8_fan_speed_temp ) ) {
                       toilet_next_state = TOIET_FAN_SPEED_TEMP_STATE;
                       toilet_ctrl_data.fan_on_off = FAN_ON;
 
                       if ( ( toilet_ctrl_data.fan_T_index & LEVEL_DIR_MASK  ) == INCREASE_LEVEL ) {
                           if ( ( toilet_ctrl_data.fan_T_index + 1 ) == ( sizeof ( fan_T_S_level [ toilet_ctrl_data.fan_S_index ] ) / sizeof ( uint8_t ) ) ) {
                               toilet_ctrl_data.fan_T_index--;
                               toilet_ctrl_data.fan_T_index |= LEVEL_DIR_MASK;
                           }
                           else
                               toilet_ctrl_data.fan_T_index++;
                       }
                       else {
                           if ( !( toilet_ctrl_data.fan_T_index & ~LEVEL_DIR_MASK  ) ) {
                               toilet_ctrl_data.fan_T_index ^= LEVEL_DIR_MASK;
                               toilet_ctrl_data.fan_T_index++;
                           }
                           else
                               toilet_ctrl_data.fan_T_index--;
                       }
                   }
                   else
                       if ( newest_press_key & ( 1 << SW3_washing ) ) {
                           toilet_next_state = TOIET_WASHING_STATE;
                       }
                       else
                           if ( newest_press_key & ( 1 << SW4_spraying ) ) {
                               toilet_next_state = TOIET_SPRAYING_STATE;
                               if ( ( toilet_ctrl_data.spraying_F_index & LEVEL_DIR_MASK  ) == INCREASE_LEVEL ) {
                                   if ( ( toilet_ctrl_data.spraying_F_index + 1 ) == ( sizeof ( spraying_F_level) / sizeof ( uint8_t ) ) ) {
                                       toilet_ctrl_data.spraying_F_index--;
                                       toilet_ctrl_data.spraying_F_index |= LEVEL_DIR_MASK;
                                   }
                                   else
                                       toilet_ctrl_data.spraying_F_index++;
                               }
                               else {
                                   if ( !( toilet_ctrl_data.spraying_F_index & ~LEVEL_DIR_MASK  ) ) {
                                       toilet_ctrl_data.spraying_F_index ^= LEVEL_DIR_MASK;
                                       toilet_ctrl_data.spraying_F_index++;
                                   }
                                   else
                                       toilet_ctrl_data.spraying_F_index--;
                               }
                           }
                           else
                               if ( newest_press_key & ( 1 << SW5_stop_all ) ) {
                                   toilet_next_state = TOIET_DUMMY_STATE;
                               }
                               else
                                   if ( newest_press_key & ( 1 << SW6_decrease ) ) {
                                       if ( toilet_cur_state == TOIET_WASHING_STATE ) {
                                           if ( toilet_ctrl_data.washing_F_index > 0 )
                                               toilet_ctrl_data.washing_F_index--;
                                       }
                                       else
                                           if ( toilet_cur_state == TOIET_FAN_SPEED_TEMP_STATE ) {
                                             //toggle fan speed
                                               if (toilet_ctrl_data.fan_S_index)
                                                   toilet_ctrl_data.fan_S_index = 0;
                                               else
                                                   toilet_ctrl_data.fan_S_index = 1;
                                           }
                                   }
                                   else
                                       if ( newest_press_key & ( 1 << SW7_increase ) ) {
                                           if ( toilet_cur_state == TOIET_WASHING_STATE ) {
                                               if ( ( toilet_ctrl_data.washing_F_index + 1 ) < sizeof ( washing_F_level ) / sizeof ( uint8_t ) )
                                                   toilet_ctrl_data.washing_F_index++;
                                           }
                                           else
                                               if ( toilet_cur_state == TOIET_FAN_SPEED_TEMP_STATE ) {
                                                   //toggle fan speed
                                                   if (toilet_ctrl_data.fan_S_index)
                                                       toilet_ctrl_data.fan_S_index = 0;
                                                   else
                                                       toilet_ctrl_data.fan_S_index = 1;
                                               }
                                       }
    }
    
    /*if ( toilet_cur_state != toilet_next_state ) {
        toilet_last_state = toilet_cur_state;
        toilet_cur_state = toilet_next_state;
    }*/
}

/* do key scanning */
uint16_t key_scanning ( void ) {    
    uint8_t key_in1, key_in2, key_in3;
    uint16_t press_key;
    
    key_scan_out1_SetDigitalOutput ();
    key_scan_out1_SetDigitalInput ();
    key_in1 = key_scan_in1_GetValue ();
    key_in2 = key_scan_in2_GetValue ();
    key_in3 = key_scan_in3_GetValue ();
    if ( key_in1 )
        press_key = 1 << SW1_water_tank_temp;
    if ( key_in2 )
        press_key = 1 << SW4_spraying;
    if ( key_in3 )
        press_key = 1 << SW7_increase;
    
    key_scan_out2_SetDigitalOutput ();
    key_scan_out2_SetDigitalInput ();
    key_in1 = key_scan_in1_GetValue ();
    key_in2 = key_scan_in2_GetValue ();
    key_in3 = key_scan_in3_GetValue ();
     if ( key_in1 )
        press_key = 1 << SW2_toilet_seat_temp;
    if ( key_in2 )
        press_key = 1 << SW5_stop_all;
    if ( key_in3 )
        press_key = 1 << SW8_fan_speed_temp;
    
    key_scan_out3_SetDigitalOutput ();
    key_scan_out3_SetDigitalInput ();
    key_in1 = key_scan_in1_GetValue ();
    key_in2 = key_scan_in2_GetValue ();
    if ( key_in1 )
        press_key = 1 << SW3_washing;
    if ( key_in2 )
        press_key = 1 << SW6_decrease;
 
    return press_key;
}

#ifdef debug_HT16C21
void I2C2_check_error ( I2C2_MESSAGE_STATUS status )
{
  if ( status > I2C2_MESSAGE_COMPLETE )
	  while ( 1 );
}
#endif

void remote_control_init ( void )
{
    /*void I2C2_MasterWrite(
            uint8_t *pdata,
            uint8_t length,
            uint16_t address,
            I2C2_MESSAGE_STATUS *pstatus);*/
    uint8_t i2c_data [ 10 ], i = 0;
    I2C2_MESSAGE_STATUS i2c_status = I2C2_MESSAGE_COMPLETE;
            
    i2c_data [ 0 ] = I2C_HT16C21_CMD_DRIVE_MODE;
    i2c_data [ 1 ] &= 0xFC;  //1/4 duty, 1/3 bias
    I2C2_MasterWrite ( i2c_data, 2, I2C_HT16C21_ADDRESS, &i2c_status );
#ifdef debug_HT16C21
	I2C2_check_error ( i2c_status );
#endif
    
    i2c_data [ 0 ] = I2C_HT16C21_CMD_SYSTEM_MODE;
    i2c_data [ 1 ] &= 0xFC;  //system osc & lcd on/off
    I2C2_MasterWrite ( i2c_data, 2, I2C_HT16C21_ADDRESS, &i2c_status );
#ifdef debug_HT16C21
	I2C2_check_error ( i2c_status );
#endif

    i2c_data [ 0 ] = I2C_HT16C21_CMD_FRAME_RATE;
    i2c_data [ 1 ] &= 0xFE;  //setting frame rate 80Hz
    I2C2_MasterWrite ( i2c_data, 2, I2C_HT16C21_ADDRESS, &i2c_status );
#ifdef debug_HT16C21
	I2C2_check_error ( i2c_status );
#endif

	//set whole RAM map as 1
	i2c_data [ 0 ] = I2C_HT16C21_CMD_FRAME_RATE;
	for ( i = 0; i < 10; i++ ) {
	
	}
}
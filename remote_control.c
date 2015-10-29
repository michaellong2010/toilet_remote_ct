
#include "remote_control.h"

volatile TOIET_STATE toilet_cur_state = TOIET_DUMMY_STATE,toilet_last_state = TOIET_DUMMY_STATE, toilet_next_state = TOIET_DUMMY_STATE;
/* refresh toilet state?refresh remote display?monitor rocker lock on/off and do ADC
 * pass toilet_ctrl_data to host via RF TX */
void toilet_state_action ( void ) {
    if ( toilet_cur_state !=  toilet_next_state) {
        toilet_last_state = toilet_cur_state;
        toilet_cur_state = toilet_next_state;
    }
    
    if ( toilet_cur_state == TOIET_WASHING_STATE || toilet_cur_state == TOIET_SPRAYING_STATE || toilet_cur_state == TOIET_FAN_SPEED_TEMP_STATE  ) {
        if ( rocker_lock_GetValue () ) {
        }
        else {
        }
    }
}

/* timer ISR to issue key scanning */
void issue_key_scanning ( void ) {
    //static TOIET_STATE toilet_cur_state = TOIET_DUMMY_STATE, toilet_last_state, toilet_next_state;
    static uint16_t newest_press_key = 0;
   
   //if ( toilet_last_state != toilet_cur_state )
        //toilet_last_state = toilet_cur_state;
    //toilet_next_state = toilet_cur_state;
    newest_press_key = key_scanning ();
    
    if ( !newest_press_key )
        return;
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
    
    key_scan_out2_SetDigitalOutput ();
    key_scan_out2_SetDigitalInput ();
    key_in1 = key_scan_in1_GetValue ();
    key_in2 = key_scan_in2_GetValue ();
    if ( key_in1 )
        press_key = 1 << SW3_washing;
    if ( key_in2 )
        press_key = 1 << SW6_decrease;
 
    return press_key;
}
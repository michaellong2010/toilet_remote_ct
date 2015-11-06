
#include "remote_control.h"
#include <stdbool.h>

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
    uint8_t level_index = 0;
    
    if ( toilet_cur_state !=  toilet_next_state) {
        toilet_last_state = toilet_cur_state;
        toilet_cur_state = toilet_next_state;
        toilet_ctrl_data.toilet_state = toilet_cur_state;
        is_need_refresh = true;
        
        //clear all logo display
        show_display_segment ( DISP_mode_logo [ Clear_All_Logo ], sizeof ( DISP_mode_logo [ Clear_All_Logo ] ), false );
        //display current state logo
        switch ( toilet_cur_state ) {
            case TOIET_SPRAYING_STATE:
                show_display_segment ( DISP_mode_logo [ Seat_Logo ], sizeof ( DISP_mode_logo [ Seat_Logo ] ), true );
                break;
            case TOIET_SEAT_TEMP_STATE:
                show_display_segment ( DISP_mode_logo [ Spraying_Logo ], sizeof ( DISP_mode_logo [ Spraying_Logo ] ), true );
                break;
        }
    }
    //display water&seat&fan&spray temperature level
    show_display_segment ( DISP_misc_level [ Clear_Misc_Level ], sizeof ( DISP_misc_level [ Clear_Misc_Level ] ), false );
    switch  ( toilet_cur_state ) {
        case TOIET_WATER_TEMP_STATE:
            level_index = toilet_ctrl_data.water_T_index;
            break;
        case TOIET_SEAT_TEMP_STATE:
            level_index = toilet_ctrl_data.toilet_seat_T_index;
            break;
        case TOIET_WASHING_STATE:
            level_index = toilet_ctrl_data.washing_F_index;
            break;
        case TOIET_SPRAYING_STATE:
            level_index = toilet_ctrl_data.spraying_F_index;
            break;
        case TOIET_FAN_SPEED_TEMP_STATE:
            level_index = toilet_ctrl_data.fan_T_index;
            break;
    }
    show_display_segment ( DISP_misc_level [ level_index ], sizeof ( DISP_misc_level [ level_index ] ), true );
    
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
    
    /*show_display_segment ( DISP_7SEG_5 [ Clear_7SEG ], sizeof ( DISP_7SEG_5 [ Clear_7SEG ] ), false );
    show_display_segment ( DISP_7SEG_6 [ Clear_7SEG ], sizeof ( DISP_7SEG_6 [ Clear_7SEG ] ), false );
    show_display_segment ( DISP_7SEG_5 [ Clear_7SEG ], sizeof ( DISP_7SEG_5 [ Clear_7SEG ] ), true );
    show_display_segment ( DISP_7SEG_6 [ Clear_7SEG ], sizeof ( DISP_7SEG_6 [ Clear_7SEG ] ), true );
    
    show_display_segment ( DISP_bat_level [ Clear_Bat_Level ], sizeof ( DISP_bat_level [ Clear_Bat_Level ] ), false );
    show_display_segment ( DISP_bat_level [ Clear_Bat_Level ], sizeof ( DISP_bat_level [ Clear_Bat_Level ] ), true );*/
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
    static uint16_t newest_press_key = 0, n_timer_off_count = 0;
   
   //if ( toilet_last_state != toilet_cur_state )
        //toilet_last_state = toilet_cur_state;
    //toilet_next_state = toilet_cur_state;
    newest_press_key = key_scanning ();
    
    if ( !newest_press_key ) {
        if ( n_timer_off_count <= DISPLAY_OFF_TIMER_OVERFLOW_COUNT ) {
            n_timer_off_count++;
        }
        else
            if ( n_timer_off_count == DISPLAY_OFF_TIMER_OVERFLOW_COUNT ) {
                DISPLAY_OFF ();
            }
        return;
    }
    else {
        DISPLAY_ON ();
        n_timer_off_count = 0;
    }
#ifdef debug_key_scanning
    newest_press_key = newest_press_key;
#else
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
                                           if ( toilet_ctrl_data.washing_F_index > 1 )
                                               toilet_ctrl_data.washing_F_index--;
                                       }
                                       else
                                           if ( toilet_cur_state == TOIET_FAN_SPEED_TEMP_STATE ) {
                                             //toggle fan speed
                                               if ( toilet_ctrl_data.fan_S_index )
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
                                                   if ( toilet_ctrl_data.fan_S_index )
                                                       toilet_ctrl_data.fan_S_index = 0;
                                                   else
                                                       toilet_ctrl_data.fan_S_index = 1;
                                               }
                                       }
    }
#endif    
    /*if ( toilet_cur_state != toilet_next_state ) {
        toilet_last_state = toilet_cur_state;
        toilet_cur_state = toilet_next_state;
    }*/
}

/* do key scanning */
uint16_t key_scanning ( void ) {    
    uint8_t key_in1, key_in2, key_in3;
    uint16_t press_key = 0, i = 0, j = 0, Max_Hist;
	static uint16_t key_buf [ KEY_COUNT ][ KEY_BUFFER_SIZE ], key_buf_head_index = 0, key_buf_tail_index = 0, key_buf_hist [ KEY_COUNT ] = { 0 };
	int16_t candidate_key_index = -1;
	static bool is_buf_full = false;
    
    key_scan_out1_SetDigitalOutput ();
    key_buf [ 0 ][ key_buf_tail_index ] = key_in1 = key_scan_in1_GetValue ();
    key_buf [ 1 ][ key_buf_tail_index ] = key_in2 = key_scan_in2_GetValue ();
    key_buf [ 2 ][ key_buf_tail_index ] = key_in3 = key_scan_in3_GetValue ();
    if ( key_in1 )
        press_key |= 1 << SW1_water_tank_temp;
    if ( key_in2 )
        press_key |= 1 << SW4_spraying;
    if ( key_in3 )
        press_key |= 1 << SW7_increase;
    key_scan_out1_SetDigitalInput ();
    
    key_scan_out2_SetDigitalOutput ();
    key_buf [ 3 ][ key_buf_tail_index ] = key_in1 = key_scan_in1_GetValue ();
    key_buf [ 4 ][ key_buf_tail_index ] = key_in2 = key_scan_in2_GetValue ();
    key_buf [ 5 ][ key_buf_tail_index ] = key_in3 = key_scan_in3_GetValue ();
     if ( key_in1 )
        press_key |= 1 << SW2_toilet_seat_temp;
    if ( key_in2 )
        press_key |= 1 << SW5_stop_all;
    if ( key_in3 )
        press_key |= 1 << SW8_fan_speed_temp;
    key_scan_out2_SetDigitalInput ();
    
    key_scan_out3_SetDigitalOutput ();
    key_buf [ 6 ][ key_buf_tail_index ] = key_in1 = key_scan_in1_GetValue ();
    key_buf [ 7 ][ key_buf_tail_index ] = key_in2 = key_scan_in2_GetValue ();
    if ( key_in1 )
        press_key |= 1 << SW3_washing;
    if ( key_in2 )
        press_key |= 1 << SW6_decrease;
    key_scan_out3_SetDigitalInput ();
 
#ifdef debug_key_scanning
    press_key = press_key;
#endif
	//buffer the key, examine every key histogram
	if ( key_buf_head_index < key_buf_tail_index ) {
		if ( ( key_buf_tail_index - key_buf_head_index + 1 ) ==  KEY_BUFFER_SIZE ) {
			/*for ( i = key_buf_head_index; i <= key_buf_tail_index; i++ ) {
				for ( j = 0 ; j < KEY_COUNT; j++ )
					if ( key_buf [ j ][ i ] )
						key_buf_hist [ j ]++;
			}*/
			is_buf_full = true;
		}
	}
	else
		if ( key_buf_tail_index < key_buf_head_index ) {

		}

	if ( is_buf_full == true ) {
		for ( i = 0; i < KEY_BUFFER_SIZE; i++ )
			for ( j = 0 ; j < KEY_COUNT; j++ )
				if ( key_buf [ j ][ i ] )
					key_buf_hist [ j ]++;
    }
    
	for ( i = 0, candidate_key_index = -1, Max_Hist = ( uint16_t ) ASSERT_TIMES_THRESHOLD; i < KEY_COUNT; i++ )
		if ( key_buf_hist [ i ] >= Max_Hist ) {
			Max_Hist = key_buf_hist [ i ];
			candidate_key_index = i;
		}
	if ( candidate_key_index >= 0 ) {
#ifdef debug_key_scanning
    press_key = press_key;
#endif
        press_key = 1 << candidate_key_index;
		memset ( key_buf, 0, sizeof( key_buf ) );
		memset ( key_buf_hist, 0, sizeof( key_buf_hist ) );
		key_buf_head_index = key_buf_tail_index = 0;
		is_buf_full = false;
	}
	else {
		key_buf_tail_index++;
		if ( is_buf_full == true ) {
			for ( j = 0 ; j < KEY_COUNT; j++ )
				if ( key_buf [ j ][ key_buf_head_index ] )
					key_buf_hist [ j ]--;
			key_buf_head_index++;
		}
		if ( key_buf_tail_index == KEY_BUFFER_SIZE )
			key_buf_tail_index = 0;
		if ( key_buf_head_index == KEY_BUFFER_SIZE )
			key_buf_head_index = 0;
	}
    return press_key;
}

#ifdef debug_HT16C21
void I2C2_check_error ( I2C2_MESSAGE_STATUS status )
{
  if ( status > I2C2_MESSAGE_COMPLETE )
	  while ( 1 );
}
#endif

void show_display_segment1 ( void )
{
    uint8_t i2c_data [ 12 ], i = 0;
    I2C2_MESSAGE_STATUS i2c_status = I2C2_MESSAGE_COMPLETE;
    
	i2c_data [ 0 ] = I2C_HT16C21_CMD_DISPLAY_DATA;
    i2c_data [ 1 ] = 0x00;
    memcpy ( i2c_data + 2, disp_ram_map_data, sizeof ( disp_ram_map_data ) );
    I2C2_MasterWrite ( i2c_data, 12, I2C_HT16C21_ADDRESS, &i2c_status );
    __delay_ms ( 10 );
#ifdef debug_HT16C21
	I2C2_check_error ( i2c_status );
#endif
    memset ( i2c_data + 2, 0, sizeof ( disp_ram_map_data ) );
    I2C2_MasterWrite ( i2c_data, 2, I2C_HT16C21_ADDRESS, &i2c_status );
    //__delay_ms ( 10 );
    I2C2_MasterRead ( i2c_data + 2, 10, I2C_HT16C21_ADDRESS, &i2c_status );
    //__delay_ms ( 10 );
    

    i2c_data [ 0 ] = I2C_HT16C21_CMD_SYSTEM_MODE;
    i2c_data [ 1 ] |= 0x03;  //system osc & lcd on/on
    I2C2_MasterWrite ( i2c_data, 2, I2C_HT16C21_ADDRESS, &i2c_status );
    __delay_ms ( 10 );
#ifdef debug_HT16C21
	I2C2_check_error ( i2c_status );
#endif

    i2c_data [ 0 ] = I2C_HT16C21_IVA;
    i2c_data [ 1 ] = 0x00;  //
    I2C2_MasterWrite ( i2c_data, 2, I2C_HT16C21_ADDRESS, &i2c_status );
    __delay_ms ( 10 );
#ifdef debug_HT16C21
	I2C2_check_error ( i2c_status );
#endif    
    
    i2c_data [ 0 ] = I2C_HT16C21_BLINK_FREQ;
    i2c_data [ 1 ] = 0x00;  //system osc & lcd on/off
    I2C2_MasterWrite ( i2c_data, 2, I2C_HT16C21_ADDRESS, &i2c_status );
    __delay_ms ( 10 );
#ifdef debug_HT16C21
	I2C2_check_error ( i2c_status );
#endif
    
    
}

//show or clear partial segments, segments ram map store in array
void show_display_segment ( uint8_t *disp_seg, uint8_t len, bool is_show )
{
    uint8_t i, seg_byte_index, seg_bit_pos;
    
    for ( i = 0; i < len; i++ ) {
        seg_byte_index = disp_seg[ i ] / 8; //extract segment byte index
        seg_bit_pos = disp_seg[ i ] % 8; //extract segment bit postion
        if ( is_show == true )
            disp_ram_map_data [ seg_byte_index ] |= ( 1 << seg_bit_pos ); 
        else
            disp_ram_map_data [ seg_byte_index ] &= ~( 1 << seg_bit_pos ); 
    }
}

void remote_control_init ( void )
{
    /*void I2C2_MasterWrite(
            uint8_t *pdata,
            uint8_t length,
            uint16_t address,
            I2C2_MESSAGE_STATUS *pstatus);*/
    uint8_t i2c_data [ 2 ], i = 0;
    I2C2_MESSAGE_STATUS i2c_status = I2C2_MESSAGE_COMPLETE;
#if 0         
    DISPLAY_OFF ();
    DISPLAY_ON ();
    i2c_data [ 0 ] = I2C_HT16C21_CMD_DRIVE_MODE;
    i2c_data [ 1 ] = 0x03;  //1/4 duty, 1/3 bias
    I2C2_MasterWrite ( i2c_data, 1, I2C_HT16C21_ADDRESS, &i2c_status );
    __delay_ms ( 10 );
    i2c_data [ 1 ] = 0x00;
    I2C2_MasterRead ( i2c_data + 1, 1, I2C_HT16C21_ADDRESS, &i2c_status );
    __delay_ms ( 10 );
#ifdef debug_HT16C21
     I2C2_check_error ( i2c_status );
#endif
    
    i2c_data [ 0 ] = I2C_HT16C21_CMD_SYSTEM_MODE;
    i2c_data [ 1 ] = 0x00;  //system osc & lcd on/off
    I2C2_MasterRead ( i2c_data, 2, I2C_HT16C21_ADDRESS, &i2c_status );
    __delay_ms ( 10 );
#ifdef debug_HT16C21
	I2C2_check_error ( i2c_status );
#endif

    i2c_data [ 0 ] = I2C_HT16C21_CMD_FRAME_RATE;
    i2c_data [ 1 ] &= 0xFF;  //setting frame rate 80Hz
    I2C2_MasterRead ( i2c_data, 2, I2C_HT16C21_ADDRESS, &i2c_status );
    __delay_ms ( 10 );
#ifdef debug_HT16C21
	I2C2_check_error ( i2c_status );
#endif

#ifdef debug_HT16C21
	//set whole RAM map as 1
	for ( i = 0; i < 10; i++ ) {
        if ( i %2 )
            disp_ram_map_data [ i ] = 0x00;
        else
            disp_ram_map_data [ i ] = 0xFF;
	}
    show_display_segment1 ();

    for ( i = 0; i < 10; i++ )
        __delay_ms ( 10 );
#endif

	//set whole RAM map as 0
	for ( i = 0; i < 10; i++ ) {
		disp_ram_map_data [ i ] = 0x00;
	}
    show_display_segment1 ();
    
	show_display_segment ( DISP_regular, sizeof ( DISP_regular), true );
    
    //start timer0
    TMR0_StartTimer( );
#endif
#ifdef debug_A7105_SPI
    if ( A7105_SpiTest () == true )
        while ( 1 );
#endif
}
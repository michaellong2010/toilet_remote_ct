
#include "remote_control.h"

uint16_t key_scanning ( void ) {    
    uint8_t key_in1, key_in2, key_in3;
    uint16_t press_key;
    TOIET_STATE toilet_cur_state = TOIET_DUMMY_STATE;
    
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
        press_key = 1 << SW8_blowing;
    
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
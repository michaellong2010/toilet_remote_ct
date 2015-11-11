/*
 * File:   main.c
 * Author: USER
 *
 * Created on 2015?10?27?, ?? 8:14
 */


#include <xc.h>
#include <stdio.h>
#include "A7105reg.h"
#include "remote_control.h"
#include "./mcc_generated_files//tmr0.h"
//#include "md5.h"


//#define DBG_PRINTF printf
#define DBG_PRINTF
void main(void) {
    //initRF ();
    //DBG_PRINTF ( "this is a test\n" );
    //TMR0_StartTimer ();
    /*char buf [11];
    unsigned n = 10;
    unsigned char digest[16];
    struct MD5Context md5c;
    //memcpy ( buf, "1234567890", n);
    memcpy ( buf, "12345", 3);
    MD5Init(&md5c);
    MD5Update (&md5c, (char *)buf, 3);
    MD5Final (digest, &md5c);*/
    SYSTEM_Initialize();
    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();
    
    
    //key_scan_out2_SetDigitalOutput ();
    //key_scan_out2_SetHigh ();
    //key_scan_out2_SetLow ();
    TMR0_StopTimer ();
    key_scan_out1_SetHigh();
    key_scan_out1_SetLow();
    key_scan_out2_SetHigh();
    key_scan_out2_SetLow();
    key_scan_out3_SetHigh();
    key_scan_out3_SetLow();
    __delay_ms (10);
    //key_scan_in1_SetLow();
    //key_scan_in2_SetLow();
    //key_scan_in3_SetLow();
    //TMR0_StartTimer( );
    remote_control_init ();
    while (1) {
        __delay_ms (10);
        toilet_state_action ();
    }
    //show_display_segment ( DISP_mode_logo[Clear_All_Logo], sizeof ( DISP_mode_logo[Clear_All_Logo] ), false );
    return;
}

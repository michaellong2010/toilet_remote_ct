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


//#define DBG_PRINTF printf
#define DBG_PRINTF
void main(void) {
    //initRF ();
    //DBG_PRINTF ( "this is a test\n" );
    //TMR0_StartTimer ();
    while (1)
        toilet_state_action ();
    return;
}

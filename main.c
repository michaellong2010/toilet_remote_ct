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
    
    while (1)
        toilet_state_action ();
    return;
}

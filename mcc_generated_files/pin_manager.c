/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB?Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB?Code Configurator - v2.25.2
        Device            :  PIC18F25K22
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#include <xc.h>
#include "pin_manager.h"
#include "../remote_control.h"

void PIN_MANAGER_Initialize(void) {
    LATA = 0x20;
    TRISA = 0xDF;
    ANSELA = 0x0F;

    LATB = 0x06;
    TRISB = 0xEF;
    ANSELB = 0x01;
    WPUB = 0x80;

    LATC = 0x07;
    TRISC = 0xD0;
    ANSELC = 0x00;

    INTCON2bits.nRBPU = 0x00;

    // enable interrupt-on-change individually    
    IOCB5 = 0;
    IOCB7 = 1;

    // enable interrupt-on-change globally
    INTCONbits.RBIE = 1;

}

void PIN_MANAGER_IOC(void) {
	int16_t i = 0, single_key_count = 0;

	while ( i++ < 5 )
		__delay_ms ( 10 );
    if ((IOCB5 == 1) && (RBIF == 1)) {
		i = single_key_count = 0;
		while ( i++ < 10 ) {
			if ( !rocker_lock_GetValue () )
				single_key_count++;
		}
		if ( single_key_count == 10 ) {
			toggle_lock ();
			RBIF = 0;
		}
		// clear interrupt-on-change flag
		//RBIF = 0;
	}
	//else
	if ((IOCB7 == 1) && (RBIF == 1)) {
        //@TODO Add handling code for IOC on pin RB5
		i = single_key_count = 0;
		while ( i++ < 10 ) {
			if ( !spotlight_GetValue () )
				single_key_count++;
		}
		if ( single_key_count == 10 ) {
			toggle_spotlight ();
        RBIF = 0;
		}
		//if ( !rocker_lock_GetValue () )
		//toggle_lock ();
        // clear interrupt-on-change flag
        RBIF = 0;
    }
}
/**
 End of File
 */
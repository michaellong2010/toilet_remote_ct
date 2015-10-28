/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB?Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB?Code Configurator - v2.25.2
        Device            :  PIC18F25K22
        Version           :  1.01
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set key_scan_in1 aliases
#define key_scan_in1_TRIS               TRISA4
#define key_scan_in1_LAT                LATA4
#define key_scan_in1_PORT               PORTAbits.RA4
#define key_scan_in1_SetHigh()    do { LATA4 = 1; } while(0)
#define key_scan_in1_SetLow()   do { LATA4 = 0; } while(0)
#define key_scan_in1_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define key_scan_in1_GetValue()         PORTAbits.RA4
#define key_scan_in1_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define key_scan_in1_SetDigitalOutput()   do { TRISA4 = 0; } while(0)

// get/set MSPI_CS aliases
#define MSPI_CS_TRIS               TRISA5
#define MSPI_CS_LAT                LATA5
#define MSPI_CS_PORT               PORTAbits.RA5
#define MSPI_CS_ANS                ANSA5
#define MSPI_CS_SetHigh()    do { LATA5 = 1; } while(0)
#define MSPI_CS_SetLow()   do { LATA5 = 0; } while(0)
#define MSPI_CS_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define MSPI_CS_GetValue()         PORTAbits.RA5
#define MSPI_CS_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define MSPI_CS_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define MSPI_CS_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define MSPI_CS_SetDigitalMode()   do { ANSA5 = 0; } while(0)
// get/set key_scan_in2 aliases
#define key_scan_in2_TRIS               TRISA6
#define key_scan_in2_LAT                LATA6
#define key_scan_in2_PORT               PORTAbits.RA6
#define key_scan_in2_SetHigh()    do { LATA6 = 1; } while(0)
#define key_scan_in2_SetLow()   do { LATA6 = 0; } while(0)
#define key_scan_in2_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define key_scan_in2_GetValue()         PORTAbits.RA6
#define key_scan_in2_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define key_scan_in2_SetDigitalOutput()   do { TRISA6 = 0; } while(0)

// get/set key_scan_in3 aliases
#define key_scan_in3_TRIS               TRISA7
#define key_scan_in3_LAT                LATA7
#define key_scan_in3_PORT               PORTAbits.RA7
#define key_scan_in3_SetHigh()    do { LATA7 = 1; } while(0)
#define key_scan_in3_SetLow()   do { LATA7 = 0; } while(0)
#define key_scan_in3_Toggle()   do { LATA7 = ~LATA7; } while(0)
#define key_scan_in3_GetValue()         PORTAbits.RA7
#define key_scan_in3_SetDigitalInput()    do { TRISA7 = 1; } while(0)
#define key_scan_in3_SetDigitalOutput()   do { TRISA7 = 0; } while(0)

// get/set rocker_lock aliases
#define rocker_lock_TRIS               TRISB5
#define rocker_lock_LAT                LATB5
#define rocker_lock_PORT               PORTBbits.RB5
#define rocker_lock_WPU                WPUB5
#define rocker_lock_ANS                ANSB5
#define rocker_lock_SetHigh()    do { LATB5 = 1; } while(0)
#define rocker_lock_SetLow()   do { LATB5 = 0; } while(0)
#define rocker_lock_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define rocker_lock_GetValue()         PORTBbits.RB5
#define rocker_lock_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define rocker_lock_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define rocker_lock_SetPullup()    do { WPUB5 = 1; } while(0)
#define rocker_lock_ResetPullup()   do { WPUB5 = 0; } while(0)
#define rocker_lock_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define rocker_lock_SetDigitalMode()   do { ANSB5 = 0; } while(0)
// get/set key_scan_out1 aliases
#define key_scan_out1_TRIS               TRISC0
#define key_scan_out1_LAT                LATC0
#define key_scan_out1_PORT               PORTCbits.RC0
#define key_scan_out1_SetHigh()    do { LATC0 = 1; } while(0)
#define key_scan_out1_SetLow()   do { LATC0 = 0; } while(0)
#define key_scan_out1_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define key_scan_out1_GetValue()         PORTCbits.RC0
#define key_scan_out1_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define key_scan_out1_SetDigitalOutput()   do { TRISC0 = 0; } while(0)

// get/set key_scan_out2 aliases
#define key_scan_out2_TRIS               TRISC1
#define key_scan_out2_LAT                LATC1
#define key_scan_out2_PORT               PORTCbits.RC1
#define key_scan_out2_SetHigh()    do { LATC1 = 1; } while(0)
#define key_scan_out2_SetLow()   do { LATC1 = 0; } while(0)
#define key_scan_out2_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define key_scan_out2_GetValue()         PORTCbits.RC1
#define key_scan_out2_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define key_scan_out2_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

// get/set IO_RC2 aliases
#define IO_RC2_TRIS               TRISC2
#define IO_RC2_LAT                LATC2
#define IO_RC2_PORT               PORTCbits.RC2
#define IO_RC2_ANS                ANSC2
#define IO_RC2_SetHigh()    do { LATC2 = 1; } while(0)
#define IO_RC2_SetLow()   do { LATC2 = 0; } while(0)
#define IO_RC2_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define IO_RC2_GetValue()         PORTCbits.RC2
#define IO_RC2_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define IO_RC2_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define IO_RC2_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define IO_RC2_SetDigitalMode()   do { ANSC2 = 0; } while(0)
// get/set SCK1 aliases
#define SCK1_TRIS               TRISC3
#define SCK1_LAT                LATC3
#define SCK1_PORT               PORTCbits.RC3
#define SCK1_ANS                ANSC3
#define SCK1_SetHigh()    do { LATC3 = 1; } while(0)
#define SCK1_SetLow()   do { LATC3 = 0; } while(0)
#define SCK1_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define SCK1_GetValue()         PORTCbits.RC3
#define SCK1_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define SCK1_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define SCK1_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define SCK1_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set SDI1 aliases
#define SDI1_TRIS               TRISC4
#define SDI1_LAT                LATC4
#define SDI1_PORT               PORTCbits.RC4
#define SDI1_ANS                ANSC4
#define SDI1_SetHigh()    do { LATC4 = 1; } while(0)
#define SDI1_SetLow()   do { LATC4 = 0; } while(0)
#define SDI1_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define SDI1_GetValue()         PORTCbits.RC4
#define SDI1_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define SDI1_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define SDI1_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define SDI1_SetDigitalMode()   do { ANSC4 = 0; } while(0)
// get/set SDO1 aliases
#define SDO1_TRIS               TRISC5
#define SDO1_LAT                LATC5
#define SDO1_PORT               PORTCbits.RC5
#define SDO1_ANS                ANSC5
#define SDO1_SetHigh()    do { LATC5 = 1; } while(0)
#define SDO1_SetLow()   do { LATC5 = 0; } while(0)
#define SDO1_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define SDO1_GetValue()         PORTCbits.RC5
#define SDO1_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define SDO1_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define SDO1_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define SDO1_SetDigitalMode()   do { ANSC5 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */
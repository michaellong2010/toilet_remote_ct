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

// get/set channel_AN0 aliases
#define channel_AN0_TRIS               TRISA0
#define channel_AN0_LAT                LATA0
#define channel_AN0_PORT               PORTAbits.RA0
#define channel_AN0_ANS                ANSA0
#define channel_AN0_SetHigh()    do { LATA0 = 1; } while(0)
#define channel_AN0_SetLow()   do { LATA0 = 0; } while(0)
#define channel_AN0_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define channel_AN0_GetValue()         PORTAbits.RA0
#define channel_AN0_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define channel_AN0_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define channel_AN0_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define channel_AN0_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set channel_AN1 aliases
#define channel_AN1_TRIS               TRISA1
#define channel_AN1_LAT                LATA1
#define channel_AN1_PORT               PORTAbits.RA1
#define channel_AN1_ANS                ANSA1
#define channel_AN1_SetHigh()    do { LATA1 = 1; } while(0)
#define channel_AN1_SetLow()   do { LATA1 = 0; } while(0)
#define channel_AN1_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define channel_AN1_GetValue()         PORTAbits.RA1
#define channel_AN1_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define channel_AN1_SetDigitalOutput()   do { TRISA1 = 0; } while(0)

#define channel_AN1_SetAnalogMode()   do { ANSA1 = 1; } while(0)
#define channel_AN1_SetDigitalMode()   do { ANSA1 = 0; } while(0)
// get/set channel_AN2 aliases
#define channel_AN2_TRIS               TRISA2
#define channel_AN2_LAT                LATA2
#define channel_AN2_PORT               PORTAbits.RA2
#define channel_AN2_ANS                ANSA2
#define channel_AN2_SetHigh()    do { LATA2 = 1; } while(0)
#define channel_AN2_SetLow()   do { LATA2 = 0; } while(0)
#define channel_AN2_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define channel_AN2_GetValue()         PORTAbits.RA2
#define channel_AN2_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define channel_AN2_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define channel_AN2_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define channel_AN2_SetDigitalMode()   do { ANSA2 = 0; } while(0)
// get/set channel_AN3 aliases
#define channel_AN3_TRIS               TRISA3
#define channel_AN3_LAT                LATA3
#define channel_AN3_PORT               PORTAbits.RA3
#define channel_AN3_ANS                ANSA3
#define channel_AN3_SetHigh()    do { LATA3 = 1; } while(0)
#define channel_AN3_SetLow()   do { LATA3 = 0; } while(0)
#define channel_AN3_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define channel_AN3_GetValue()         PORTAbits.RA3
#define channel_AN3_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define channel_AN3_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define channel_AN3_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define channel_AN3_SetDigitalMode()   do { ANSA3 = 0; } while(0)
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
// get/set key_scan_in3 aliases
#define key_scan_in3_TRIS               TRISA6
#define key_scan_in3_LAT                LATA6
#define key_scan_in3_PORT               PORTAbits.RA6
#define key_scan_in3_SetHigh()    do { LATA6 = 1; } while(0)
#define key_scan_in3_SetLow()   do { LATA6 = 0; } while(0)
#define key_scan_in3_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define key_scan_in3_GetValue()         PORTAbits.RA6
#define key_scan_in3_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define key_scan_in3_SetDigitalOutput()   do { TRISA6 = 0; } while(0)

// get/set key_scan_in2 aliases
#define key_scan_in2_TRIS               TRISA7
#define key_scan_in2_LAT                LATA7
#define key_scan_in2_PORT               PORTAbits.RA7
#define key_scan_in2_SetHigh()    do { LATA7 = 1; } while(0)
#define key_scan_in2_SetLow()   do { LATA7 = 0; } while(0)
#define key_scan_in2_Toggle()   do { LATA7 = ~LATA7; } while(0)
#define key_scan_in2_GetValue()         PORTAbits.RA7
#define key_scan_in2_SetDigitalInput()    do { TRISA7 = 1; } while(0)
#define key_scan_in2_SetDigitalOutput()   do { TRISA7 = 0; } while(0)

// get/set SCL2 aliases
#define SCL2_TRIS               TRISB1
#define SCL2_LAT                LATB1
#define SCL2_PORT               PORTBbits.RB1
#define SCL2_WPU                WPUB1
#define SCL2_ANS                ANSB1
#define SCL2_SetHigh()    do { LATB1 = 1; } while(0)
#define SCL2_SetLow()   do { LATB1 = 0; } while(0)
#define SCL2_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define SCL2_GetValue()         PORTBbits.RB1
#define SCL2_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define SCL2_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define SCL2_SetPullup()    do { WPUB1 = 1; } while(0)
#define SCL2_ResetPullup()   do { WPUB1 = 0; } while(0)
#define SCL2_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define SCL2_SetDigitalMode()   do { ANSB1 = 0; } while(0)
// get/set SDA2 aliases
#define SDA2_TRIS               TRISB2
#define SDA2_LAT                LATB2
#define SDA2_PORT               PORTBbits.RB2
#define SDA2_WPU                WPUB2
#define SDA2_ANS                ANSB2
#define SDA2_SetHigh()    do { LATB2 = 1; } while(0)
#define SDA2_SetLow()   do { LATB2 = 0; } while(0)
#define SDA2_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define SDA2_GetValue()         PORTBbits.RB2
#define SDA2_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define SDA2_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define SDA2_SetPullup()    do { WPUB2 = 1; } while(0)
#define SDA2_ResetPullup()   do { WPUB2 = 0; } while(0)
#define SDA2_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define SDA2_SetDigitalMode()   do { ANSB2 = 0; } while(0)
// get/set env_temp_en aliases
#define env_temp_en_TRIS               TRISB3
#define env_temp_en_LAT                LATB3
#define env_temp_en_PORT               PORTBbits.RB3
#define env_temp_en_WPU                WPUB3
#define env_temp_en_ANS                ANSB3
#define env_temp_en_SetHigh()    do { LATB3 = 1; } while(0)
#define env_temp_en_SetLow()   do { LATB3 = 0; } while(0)
#define env_temp_en_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define env_temp_en_GetValue()         PORTBbits.RB3
#define env_temp_en_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define env_temp_en_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define env_temp_en_SetPullup()    do { WPUB3 = 1; } while(0)
#define env_temp_en_ResetPullup()   do { WPUB3 = 0; } while(0)
#define env_temp_en_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define env_temp_en_SetDigitalMode()   do { ANSB3 = 0; } while(0)
// get/set backlight aliases
#define backlight_TRIS               TRISB4
#define backlight_LAT                LATB4
#define backlight_PORT               PORTBbits.RB4
#define backlight_WPU                WPUB4
#define backlight_ANS                ANSB4
#define backlight_SetHigh()    do { LATB4 = 1; } while(0)
#define backlight_SetLow()   do { LATB4 = 0; } while(0)
#define backlight_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define backlight_GetValue()         PORTBbits.RB4
#define backlight_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define backlight_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define backlight_SetPullup()    do { WPUB4 = 1; } while(0)
#define backlight_ResetPullup()   do { WPUB4 = 0; } while(0)
#define backlight_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define backlight_SetDigitalMode()   do { ANSB4 = 0; } while(0)
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

// get/set key_scan_out3 aliases
#define key_scan_out3_TRIS               TRISC2
#define key_scan_out3_LAT                LATC2
#define key_scan_out3_PORT               PORTCbits.RC2
#define key_scan_out3_ANS                ANSC2
#define key_scan_out3_SetHigh()    do { LATC2 = 1; } while(0)
#define key_scan_out3_SetLow()   do { LATC2 = 0; } while(0)
#define key_scan_out3_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define key_scan_out3_GetValue()         PORTCbits.RC2
#define key_scan_out3_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define key_scan_out3_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define key_scan_out3_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define key_scan_out3_SetDigitalMode()   do { ANSC2 = 0; } while(0)
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
// get/set TX1 aliases
#define TX1_TRIS               TRISC6
#define TX1_LAT                LATC6
#define TX1_PORT               PORTCbits.RC6
#define TX1_ANS                ANSC6
#define TX1_SetHigh()    do { LATC6 = 1; } while(0)
#define TX1_SetLow()   do { LATC6 = 0; } while(0)
#define TX1_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define TX1_GetValue()         PORTCbits.RC6
#define TX1_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define TX1_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

#define TX1_SetAnalogMode()   do { ANSC6 = 1; } while(0)
#define TX1_SetDigitalMode()   do { ANSC6 = 0; } while(0)
// get/set RX1 aliases
#define RX1_TRIS               TRISC7
#define RX1_LAT                LATC7
#define RX1_PORT               PORTCbits.RC7
#define RX1_ANS                ANSC7
#define RX1_SetHigh()    do { LATC7 = 1; } while(0)
#define RX1_SetLow()   do { LATC7 = 0; } while(0)
#define RX1_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define RX1_GetValue()         PORTCbits.RC7
#define RX1_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define RX1_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define RX1_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define RX1_SetDigitalMode()   do { ANSC7 = 0; } while(0)

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
/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.26
        Device            :  PIC16LF1829
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

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

// get/set SEGL3 aliases
#define SEGL3_TRIS               TRISAbits.TRISA1
#define SEGL3_LAT                LATAbits.LATA1
#define SEGL3_PORT               PORTAbits.RA1
#define SEGL3_WPU                WPUAbits.WPUA1
#define SEGL3_ANS                ANSELAbits.ANSA1
#define SEGL3_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define SEGL3_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define SEGL3_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define SEGL3_GetValue()           PORTAbits.RA1
#define SEGL3_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define SEGL3_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define SEGL3_SetPullup()      do { WPUAbits.WPUA1 = 1; } while(0)
#define SEGL3_ResetPullup()    do { WPUAbits.WPUA1 = 0; } while(0)
#define SEGL3_SetAnalogMode()  do { ANSELAbits.ANSA1 = 1; } while(0)
#define SEGL3_SetDigitalMode() do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set CDL3 aliases
#define CDL3_TRIS               TRISAbits.TRISA2
#define CDL3_LAT                LATAbits.LATA2
#define CDL3_PORT               PORTAbits.RA2
#define CDL3_WPU                WPUAbits.WPUA2
#define CDL3_ANS                ANSELAbits.ANSA2
#define CDL3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define CDL3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define CDL3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define CDL3_GetValue()           PORTAbits.RA2
#define CDL3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define CDL3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define CDL3_SetPullup()      do { WPUAbits.WPUA2 = 1; } while(0)
#define CDL3_ResetPullup()    do { WPUAbits.WPUA2 = 0; } while(0)
#define CDL3_SetAnalogMode()  do { ANSELAbits.ANSA2 = 1; } while(0)
#define CDL3_SetDigitalMode() do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set SEGDP aliases
#define SEGDP_TRIS               TRISAbits.TRISA4
#define SEGDP_LAT                LATAbits.LATA4
#define SEGDP_PORT               PORTAbits.RA4
#define SEGDP_WPU                WPUAbits.WPUA4
#define SEGDP_ANS                ANSELAbits.ANSA4
#define SEGDP_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SEGDP_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SEGDP_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SEGDP_GetValue()           PORTAbits.RA4
#define SEGDP_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SEGDP_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define SEGDP_SetPullup()      do { WPUAbits.WPUA4 = 1; } while(0)
#define SEGDP_ResetPullup()    do { WPUAbits.WPUA4 = 0; } while(0)
#define SEGDP_SetAnalogMode()  do { ANSELAbits.ANSA4 = 1; } while(0)
#define SEGDP_SetDigitalMode() do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set CD4 aliases
#define CD4_TRIS               TRISAbits.TRISA5
#define CD4_LAT                LATAbits.LATA5
#define CD4_PORT               PORTAbits.RA5
#define CD4_WPU                WPUAbits.WPUA5
#define CD4_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define CD4_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define CD4_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define CD4_GetValue()           PORTAbits.RA5
#define CD4_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define CD4_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define CD4_SetPullup()      do { WPUAbits.WPUA5 = 1; } while(0)
#define CD4_ResetPullup()    do { WPUAbits.WPUA5 = 0; } while(0)

// get/set SEGA aliases
#define SEGA_TRIS               TRISBbits.TRISB4
#define SEGA_LAT                LATBbits.LATB4
#define SEGA_PORT               PORTBbits.RB4
#define SEGA_WPU                WPUBbits.WPUB4
#define SEGA_ANS                ANSELBbits.ANSB4
#define SEGA_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define SEGA_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define SEGA_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define SEGA_GetValue()           PORTBbits.RB4
#define SEGA_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define SEGA_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define SEGA_SetPullup()      do { WPUBbits.WPUB4 = 1; } while(0)
#define SEGA_ResetPullup()    do { WPUBbits.WPUB4 = 0; } while(0)
#define SEGA_SetAnalogMode()  do { ANSELBbits.ANSB4 = 1; } while(0)
#define SEGA_SetDigitalMode() do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set SEGG aliases
#define SEGG_TRIS               TRISBbits.TRISB5
#define SEGG_LAT                LATBbits.LATB5
#define SEGG_PORT               PORTBbits.RB5
#define SEGG_WPU                WPUBbits.WPUB5
#define SEGG_ANS                ANSELBbits.ANSB5
#define SEGG_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define SEGG_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define SEGG_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define SEGG_GetValue()           PORTBbits.RB5
#define SEGG_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define SEGG_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define SEGG_SetPullup()      do { WPUBbits.WPUB5 = 1; } while(0)
#define SEGG_ResetPullup()    do { WPUBbits.WPUB5 = 0; } while(0)
#define SEGG_SetAnalogMode()  do { ANSELBbits.ANSB5 = 1; } while(0)
#define SEGG_SetDigitalMode() do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set SEGB aliases
#define SEGB_TRIS               TRISBbits.TRISB6
#define SEGB_LAT                LATBbits.LATB6
#define SEGB_PORT               PORTBbits.RB6
#define SEGB_WPU                WPUBbits.WPUB6
#define SEGB_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define SEGB_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define SEGB_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define SEGB_GetValue()           PORTBbits.RB6
#define SEGB_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define SEGB_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define SEGB_SetPullup()      do { WPUBbits.WPUB6 = 1; } while(0)
#define SEGB_ResetPullup()    do { WPUBbits.WPUB6 = 0; } while(0)

// get/set CD1 aliases
#define CD1_TRIS               TRISBbits.TRISB7
#define CD1_LAT                LATBbits.LATB7
#define CD1_PORT               PORTBbits.RB7
#define CD1_WPU                WPUBbits.WPUB7
#define CD1_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define CD1_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define CD1_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define CD1_GetValue()           PORTBbits.RB7
#define CD1_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define CD1_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define CD1_SetPullup()      do { WPUBbits.WPUB7 = 1; } while(0)
#define CD1_ResetPullup()    do { WPUBbits.WPUB7 = 0; } while(0)

// get/set SEGF aliases
#define SEGF_TRIS               TRISCbits.TRISC0
#define SEGF_LAT                LATCbits.LATC0
#define SEGF_PORT               PORTCbits.RC0
#define SEGF_WPU                WPUCbits.WPUC0
#define SEGF_ANS                ANSELCbits.ANSC0
#define SEGF_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define SEGF_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define SEGF_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define SEGF_GetValue()           PORTCbits.RC0
#define SEGF_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define SEGF_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define SEGF_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define SEGF_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define SEGF_SetAnalogMode()  do { ANSELCbits.ANSC0 = 1; } while(0)
#define SEGF_SetDigitalMode() do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set SEGL1L2 aliases
#define SEGL1L2_TRIS               TRISCbits.TRISC1
#define SEGL1L2_LAT                LATCbits.LATC1
#define SEGL1L2_PORT               PORTCbits.RC1
#define SEGL1L2_WPU                WPUCbits.WPUC1
#define SEGL1L2_ANS                ANSELCbits.ANSC1
#define SEGL1L2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define SEGL1L2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define SEGL1L2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define SEGL1L2_GetValue()           PORTCbits.RC1
#define SEGL1L2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SEGL1L2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define SEGL1L2_SetPullup()      do { WPUCbits.WPUC1 = 1; } while(0)
#define SEGL1L2_ResetPullup()    do { WPUCbits.WPUC1 = 0; } while(0)
#define SEGL1L2_SetAnalogMode()  do { ANSELCbits.ANSC1 = 1; } while(0)
#define SEGL1L2_SetDigitalMode() do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SEGC aliases
#define SEGC_TRIS               TRISCbits.TRISC2
#define SEGC_LAT                LATCbits.LATC2
#define SEGC_PORT               PORTCbits.RC2
#define SEGC_WPU                WPUCbits.WPUC2
#define SEGC_ANS                ANSELCbits.ANSC2
#define SEGC_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SEGC_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SEGC_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SEGC_GetValue()           PORTCbits.RC2
#define SEGC_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SEGC_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SEGC_SetPullup()      do { WPUCbits.WPUC2 = 1; } while(0)
#define SEGC_ResetPullup()    do { WPUCbits.WPUC2 = 0; } while(0)
#define SEGC_SetAnalogMode()  do { ANSELCbits.ANSC2 = 1; } while(0)
#define SEGC_SetDigitalMode() do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set CDL1L2 aliases
#define CDL1L2_TRIS               TRISCbits.TRISC3
#define CDL1L2_LAT                LATCbits.LATC3
#define CDL1L2_PORT               PORTCbits.RC3
#define CDL1L2_WPU                WPUCbits.WPUC3
#define CDL1L2_ANS                ANSELCbits.ANSC3
#define CDL1L2_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define CDL1L2_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define CDL1L2_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define CDL1L2_GetValue()           PORTCbits.RC3
#define CDL1L2_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define CDL1L2_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define CDL1L2_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define CDL1L2_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define CDL1L2_SetAnalogMode()  do { ANSELCbits.ANSC3 = 1; } while(0)
#define CDL1L2_SetDigitalMode() do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SEGE aliases
#define SEGE_TRIS               TRISCbits.TRISC4
#define SEGE_LAT                LATCbits.LATC4
#define SEGE_PORT               PORTCbits.RC4
#define SEGE_WPU                WPUCbits.WPUC4
#define SEGE_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SEGE_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SEGE_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SEGE_GetValue()           PORTCbits.RC4
#define SEGE_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SEGE_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SEGE_SetPullup()      do { WPUCbits.WPUC4 = 1; } while(0)
#define SEGE_ResetPullup()    do { WPUCbits.WPUC4 = 0; } while(0)

// get/set CD3 aliases
#define CD3_TRIS               TRISCbits.TRISC5
#define CD3_LAT                LATCbits.LATC5
#define CD3_PORT               PORTCbits.RC5
#define CD3_WPU                WPUCbits.WPUC5
#define CD3_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define CD3_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define CD3_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define CD3_GetValue()           PORTCbits.RC5
#define CD3_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define CD3_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define CD3_SetPullup()      do { WPUCbits.WPUC5 = 1; } while(0)
#define CD3_ResetPullup()    do { WPUCbits.WPUC5 = 0; } while(0)

// get/set SEGD aliases
#define SEGD_TRIS               TRISCbits.TRISC6
#define SEGD_LAT                LATCbits.LATC6
#define SEGD_PORT               PORTCbits.RC6
#define SEGD_WPU                WPUCbits.WPUC6
#define SEGD_ANS                ANSELCbits.ANSC6
#define SEGD_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define SEGD_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define SEGD_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define SEGD_GetValue()           PORTCbits.RC6
#define SEGD_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define SEGD_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define SEGD_SetPullup()      do { WPUCbits.WPUC6 = 1; } while(0)
#define SEGD_ResetPullup()    do { WPUCbits.WPUC6 = 0; } while(0)
#define SEGD_SetAnalogMode()  do { ANSELCbits.ANSC6 = 1; } while(0)
#define SEGD_SetDigitalMode() do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set CD2 aliases
#define CD2_TRIS               TRISCbits.TRISC7
#define CD2_LAT                LATCbits.LATC7
#define CD2_PORT               PORTCbits.RC7
#define CD2_WPU                WPUCbits.WPUC7
#define CD2_ANS                ANSELCbits.ANSC7
#define CD2_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define CD2_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define CD2_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define CD2_GetValue()           PORTCbits.RC7
#define CD2_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define CD2_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define CD2_SetPullup()      do { WPUCbits.WPUC7 = 1; } while(0)
#define CD2_ResetPullup()    do { WPUCbits.WPUC7 = 0; } while(0)
#define CD2_SetAnalogMode()  do { ANSELCbits.ANSC7 = 1; } while(0)
#define CD2_SetDigitalMode() do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

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
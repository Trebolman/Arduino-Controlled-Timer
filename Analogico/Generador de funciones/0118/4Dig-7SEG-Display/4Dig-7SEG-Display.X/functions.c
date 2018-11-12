/* 
 * File:   functions.c
 * Author: Mike
 *
 * This file contains all the useful functions to be used by the main application
 * 
 * Created on November 1, 2017, 4:59 PM
 */

#pragma switch simple

#include "mcc_generated_files/mcc.h"
#include "functions.h"


uint8_t digit1 = 1;
uint8_t digit1val = 1;
uint8_t digit2 = 2;
uint8_t digit2val = 7;
uint8_t digit3 = 3;
uint8_t digit3val = 0;
uint8_t digit4 = 4;
uint8_t digit4val = 0;
uint8_t delaytime = 10;

uint8_t minutes = 8;
uint8_t tenminutes = 0;
uint8_t hours = 7;
uint8_t tenhours = 1;

uint8_t maxseconds = 60;
uint8_t maxminutes = 10;
uint8_t maxtenminutes = 6;
uint8_t maxhours = 10;
uint8_t maxtenhours = 3;


uint8_t displayNumber(uint8_t number) {
        
    clrNumber();
    
    SEGL1L2_SetHigh();
    
    switch(number) {
        case 0:           // a,b,c,d,e,f
            SEGA_SetHigh();
            SEGB_SetHigh();
            SEGC_SetHigh();
            SEGD_SetHigh();
            SEGE_SetHigh();
            SEGF_SetHigh();
            SEGG_SetLow();
            break;
        
        case 1:            // b,c
            SEGA_SetLow();
            SEGB_SetHigh();
            SEGC_SetHigh();
            SEGD_SetLow();
            SEGE_SetLow();
            SEGF_SetLow();
            SEGG_SetLow();
            break;

        case 2:            // a,b,g,e,d
            SEGA_SetHigh();
            SEGB_SetHigh();
            SEGC_SetLow();
            SEGD_SetHigh();
            SEGE_SetHigh();
            SEGF_SetLow();
            SEGG_SetHigh();
            break;

        case 3:            // a,b,g,c,d
            SEGA_SetHigh();
            SEGB_SetHigh();
            SEGC_SetHigh();
            SEGD_SetHigh();
            SEGE_SetLow();
            SEGF_SetLow();
            SEGG_SetHigh();
            break;
        
        case 4:            //f,b,g,c
            SEGA_SetLow();
            SEGB_SetHigh();
            SEGC_SetHigh();
            SEGD_SetLow();
            SEGE_SetLow();
            SEGF_SetHigh();
            SEGG_SetHigh();
            break;
        
        case 5:            // a,f,g,c,d
            SEGA_SetHigh();
            SEGB_SetLow();
            SEGC_SetHigh();
            SEGD_SetHigh();
            SEGE_SetLow();
            SEGF_SetHigh();
            SEGG_SetHigh();
            break;
         
        case 6:            // a,f,g,e,c,d
            SEGA_SetHigh();
            SEGB_SetLow();
            SEGC_SetHigh();
            SEGD_SetHigh();
            SEGE_SetHigh();
            SEGF_SetHigh();
            SEGG_SetHigh();
            break;

        case 7:            // a,b,c
            SEGA_SetHigh();
            SEGB_SetHigh();
            SEGC_SetHigh();
            SEGD_SetLow();
            SEGE_SetLow();
            SEGF_SetLow();
            SEGG_SetLow();
            break;

        case 8:            // a,b,c,d,e,f,g
            SEGA_SetHigh();
            SEGB_SetHigh();
            SEGC_SetHigh();
            SEGD_SetHigh();
            SEGE_SetHigh();
            SEGF_SetHigh();
            SEGG_SetHigh();
            break;

        case 9:            // a,b,f,g,c
            SEGA_SetHigh();
            SEGB_SetHigh();
            SEGC_SetHigh();
            SEGD_SetLow();
            SEGE_SetLow();
            SEGF_SetHigh();
            SEGG_SetHigh();
            break;

        default:            // show E for ERROR a,f,g,e,d
            SEGA_SetHigh();
            SEGB_SetLow();
            SEGC_SetLow();
            SEGD_SetHigh();
            SEGE_SetHigh();
            SEGF_SetHigh();
            SEGG_SetHigh();
            break;
                     }
    
    return 1;
}

uint8_t clrNumber(void) {
    SEGA_SetLow();
    SEGB_SetLow();
    SEGC_SetLow();
    SEGD_SetLow();
    SEGE_SetLow();
    SEGF_SetLow();
    SEGG_SetLow();
    SEGL1L2_SetLow();
    
    return 1;
}


uint8_t displayDigit(uint8_t digit, uint8_t number) {
    // Need a function that selects a digit and a number and displays them
    
    clearDigits();
    displayNumber(number);
    CDL1L2_SetLow();
    
    switch(digit) {
        case 1: CD1_SetLow(); break;
        case 2: CD2_SetLow(); break;
        case 3: CD3_SetLow(); break;
        case 4: CD4_SetLow(); break;
        default: clearDigits(); break;
    }
    
    return 1;
}
        
uint8_t clearDigits() {
    CD1_SetHigh();
    CD2_SetHigh();
    CD3_SetHigh();
    CD4_SetHigh();
    CDL1L2_SetHigh();
    
    return 1;
}

uint8_t updateDigits(void) {

    displayDigit(digit1, digit1val);
    __delay_us(10);
    displayDigit(digit2, digit2val);
    __delay_us(10);
    displayDigit(digit3, digit3val);
    __delay_us(10);
    displayDigit(digit4, digit4val);
    __delay_us(10);     
    
    return 1;
}

uint8_t updateTime(void) {
        
    minutes++;
    seconds = 0;
    
    if(minutes >= maxminutes) {
        tenminutes++;
        minutes = 0;
    }
    if(tenminutes >= maxtenminutes) {
        hours++;
        tenminutes = 0;
        minutes = 0;
    }
    if(hours >= maxhours) {
        tenhours++;
        hours = 0;
        tenminutes = 0;
        minutes = 0;
    } 
    if(((tenhours >= 2) && (hours >= 4)) || (tenhours > 2)) {
        tenhours = 0;
        hours = 0;
        tenminutes = 0;
        minutes = 0;
    }
    
    digit4val = minutes;
    digit3val = tenminutes;
    digit2val = hours;
    digit1val = tenhours;
}
/* 
 * File:   functions.h
 * Author: Mike
 *
 * Created on November 1, 2017, 4:59 PM
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
extern volatile uint8_t seconds;
extern volatile uint8_t half_second;

// Define new functions here
uint8_t displayNumber(uint8_t number);
uint8_t clrNumber(void);
uint8_t displayDigit(uint8_t digit, uint8_t number);
uint8_t clearDigits();
uint8_t updateDigits(void);
uint8_t updateTime(void);

#ifdef	__cplusplus
}
#endif

#endif	/* FUNCTIONS_H */


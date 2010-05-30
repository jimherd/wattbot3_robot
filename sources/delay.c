/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        delay.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#include "global.h"

//***********************************************************************
//** Function:      delay_10us
//** 
//** Description:   10uS loop counter delay
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************  
void delay_10us()
{
uint8_t n;

    for (n=0 ; n<14 ; n++) {
        asm("nop");
        asm("nop");
    }
}

//***********************************************************************
//** Function:      delay_100us
//** 
//** Description:   100uS loop counter delay
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************  
void delay_100us(void)
{
uint8_t n;

    for (n=0 ; n<141 ; n++) {
        asm("nop");
        asm("nop");
    }
}

//***********************************************************************
//** Function:      delay_1ms
//** 
//** Description:   1ms loop counter delay
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************  
void delay_1ms(void)
{
uint8_t n;

    for (n=0 ; n<10 ; n++) {
        delay_100us();
    }
}

//***********************************************************************
//** Function:      delay a number of milliseconds
//** 
//** Description:   
//**
//** Parameters:    Count : number of milliseconds (0->255)
//** Returns:       None
//***********************************************************************  
void delay_ms(uint8_t count)
{
uint8_t  n;

    if (count == 0) {
        return;
    }
    for (n=0 ; n < count ; n++) {
        delay_1ms();
    }
}

//***********************************************************************
//** Function:      delay_1ms
//** 
//** Description:   250ms loop counter delay
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************  
void delay_250ms()
{
uint8_t n;

    for (n=0 ; n<250 ; n++) {
        delay_1ms();
    }
}




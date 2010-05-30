/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        isr.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Interupt service routine
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 * Jim Herd              02/07/2009    added RTI first level interrupt handler 
 ************************************************************************/

#include "global.h"
#include "pindef.h"

#include "cypusb.h"

/*
Interrupt Definitions
VectorNumber_Vrti               25
VectorNumber_Viic1              24
VectorNumber_Vadc1              23
VectorNumber_Vkeyboard1         22
VectorNumber_Vsci2tx            21
VectorNumber_Vsci2rx            20
VectorNumber_Vsci2err           19
VectorNumber_Vsci1tx            18
VectorNumber_Vsci1rx            17
VectorNumber_Vsci1err           16
VectorNumber_Vspi1              15
VectorNumber_Vtpm2ovf           14
VectorNumber_Vtpm2ch1           13
VectorNumber_Vtpm2ch0           12
VectorNumber_Vtpm1ovf           11
VectorNumber_Vtpm1ch5           10
VectorNumber_Vtpm1ch4           9
VectorNumber_Vtpm1ch3           8
VectorNumber_Vtpm1ch2           7
VectorNumber_Vtpm1ch1           6
VectorNumber_Vtpm1ch0           5
VectorNumber_Vicg               4
VectorNumber_Vlvd               3
VectorNumber_Virq               2
VectorNumber_Vswi               1
VectorNumber_Vreset             0
*/

//***********************************************************************
//** Function:      Vsci1rx
//** 
//** Description:   SCI1 receive interrupt vector
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************
interrupt VectorNumber_Vsci1rx void Vsci1rx1(void)
{
  asm("nop");
}

//***********************************************************************
//** Function:      Vkeyboard1
//** 
//** Description:   Vkeyboard1 interrupt vector
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************
interrupt VectorNumber_Vkeyboard1 void Vkeyboard11(void)
{
    asm("nop");
}

//***********************************************************************
//** Function:      Virq
//** 
//** Description:   Virq interrupt vector
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************
interrupt VectorNumber_Virq void Virq1(void)
{

    do{
        radio_rx_isr();
        IRQSC_IRQACK = 1;
    } while(IRQSC_IRQF);     
}

//----------------------------------------------------------------------------
// Vrti   first level interrupt handler for RTI interrupt.
// ====
// 
// 1. Acknowledge RTI interrupt.
// 2. Call interrupt service routine
//----------------------------------------------------------------------------

interrupt VectorNumber_Vrti void Vrti1(void){

    SRTISC_RTIACK = 1;                   /* Reset real-time interrupt request flag */
    rti_isr();
}
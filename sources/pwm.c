/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        pwm.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  PWM driver 
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 * Jim Herd               1/06/209     Update to use new H-bridge chips
 ************************************************************************/

#include "global.h"
#include "pwm.h"

//***********************************************************************
//** Function:      pwm0_duty
//** 
//** Description:   Sets switch value of given channel on TPM1
//**
//** Parameters:    char chan - PWM channel to change 
//**                int duty  - New switch value
//** Returns:       None
//***********************************************************************
//void pwm0_duty(char chan, int duty){
//  switch(chan){    
//    case 0:  TPM1C0V = duty; break; 
//    case 1:  TPM1C1V = duty; break; 
//    case 2:  TPM1C2V = duty; break; 
//    case 3:  TPM1C3V = duty; break; 
//    default: break;
//  }
//}

//***********************************************************************
//** Function:      pwm1_duty
//** 
//** Description:   Sets switch value of given channel on TPM2
//**
//** Parameters:    char chan - PWM channel to change 
//**                int duty  - New switch value
//** Returns:       None
//***********************************************************************
void pwm2_duty(uint8_t chan, uint16_t duty)
{
    switch(chan){    
        case 0:  TPM2C0V = duty; break; 
        case 1:  TPM2C1V = duty; break; 
        default: break;
    }
}





// old code


//***********************************************************************
//** Function:      init_pwm
//** 
//** Description:   Initialises the PWM module 
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************
//void init_pwm(){
//  /* ### Init_TPM1 init code */
//  TPM1SC = 0x00;                       /* Stop and reset counter */
// 
//  TPM1MOD = 0x0C36;                    /* Period value setting */
//  TPM1C0V = 0x00DF;                    /* Compare 0 value setting */
//  TPM1C1V = 0x00DF;                    /* Compare 1 value setting */
//  TPM1C3V = 0x00DF;                    /* Compare 2 value setting */
//  TPM1C4V = 0x00DF;                    /* Compare 3 value setting */
// 
//  TPM1C0SC = 0x28;                     /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
//  TPM1C1SC = 0x28;                     /* Int. flag clearing (2nd part) and channel 1 contr. register setting */
//  TPM1C2SC = 0x28;                     /* Int. flag clearing (2nd part) and channel 2 contr. register setting */
//  TPM1C3SC = 0x28;                     /* Int. flag clearing (2nd part) and channel 3 contr. register setting */
//  
//  /* TPM2SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=1,PS1=1,PS0=1 */
//  TPM1SC = 0x0F;                       /* Int. flag clearing (2nd part) and timer control register setting */
//
//  /* ### Init_TPM2 init code */
//  TPM2SC = 0x00;                      /* Stop and reset counter */
//  
//  TPM2MOD = 0x007F;                   /* Period value setting */
//  TPM2C0V = 0x0000;                   /* Compare 0 value setting */
//  TPM2C1V = 0x0000;                   /* Compare 1 value setting */  
//  
//  TPM2C0SC = 0x28;                    /* Int. flag clearing (2nd part) and channel 0 contr. register setting */
//  TPM2C1SC = 0x28;                    /* Int. flag clearing (2nd part) and channel 1 contr. register setting */  
//  
//  /* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=1,PS1=1,PS0=1 */
//  TPM2SC = 0x0F;                      /* Int. flag clearing (2nd part) and timer control register setting */
//}

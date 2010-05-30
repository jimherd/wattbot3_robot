/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        servo.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Servo driver
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/
 
#include "global.h"

//***********************************************************************
//** Function:      servo_pos
//** Description:   Sets servo position
//** Parameters:    char num - Servo to move (0->3)
//**                char pos - New position (0->14)
//** Returns:       None
//***********************************************************************
void servo_pos(char num, char pos)
{
  
const uint16_t position[]={156,167,179,190,201,212,223,234,246,257,268,279,290,301,313};

    if (pos > (sizeof(position)/2)) {
        pos= (sizeof(position)/2) - 1;
    }
    pwm2_duty(num, position[pos]);
}
 
 
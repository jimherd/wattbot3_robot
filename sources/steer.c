/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        steer.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:      
 *************************************************************************
 * File description:
 *  Servo driver
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Jim Herd             28/05/2010    Original.
 ************************************************************************/
 
#include "global.h"

//----------------------------------------------------------------------------
// table of values to map joystick reading to % full speed
//
//const uint8_t joystick_to_speed[32] = {
//    0,0,20,22,24,26,28,30,33,36,39,41,44,47,50,53,56,59,62,65,68,71,74,77,81,85,88,91,94,97,100,100     
//};
const uint8_t joystick_to_speed[32] = {
    0,30,30,30,30,30,30,30,30,30,30,30,30,40,40,40,40,40,40,40,40,40,45,50,55,60,65,70,75,80,85,100     
};

//***********************************************************************
//** Function:      steer_mode_A
//** Description:   Calc motor commands for skid steering mode
//** Parameters:    psx_data - Data packet from PS2 controller
//**                m_data   - motor data 
//** Returns:       None
//***********************************************************************

void steer_mode_A(psx_map  *psx_data, motor_data  *m_data) 
{
    
//
// adjust motors based on "y-value" of left and right joysticks
//
//  0->255   :: 255 = full speed reverse, 0 = full speed forward , 128 = off
//
//  1. Convert 0->255 range of joystick pot to 0->63 (right shift by 2)
//  2. 0->31 defines forward speed ;  31=full speed ; 0 = off
//      a. convert to 31->0
//  3. 32->63 defines forward speed ; 32=off ;        63 = full speed
//      a. convert to 0->31         ;  0=off ;        31 = full speed
//
// compute left motor control
//
    m_data->left_speed = psx_data->joy_left_y;
    m_data->left_speed = (m_data->left_speed >> 2) & 0x3F;
    if (m_data->left_speed > 31) {
        m_data->left_motor_mode = MOTOR_BACKWARD;
        m_data->left_speed = m_data->left_speed - 32;              // convert 32->63  to   0->31
    } else {        
        m_data->left_motor_mode = MOTOR_FORWARD;      
        m_data->left_speed = ((~m_data->left_speed) & 0x1F);       // convert 31->0   to   0->31
    }
    m_data->left_speed = joystick_to_speed[m_data->left_speed];
    if (m_data->left_speed == 0) {
        m_data->left_motor_mode = MOTOR_BRAKE;
    }
//
// compute right motor control
//    
    m_data->right_speed = psx_data->joy_right_y;
    m_data->right_speed = (m_data->right_speed >> 2) & 0x3F;
    if (m_data->right_speed > 31) {      
        m_data->right_motor_mode = MOTOR_BACKWARD;
        m_data->right_speed = m_data->right_speed - 32;              // convert 32->63  to   0->31
    } else {
        m_data->right_motor_mode = MOTOR_FORWARD;          
        m_data->right_speed = ((~m_data->right_speed) & 0x1F);       // convert 31->0   to   0->31
    }
    m_data->right_speed = joystick_to_speed[m_data->right_speed];
    if (m_data->right_speed == 0) {
        m_data->right_motor_mode = MOTOR_BRAKE;
    }
}

//***********************************************************************
//** Function:      steer_mode_B
//** Description:   Calc motor commands for steer/speed steering mode
//** Parameters:    psx_data - Data packet from PS2 controller
//**                m_data   - motor data 
//** Returns:       None
//***********************************************************************
void steer_mode_B(psx_map  *psx_data, motor_data  *m_data) 
{


}


//***********************************************************************
//** Function:      steer_mode_A
//** Description:   Calc motor commands for skid steering mode
//** Parameters:    psx_data - Data packet from PS2 controller
//**                m_data   - motor data 
//** Returns:       None
//***********************************************************************
void command_motors (motor_data  *m_data) 
{
    
    if (((m_data->left_motor_mode == MOTOR_FORWARD) && (m_data->current_left_motor_mode == MOTOR_BACKWARD)) ||
        ((m_data->left_motor_mode == MOTOR_BACKWARD) && (m_data->current_left_motor_mode == MOTOR_FORWARD))) {
        set_motor(LEFT_MOTOR, MOTOR_BRAKE, 0);
        delay_ms(30);
        }
    set_motor(LEFT_MOTOR, m_data->left_motor_mode, (uint8_t)m_data->left_speed);
    
    if (((m_data->right_motor_mode == MOTOR_FORWARD) && (m_data->current_right_motor_mode == MOTOR_BACKWARD)) ||
        ((m_data->right_motor_mode == MOTOR_BACKWARD) && (m_data->current_right_motor_mode == MOTOR_FORWARD))) {
        set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);
        delay_ms(30);
        }     
    delay_ms(10);
    set_motor(RIGHT_MOTOR, m_data->right_motor_mode, (uint8_t)m_data->right_speed);
    delay_ms(100);
}
    
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

const uint8_t joystick_to_speed[32] = {
    0,30,30,30,30,30,30,30,30,30,30,30,30,40,40,40,40,40,40,40,40,40,45,50,55,60,65,70,75,80,85,100     
};

//----------------------------------------------------------------------------
// steer_mode_A : Calc motor commands for skid steering mode
// ============
//
// Notes
//      adjust motors based on "y-value" of left and right joysticks
//
//      0->255   :: 255 = full speed reverse, 0 = full speed forward , 128 = off
//
//      1. Convert 0->255 range of joystick pot to 0->63 (right shift by 2)
//      2. 0->31 defines forward speed ;  31=full speed ; 0 = off
//          a. convert to 31->0
//      3. 32->63 defines forward speed ; 32=off ;        63 = full speed
//          a. convert to 0->31         ;  0=off ;        31 = full speed
//
// Parameters
//      psx_data      pointer to PS2 controller data structure
//      motor_data    pointer to motor data structure
//
// Values returned
//      none
//
void steer_mode_A(psx_map  *psx_data, motor_data  *m_data) 
{

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

//----------------------------------------------------------------------------
// steer_mode_B : Calc motor commands for steer/speed steering mode
// ============
//
// Notes
//      Left joystick gives steering information
//      Right joystick gives speed information
//          converted for 0->128 to MINIMUN_SPEED->100
//      Invert joystick values
//
// Parameters
//      psx_data[in]      pointer to PS2 controller data structure
//      motor_data[out]   pointer to motor data structure
//
// Values returned
//      none
//
void steer_mode_B(psx_map  *psx_data, motor_data  *m_data) 
{
direction_t steer_code;
uint8_t speed, joy_left_x, joy_left_y, joy_right_x, joy_right_y;

    joy_left_x = ~psx_data->joy_left_x;
    joy_left_y = ~psx_data->joy_left_y;
    joy_right_x = ~psx_data->joy_right_x;
    joy_right_y = ~psx_data->joy_right_y;
           
    speed =  joy_right_y - 128;
    speed = ((speed * (100 - MINIMUM_SPEED))/128) + MINIMUM_SPEED;
    steer_code = ((joy_left_x >> 5) & 0x07) + ((joy_left_y >> 2) & 0x38);
    switch (steering_mode_B_states[steer_code]) {
      case HALTED :
        m_data->left_speed = 0; m_data->right_speed = 0;
        m_data->left_motor_mode = MOTOR_BRAKE;
        m_data->right_motor_mode = MOTOR_BRAKE;
        break;
      case FORWARD :
        m_data->left_speed = speed; m_data->right_speed = speed;
        m_data->left_motor_mode = MOTOR_FORWARD;
        m_data->right_motor_mode = MOTOR_FORWARD;
        break;
      case BACKWARD :
        m_data->left_speed = speed; m_data->right_speed = speed;
        m_data->left_motor_mode = MOTOR_BACKWARD;
        m_data->right_motor_mode = MOTOR_BACKWARD;        
        break;
      case SPIN_LEFT :
        m_data->left_speed = speed; m_data->right_speed = speed;
        m_data->left_motor_mode = MOTOR_BACKWARD;
        m_data->right_motor_mode = MOTOR_FORWARD;        
        break;
      case SPIN_RIGHT :
        m_data->left_speed = speed; m_data->right_speed = speed;
        m_data->left_motor_mode = MOTOR_FORWARD;
        m_data->right_motor_mode = MOTOR_BACKWARD;        
        break;
      case FORWARD_LEFT :
        m_data->left_speed = ((speed - MINIMUM_SPEED)/2); m_data->right_speed = speed;
        m_data->left_motor_mode = MOTOR_FORWARD;
        m_data->right_motor_mode = MOTOR_FORWARD;        
        break;
      case FORWARD_RIGHT :
        m_data->left_speed = speed; m_data->right_speed = ((speed - MINIMUM_SPEED)/2);
        m_data->left_motor_mode = MOTOR_FORWARD;
        m_data->right_motor_mode = MOTOR_FORWARD;        
        break; 
      case REVERSE_LEFT :
        m_data->left_speed = ((speed - MINIMUM_SPEED)/2); m_data->right_speed = speed;
        m_data->left_motor_mode = MOTOR_BACKWARD;
        m_data->right_motor_mode = MOTOR_BACKWARD;        
        break;
      case REVERSE_RIGHT :
        m_data->left_speed = speed; m_data->right_speed = ((speed - MINIMUM_SPEED)/2);
        m_data->left_motor_mode = MOTOR_BACKWARD;
        m_data->right_motor_mode = MOTOR_BACKWARD;        
        break;                                 
      default:
        break;
    }
}


//----------------------------------------------------------------------------
// command_motors : convert motor commands to motor moves
// ==============
//
// Notes
//
// Parameters
//      motor_data[in]    pointer to motor data structure
//
// Values returned
//      none
//
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
    
/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        global.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  global.c
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 * Jim Herd              28/05/2010    Added flash data area
 ************************************************************************/
 
#include  "global.h"

   
//----------------------------------------------------------------------------
// Variables held in flash areas that can be re-flashed
//
//
#pragma   push
#pragma   DATA_SEG    FLASH_CONST

FLASH_data_t    FLASH_data;

#pragma   pop  

 
//----------------------------------------------------------------------------
// Global variables
//
uint16_t         right_speed, left_speed, current_right_speed, current_left_speed;
motor_mode_t     left_motor_mode, right_motor_mode, current_left_motor_mode, current_right_motor_mode;
uint16_t         left_motor_state, right_motor_state;
vehicle_state_t  state_of_vehicle;
uint8_t          pwm_differential;
uint8_t          radio_channel;

uint8_t          radio_id;


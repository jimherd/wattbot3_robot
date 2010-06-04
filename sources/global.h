/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        global.h
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Global includes, variables and definitions.
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#ifndef __global_H
#define __global_H

#include "PE_types.h"
#include "user_defines.h"

typedef struct  {
    uint16_t         right_speed, left_speed, current_right_speed, current_left_speed;
    motor_mode_t     left_motor_mode, right_motor_mode, current_left_motor_mode, current_right_motor_mode;
    uint16_t         left_motor_state, right_motor_state;
    vehicle_state_t  state_of_vehicle;
    uint8_t          pwm_differential;
} motor_data;

typedef struct {
    int16_t     x1, y1;
    int16_t     x2, y2; 
    int16_t     delta_x, delta_y; 
} segment_data;

typedef volatile struct {
    uint8_t     GUARD_BYTE; 
    uint8_t     steer_mode, motor_diff;
} FLASH_data_t;

#include "stdio.h" 
#include <stdtypes.h>
#include <hidef.h>
#include "derivative.h" /* Include peripheral declarations */

#include "pindef.h"     /* Pin definitions */
#include "sys_defines.h"

#include "user_code.h"

#include "pwm.h"
#include "delay.h"
#include "packetiser.h"

#include "init.h"       
#include "spi.h"
#include "sci.h"

#include "cypusb.h"
#include "servo.h"
#include "psx.h"
#include "main.h"
#include "rti.h"
#include "steer.h"
#include "flashio.h"
#include "adc.h"

extern  uint16_t         right_speed, left_speed, current_right_speed, current_left_speed;
extern  uint8_t          left_PWM, right_PWM, new_left_PWM, new_right_PWM;
extern  motor_mode_t     left_motor_mode, right_motor_mode, current_left_motor_mode, current_right_motor_mode;
extern  uint16_t         left_motor_state, right_motor_state;
extern  vehicle_state_t  state_of_vehicle;
extern  uint16_t         straight_line_speed, turn_speed;
extern  uint8_t          pwm_differential;
extern  uint8_t          radio_channel;
extern  uint32_t         tick_count;
extern  uint8_t          radio_id;

extern  const uint8_t steering_mode_B_states[64];
extern  const segment_data segment_1;
extern  const segment_data segment_2;
extern  const uint8_t isqrt_table[512];


extern  FLASH_data_t    FLASH_data;

#endif  /* __global_H */
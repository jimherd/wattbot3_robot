
#ifndef __user_code_H
#define __user_code_H

#include "global.h"

/* MODULE user_code */
 
//----------------------------------------------------------------------------
// function prototypes
//
void motor_sys_init(motor_data  *m_data);
void set_vehicle_state(void);
void set_motor(motor_t unit, motor_mode_t state, uint8_t pwm_width);
void  set_motor_from_struct(motor_t unit, motor_data  *m_data);
void vehicle_stop(void);
int16_t abs16(int16_t  value);
uint8_t  get_radio_channel(void);
uint8_t read_address(void);
void exec_command(uint8_t command_code);
void hang(uint8_t flash_count);
uint8_t nibble_swap(uint8_t value);
void check_battery_volts(motor_data  *m_data);

#endif


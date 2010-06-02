/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        main.h
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Header file for main.c  
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Jim Herd            28/05/2010    Original.
 ************************************************************************/
 
#ifndef __steer_H
#define __steer_H


 
void steer_mode_0(psx_map  *psx_data, motor_data  *m_data);
void steer_mode_1(psx_map  *psx_data, motor_data  *m_data);
void steer_mode_2(psx_map  *psx_data, motor_data  *m_data);
void command_motors(motor_data  *m_data);
uint8_t linear_interpolate(uint8_t x_value, segment_data  *s_data);
uint8_t get_PWM_B(uint8_t x_value, segment_data  *s_data);

#endif  /* __steer_H */
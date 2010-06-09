/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        init.h
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Header for microcontroller initialisation code
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#ifndef __init_H
#define __init_H
 
void init_system(void);
void Init_mcu(void);
void Init_pwm(void);
void Init_Dig_IO(void);
void Init_RTI(void);
void Init_flashio(void);
void Init_low_voltage_detect(void);

#endif  /* __init_H */
/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        main.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Robot Firmware
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 * Jim Herd               1/05/2009    Update for new H-bridge chip
 *                       28/05/2010    Restructured code to allow multiple
 *                                     steering modes
 ************************************************************************/

#include "global.h"      


//***********************************************************************
//** Function:      Main
//** Description:   Entry point of user code
//** Parameters:    None
//** Returns:       None
//***********************************************************************
void main()
{
static uint16_t   good_packets, bad_packets;
uint32_t          start_time, end_time, elapsed_time;
psx_map           psx_data;
motor_data        mot_data;
uint8_t           temp;
  
    init_system();
    motor_sys_init(&mot_data);
    test1();
//
//  Check radio address switches. If raw value is > 0xA0 then process as special commands
//
    temp = nibble_swap(SWITCH_VALUE);
    if (temp > 0xA0) {
        exec_command(temp & 0x0F);
        hang(FLASH_UPDATE_COMPLETE);
    }
    
    good_packets = 0;  
    bad_packets = 0;
    FOREVER {
//
// Get a data packet
//
        YELLOW_LED_OFF;
        start_time = tick_count;
        while(packet_rx(&psx_data, sizeof(psx_data)) != sizeof(psx_data)) {    
            bad_packets++;
            if (bad_packets > 200) {
                vehicle_stop();
                radio_rx_sm_rst();
                bad_packets = 0;
            }
        }
        end_time = tick_count;
        elapsed_time = end_time - start_time;
        if (elapsed_time > 60) {
            RED_LED_OFF;
            vehicle_stop();
            radio_rx_sm_rst();
            bad_packets = 0;
//            RED_LED_ON;
        }
        YELLOW_LED_ON;

        temp = FLASH_data.steer_mode;
        if (temp > MAX_STEER_MODE) {
            temp = 0;
        }
temp = STEER_MODE_2;    // ***************************** temporary test
        switch (temp) {
          case STEER_MODE_0 :
            steer_mode_0(&psx_data, &mot_data);
            break;
          case STEER_MODE_1 :
            steer_mode_1(&psx_data, &mot_data);
            break;
          case STEER_MODE_2 :
            steer_mode_2(&psx_data, &mot_data);
            break;            
          default :
            hang(3);
            break;
        }
        command_motors(&mot_data);
//
// adjust servos
//
        if(!psx_data.buttons.L1) servo_pos(0,0);
        if(!psx_data.buttons.R1) servo_pos(1,0);
        if(!psx_data.buttons.L2) servo_pos(0,14);
        if(!psx_data.buttons.R2) servo_pos(1,14);
        
        good_packets++;
    }
}

//----------------------------------------------------------------------------
// test1 : run small motor movement
// =====
//
// Description
//      On initialisation small robot movement shows robot to be working
//
// Notes
//         
//----------------------------------------------------------------------------

void test1(void)
{
    
uint8_t  i;

    for (i=0 ; i < 2 ; i++) {
        delay_250ms();
    }
    set_motor(LEFT_MOTOR, MOTOR_FORWARD, 50); 
    set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, 50);
    for (i=0 ; i < 2 ; i++) {
        delay_ms(150);
    } 
    set_motor(LEFT_MOTOR, MOTOR_BACKWARD, 50); 
    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, 50); 
    for (i=0 ; i < 2 ; i++) {
        delay_ms(150);
    } 
    set_motor(LEFT_MOTOR, MOTOR_OFF, 50); 
    set_motor(RIGHT_MOTOR, MOTOR_OFF, 50);     
    for (i=0 ; i < 2 ; i++) {
        delay_ms(150);
    }
}


//----------------------------------------------------------------------------
// table of values to map joystick reading to % full speed
//
//const uint8_t joystick_to_speed[32] = {
//    0,0,20,22,24,26,28,30,33,36,39,41,44,47,50,53,56,59,62,65,68,71,74,77,81,85,88,91,94,97,100,100     
//};
//const uint8_t joystick_to_speed[32] = {
//    0,30,30,30,30,30,30,30,30,30,30,30,30,40,40,40,40,40,40,40,40,40,45,50,55,60,65,70,75,80,85,100     
//};


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
//    left_speed = psx_data.joy_left_y;
//    left_speed = (left_speed >> 2) & 0x3F;
//    if (left_speed > 31) {
//        left_motor_mode = MOTOR_BACKWARD;
//        left_speed = left_speed - 32;              // convert 32->63  to   0->31
//    } else {        
//        left_motor_mode = MOTOR_FORWARD;      
//        left_speed = ((~left_speed) & 0x1F);       // convert 31->0   to   0->31
//    }
//    left_speed = joystick_to_speed[left_speed];
//    if (left_speed == 0) {
//        left_motor_mode = MOTOR_BRAKE;
//    }
//
// compute right motor control
//    
//    right_speed = psx_data.joy_right_y;
//    right_speed = (right_speed >> 2) & 0x3F;
//    if (right_speed > 31) {      
//        right_motor_mode = MOTOR_BACKWARD;
//        right_speed = right_speed - 32;              // convert 32->63  to   0->31
//    } else {
//        right_motor_mode = MOTOR_FORWARD;          
//        right_speed = ((~right_speed) & 0x1F);       // convert 31->0   to   0->31
//    }
//    right_speed = joystick_to_speed[right_speed];
//    if (right_speed == 0) {
//        right_motor_mode = MOTOR_BRAKE;
//    }
//
// set motors
// 
//    if (((left_motor_mode == MOTOR_FORWARD) && (current_left_motor_mode == MOTOR_BACKWARD)) ||
//        ((left_motor_mode == MOTOR_BACKWARD) && (current_left_motor_mode == MOTOR_FORWARD))) {
//        set_motor(LEFT_MOTOR, MOTOR_BRAKE, 0);
//        delay_ms(30);
//        }
//    set_motor(LEFT_MOTOR, left_motor_mode, (uint8_t)left_speed);
//    
//    if (((right_motor_mode == MOTOR_FORWARD) && (current_right_motor_mode == MOTOR_BACKWARD)) ||
//        ((right_motor_mode == MOTOR_BACKWARD) && (current_right_motor_mode == MOTOR_FORWARD))) {
//        set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);
//        delay_ms(30);
//        }     
//    delay_ms(10);
//    set_motor(RIGHT_MOTOR, right_motor_mode, (uint8_t)right_speed);
//    delay_ms(100);
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
//
// check battery levels and do one of the following
//
//  1. battery level very low -> show recharge message. and halt
//  2. battery level low -> show battery level message for several seconds then show "robot"
//  3. battery level OK -> continue as normal and show "robot" string
//   
    check_battery_volts();
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
            hang(BAD_STEER_MODE);
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
//
// check battery
//        
//        check_battery_volts();
        
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



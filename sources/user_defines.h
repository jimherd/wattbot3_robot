//----------------------------------------------------------------------------
//
//                  Robokid
//
//----------------------------------------------------------------------------
// user_defines.h : application specific program constants 
// ==============
//
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           31/07/2008    
///----------------------------------------------------------------------------

 
#ifndef __user_defines_H
#define __user_defines_H

#include "global.h"

//----------------------------------------------------------------------------
// define the version of vehicle hardware 
//

//----------------------------------------------------------------------------
// Macros
// ======
//
#define     RED_LED_ON      PTGD_PTGD3 = 1;
#define     RED_LED_OFF     PTGD_PTGD3 = 0;

#define     YELLOW_LED_ON    PTGD_PTGD4 = 1;
#define     YELLOW_LED_OFF   PTGD_PTGD4 = 0;

#define     KICK_WATCHDOG    SRS = 0x00;

//----------------------------------------------------------------------------
// system clock
//
#define BUSCLK  20000000  //Bus clock frequency (Hz)

//----------------------------------------------------------------------------
// timing defines
//
#define     PWM_FREQ    5000                // PWM set to 5kHz for motors
#define     PWM_COUNT   (BUSCLK/PWM_FREQ)   // main PWM count to give PWM_FREQ

//
#define     BAUD        57600               // Baud rate (BPS)


#define     WAIT_1SEC       DelayMs(1000);

//----------------------------------------------------------------------------

#define     DEFAULT_SPEED             60    // 60% full speed
#define     DEFAULT_LINE_BUMP_SPEED   60    // %
#define     DEFAULT_REVERSE_TIME       3
#define     DEFAULT_SPIN_TIME          5
#define     DEFAULT_PWM               60

#define     MINIMUM_PWM               10
#define     MAXIMUM_PWM              100
//
// linear segemnts for speed to PWM transfer funcion colaculation
//
#define     KNEE_1_X                 120
#define     KNEE_1_Y                  35

#define     NOS_SEGMENTS               2

#define     DIFFERENTIAL_NULL          7

#define     FLASH_ERASE_STATE       0xff

#define     CRITICAL_BATTERY_THRESHOLD  150
#define     LOW_BATTERY_THRESHOLD       180

typedef enum {
    STEER_MODE_0, STEER_MODE_1, STEER_MODE_2
} steer_mode_t;
#define   MAX_STEER_MODE    STEER_MODE_2
 

//----------------------------------------------------------------------------
// error codes
//
#define     OK          0
#define     FAIL        1

#define     FLASH_UPDATE_COMPLETE   2

//----------------------------------------------------------------------------
// ON/OFF codes
//
#define     ON          0x55
#define     OFF         0xCC

//----------------------------------------------------------------------------
// Motor action/state definitions
//
typedef enum {FULL_SPEED=100, HALF_SPEED=50} speed_t;
typedef enum {MOTOR_OFF, MOTOR_FORWARD, MOTOR_BACKWARD, MOTOR_BRAKE} motor_mode_t;
typedef enum {STOPPED, MOVING_FORWARD, MOVING_BACKWARD, TURNING_LEFT, TURNING_RIGHT} vehicle_state_t;
typedef enum {LEFT_MOTOR, RIGHT_MOTOR} motor_t;
typedef enum {HALTED, FORWARD, BACKWARD, SPIN_RIGHT, SPIN_LEFT, FORWARD_LEFT, FORWARD_RIGHT, REVERSE_LEFT, REVERSE_RIGHT} direction_t;
typedef enum {MODE_INIT, MODE_RUNNING, MODE_STOPPED} mode_state_t;
   
//----------------------------------------------------------------------------
// error codes
//
typedef enum {
    NO_ERROR, TIME_OUT
} error_codes_t;    

//----------------------------------------------------------------------------
// analogue channels  (0->13)
//
typedef enum {
        BATTERY_VOLTS, 
        
} a2d_channels_t;
 

#endif


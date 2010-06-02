//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// user_code.c : code to run main functions of the vehicle
// ===========
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd                 
//----------------------------------------------------------------------------

#include "global.h"

#pragma  MESSAGE DISABLE C1420

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// MODULE user_code 
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// motor_sys_init : initialisation of motor control variables
// ==============
//
//
void motor_sys_init(motor_data  *m_data) 
{
    m_data->state_of_vehicle = STOPPED;
    m_data->left_motor_state = MOTOR_OFF;
    m_data->right_motor_state = MOTOR_OFF;
    
    m_data->left_speed  = DEFAULT_SPEED; 
    m_data->right_speed = DEFAULT_SPEED; 
//    m_data->left_PWM    = DEFAULT_PWM; 
//    m_data->right_PWM   = DEFAULT_PWM;
     
    m_data->current_left_speed = 0;
    m_data->current_right_speed = 0; 
    m_data->pwm_differential = DIFFERENTIAL_NULL;

    set_motor(RIGHT_MOTOR, MOTOR_OFF, 0);
    set_motor(LEFT_MOTOR , MOTOR_OFF, 0);
}

//----------------------------------------------------------------------------
// set_vehicle_state : update state of vehicle
// =================
//
// Notes
//      Uses the state of each motor to define the state of the vehicle
//      -              STOPPED, MOVING_FORWARD, MOVING_BACKWARD, TURNING_LEFT, TURNING_RIGHT
// 
//void set_vehicle_state(void) 
//{
//
//    if ((left_motor_state == MOTOR_FORWARD) && (right_motor_state == MOTOR_FORWARD)) { 
//        state_of_vehicle = MOVING_FORWARD;
//        current_speed = straight_line_speed;
//    } else if ((left_motor_state == MOTOR_BACKWARD) && (right_motor_state == MOTOR_BACKWARD)) {
//        state_of_vehicle = MOVING_BACKWARD;
//        current_speed = straight_line_speed;
//    } else if ((left_motor_state == MOTOR_BACKWARD) && (right_motor_state == MOTOR_FORWARD)) {
//        state_of_vehicle = TURNING_LEFT;
//        current_speed = turn_speed;
//    } else if ((left_motor_state == MOTOR_FORWARD) && (right_motor_state == MOTOR_BACKWARD)) {
//        state_of_vehicle = TURNING_RIGHT;
//        current_speed = turn_speed;        
//    } else {
//        state_of_vehicle = STOPPED;
//        current_speed = 0;
//    }
//}

//----------------------------------------------------------------------------
// set_motor : configure a motor
// =========
//
// Notes
//      The motor speed is specified in the range of 0 to 100% which is
//      converted to the range 0 to 250 for use in the routine 'SetRatio8"
//
// Parameters
//      unit      : LEFT_MOTOR or RIGHT_MOTOR
//      state     : MOTOR_OFF, MOTOR_FORWARD, MOTOR_BACKWARD, or MOTOR_BRAKE
//      pwm_width : 0% to 100%
//
void  set_motor(motor_t unit, motor_mode_t state, uint8_t pwm_width) {

uint16_t  pulse_count, period_count ;

    period_count = TPM1MOD;        // get current period count (e.g. 889 for 5kHz frequency)
    pulse_count = (period_count/100) * (100 - pwm_width);
    
    if (unit == LEFT_MOTOR) {
        switch (state) {
            case MOTOR_OFF :        // set FREEWHEEL condition
                setReg16(TPM1C0V, 0);     // set LOW on PWM1 and PWM2
                setReg16(TPM1C1V, 0);                
                break;
            case MOTOR_FORWARD :    // set LOW on PWM2 and LM_PWM on LM_PWM1                                
                setReg16(TPM1C0V, pulse_count);       // set LOW on LM_PWM1
                setReg16(TPM1C1V, period_count);      // set pwm on LM_PWM2           
                break;
            case MOTOR_BACKWARD :   // set LOW on PWM1 and PWM on PWM2
                setReg16(TPM1C0V, period_count);      // set pwm on LM_PWM1
                setReg16(TPM1C1V, pulse_count);       // set LOW on LM_PWM2    
                break;
            case MOTOR_BRAKE :      // set BRAKE condition
                setReg16(TPM1C0V, period_count);     // set HIGH on LM_PWM1 and LM_PWM2
                setReg16(TPM1C1V, period_count);
                break;
            default :
                break;
        }
        current_left_motor_mode = state;
    }
    
    if (unit == RIGHT_MOTOR) {
        switch (state) {
            case MOTOR_OFF :        // set FREEWHEEL condition
                setReg16(TPM1C2V, 0);     // set LOW on RM_PWM1 and RM_PWM2
                setReg16(TPM1C3V, 0);
                break;
            case MOTOR_FORWARD :    // set LOW on RM_PWM2 and pwm on LM_PWM1
                setReg16(TPM1C2V, period_count);      // set pwm on RM_PWM1
                setReg16(TPM1C3V, pulse_count);       // set LOW on RM_PWM2
                break;
            case MOTOR_BACKWARD :   // set LOW on RM_PWM1 and RM_PWM2
                setReg16(TPM1C2V, pulse_count);       // set LOW on RM_PWM1
                setReg16(TPM1C3V, period_count);      // set pwm on RM_PWM2
                break;
            case MOTOR_BRAKE :      // set BRAKE condition
                setReg16(TPM1C2V, period_count);     // set HIGH on RM_PWM1 and RM_PWM2
                setReg16(TPM1C3V, period_count);
                break;
            default :
                break;
        }
        current_right_motor_mode = state;
    }
    setReg8(TPM1SC, (TPM_OVFL_INT_DIS | TPM_EDGE_ALIGN | TPM_BUSCLK | TPM_PRESCAL_DIV1));  
//    set_vehicle_state(); 
}

//----------------------------------------------------------------------------
// vehicle_stop : set both motor to brake
// ============
//
void vehicle_stop(void) {

    set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);
    set_motor(LEFT_MOTOR , MOTOR_BRAKE, 0);
}

//----------------------------------------------------------------------------
// abs16 : compute absolute value for a in16_t type value
// =====
//
int16_t abs16(int16_t  value) {
    
    if (value < 0){
        return -value;
    } else {
        return value;
    }
}

//----------------------------------------------------------------------------
// get_radio_channel : read RED/BLUE switches to define radio channel
// =================
//
// Notes
//      Data is input from PORTA and is inverted.
//
// Parameters
//      None
//
// Values returned
//      radio channel number : uint8_t
//
uint8_t  get_radio_channel(void) 
{
uint8_t   temp, red_digit, blue_digit;

    temp = PTAD;  temp = ~temp;
    red_digit = temp & 0x0F;
    blue_digit = ((temp >> 4)  & 0x0F);
    
    return  (red_digit * 10) + blue_digit;
}

//----------------------------------------------------------------------------
// exec_command : execute a configuration command
// ============
//
// Notes
//      Data is input from PORTA and is inverted.
//
// Parameters
//      command_code    command specifier
//
// Values returned
//      None
//
void exec_command(uint8_t command_code)
{
FLASH_data_t   FLASH_data_image;

    memcpy(&FLASH_data, &FLASH_data_image, sizeof(FLASH_data_t));    // get flash data

    switch(command_code) {
      case STEER_MODE_0 :
        FLASH_data_image.steer_mode = STEER_MODE_0;
        break;
      case STEER_MODE_1 :
        FLASH_data_image.steer_mode = STEER_MODE_1;
        break;
      case STEER_MODE_2 :
        FLASH_data_image.steer_mode = STEER_MODE_2;
        break;                
      default:
        break;
    }
//
// clear FLASH area
//    
    FlashErasePage((uint16_t)&FLASH_data.GUARD_BYTE);
//
// write data to FLASH area
//       
    FlashProgramByte((uint16_t)&FLASH_data.steer_mode, FLASH_data_image.steer_mode);
    FlashProgramByte((uint16_t)&FLASH_data.motor_diff, FLASH_data_image.motor_diff);
}


//
//   4. store in FLASH area for later use   (Time for FLASH write to work?)
//
//        memcpy(&FLASH_data, &FLASH_data_image, sizeof(FLASH_data_t));
//        FLASH_data_image.LEFT_WHEEL_THRESHOLD = left_threshold;
//        FLASH_data_image.RIGHT_WHEEL_THRESHOLD = right_threshold;
//        FlashErasePage((uint16_t)&FLASH_data.GUARD_BYTE);
//        FlashProgramByte((uint16_t)&FLASH_data.LEFT_WHEEL_THRESHOLD, FLASH_data_image.LEFT_WHEEL_THRESHOLD);
//        FlashProgramByte((uint16_t)&FLASH_data.RIGHT_WHEEL_THRESHOLD, FLASH_data_image.RIGHT_WHEEL_THRESHOLD);



//----------------------------------------------------------------------------
// hang : halt and flash code on yellow light
// ====
//
// Notes
//      Yellow led is falshed "flash_count" times with a period of 0.5 second.
//      Repeated infinitely, with 2 seconds between goups of flashes.
//
// Parameters
//      command_code    command specifier
//
// Values returned
//      None
//
void hang(uint8_t flash_count)
{
int i;

    YELLOW_LED_OFF;
    FOREVER {
        for(i=0 ; i < flash_count ; i++) {
            YELLOW_LED_ON;
            delay_250ms();delay_250ms();
            YELLOW_LED_OFF;
            delay_250ms();delay_250ms(); 
        }
        for(i=0 ; i<4 ; i++) {
            delay_250ms();delay_250ms();
        }
    }
}

//----------------------------------------------------------------------------
// nibble_swap : swap upper and lower nibbles of 8-bit value
// ===========
//
// Notes
//
// Parameters
//      value    8-bit value to be nibble swapped
//
// Values returned
//      swapped value
//
uint8_t nibble_swap(uint8_t value)
{
    asm {
            LDA     value
            NSA
    };
    return value;
}

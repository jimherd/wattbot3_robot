/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        init.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Micontroller initialisation functions
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/
 
#include "global.h"

//----------------------------------------------------------------------------
// init_system : call initialisation code
// ===========
//
// Parameters
//      None
//
// Notes
//      
//
void init_system(void)
{
    Init_mcu();
    Init_Dig_IO();    
    Init_pwm();
    Init_RTI();
    Init_adc();
    Init_flashio(); 
    init_spi_norm();
    radio_channel = get_radio_channel();      
    init_radio();

//    set_motor(LEFT_MOTOR, MOTOR_OFF, 0); 
//    set_motor(RIGHT_MOTOR, MOTOR_OFF, 0);
//    current_left_speed = 0; current_right_speed = 0;
//    current_left_motor_mode = MOTOR_OFF; current_right_motor_mode = MOTOR_OFF;
    
    RED_LED_ON;

    radio_id = radio_get_id();
}

//***********************************************************************
//** Function:      init_mcu
//** Description:   
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void Init_mcu(void)
{
  /* Common initialization of the write once registers */
  /* SOPT: COPE=0,COPT=1,STOPE=0 */
    SOPT = 0x73;   //  SOPT = 0x53;    // use STOP instruction to force a reset                                  
 
  /* SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=1,LVDSE=1,LVDE=0,BGBE=0 */
  SPMSC1 = 0x18;                                      
  /* SPMSC2: LVWF=0,LVWACK=0,LVDV=0,LVWV=0,PPDF=0,PPDACK=0,PPDC=0 */
  SPMSC2 = 0x00;                                      
  /* SMCLK: MPE=0,MCSEL=0 */
  SMCLK &= (unsigned char)~0x17;                     
  
  /*  System clock initialization */
  /* ICGC1: HGO=0,RANGE=1,REFS=0,CLKS1=0,CLKS0=1,OSCSTEN=1,LOCD=1 */
  ICGC1 = 0x4E;                                      
  /* ICGC2: LOLRE=1,MFD2=1,MFD1=1,MFD0=1,LOCRE=0,RFD2=0,RFD1=0,RFD0=0 */
  ICGC2 = 0xF0;                                      
  
  ICGTRM = *(unsigned char*far)0xFFBE; /* Initialize ICGTRM register from a non volatile memory */
  while(!ICGS1_LOCK);                  /* Wait */
  
  EnableInterrupts;
}

//----------------------------------------------------------------------------
// Init_pwm : configure PWM generation subsystem
// ========
//
// Parameters
//      None
//
// Notes
//      
//
void Init_pwm(void){
//
// init of channel 1 : PWM signals for the two DC motors
//                      
    setReg8(TPM1SC, (TPM_NO_CLK));       // Stop and reset counter   0x00

    setReg16(TPM1MOD, PWM_COUNT);        // Period value setting 
    
    setReg16(TPM1C0V, 0x1000);
    setReg16(TPM1C1V, 0x1000);
    setReg16(TPM1C2V, 0x1000);
    setReg16(TPM1C3V, 0x1000);
    
    setReg8(TPM1C0SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
    setReg8(TPM1C1SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
    setReg8(TPM1C2SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
    setReg8(TPM1C3SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
                   
    setReg8(TPM1SC, (TPM_OVFL_INT_DIS | TPM_EDGE_ALIGN | TPM_BUSCLK | TPM_PRESCAL_DIV1));
//
// init of channel 2
//
    setReg8(TPM2SC, (TPM_NO_CLK));       // Stop and reset counter   0x00
  
    TPM2MOD = 0x0C36;                   /* Period value setting */

    TPM2C0V = 0x00DF;                   /* Compare 0 value setting */
    TPM2C1V = 0x00DF;                   /* Compare 1 value setting */  

    setReg8(TPM2C0SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
    setReg8(TPM2C1SC, (TPM_INT_DIS | PWM_EDGE_ALIGNED | PWM_ACT_HIGH_PULSE));
  
    setReg8(TPM2SC, (TPM_OVFL_INT_DIS | TPM_EDGE_ALIGN | TPM_BUSCLK | TPM_PRESCAL_DIV128));

}
 

//----------------------------------------------------------------------------
// Init_Dig_IO : configure digital I/O lines
// ===========
//
// Parameters
//      None
//
// Notes
//      the bit patterns for the initialisation are in file "pindef,h"
//
void Init_Dig_IO(void) {
//
// set data direction registers
//
    setReg8(PTADD, PORTA_DIR);
    setReg8(PTCDD, PORTC_DIR);
    setReg8(PTEDD, PORTE_DIR);
    setReg8(PTFDD, PORTF_DIR);  
    setReg8(PTGDD, PORTG_DIR);
//
// set pull-up registers
//
    setReg8(PTAPE, PORTA_PULLUP);
    setReg8(PTCPE, PORTC_PULLUP);
    setReg8(PTEPE, PORTE_PULLUP);
    setReg8(PTFPE, PORTF_PULLUP);  
    setReg8(PTGPE, PORTG_PULLUP);
//
// set slewrate control registers
//
    setReg8(PTASE, PORTA_SLEWRATE);
    setReg8(PTBSE, PORTB_SLEWRATE);
    setReg8(PTCSE, PORTC_SLEWRATE);
    setReg8(PTDSE, PORTD_SLEWRATE);
    setReg8(PTESE, PORTE_SLEWRATE);
    setReg8(PTFSE, PORTF_SLEWRATE);  
    setReg8(PTGSE, PORTG_SLEWRATE);
//
// set output drive control registers
//
    setReg8(PTADS, PORTA_OUT_DRIVE);
    setReg8(PTBDS, PORTB_OUT_DRIVE);
    setReg8(PTCDS, PORTC_OUT_DRIVE);
    setReg8(PTDDS, PORTD_OUT_DRIVE);
    setReg8(PTEDS, PORTE_OUT_DRIVE);
    setReg8(PTFDS, PORTF_OUT_DRIVE);  
    setReg8(PTGDS, PORTG_OUT_DRIVE);
//
// initialise outputs
// 
    setReg8(PTAD, PORTA_INIT);
    setReg8(PTCD, PORTC_INIT);
    setReg8(PTED, PORTE_INIT);
    setReg8(PTFD, PORTF_INIT);  
    setReg8(PTGD, PORTG_INIT);       
}

//----------------------------------------------------------------------------
// Init_RTI : configure real-time interrupt subsystem
// ========
//
// Parameters
//      None
//
// Notes
//      Set to use 1kHz internal source to gine 8mS RTI interrupt
//
void Init_RTI(void) {

    setReg8(SRTISC, (RTI_CLK_SEL_1KHZ | RTI_INT_EN | RTI_DEL8MS));       
}

//----------------------------------------------------------------------------
// Init_flashio : configure flash subsystem to allow erase/write commands
// ============
//
// Parameters
//      None
//
// Notes
//      Set parameters to give a flash clock of approx 200k from the busclk.
//
void Init_flashio(void) {  
    setReg8(FCDIV, (FC_PRESCALE_8 | FC_DIV_20MHZ_BUSCLK));
}     



                                                                     
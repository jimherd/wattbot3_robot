/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        adc.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Analogue to Digital converter driver
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#include "global.h"
#include "adc.h"

//***********************************************************************
//** Function:      init_adc
//** Description:   Initialises ADC port
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void init_adc()
{
  /* ### Init_ADC init code */
  /* APCTL1: ADPC7=0,ADPC6=0,ADPC5=0,ADPC4=0,ADPC3=0,ADPC2=0,ADPC1=0,ADPC0=1 */
    APCTL1 = 0x01;                                      
  /* ADC1CFG: ADLPC=0,ADIV1=1,ADIV0=1,ADLSMP=1,MODE1=0,MODE0=0,ADICLK1=1,ADICLK0=1 */
    ADC1CFG = 0x73;                                      
  /* ADC1SC2: ADACT=0,ADTRG=0,ACFE=0,ACFGT=0 */
    ADC1SC2 = 0x00;                                      
  /* ADC1CV: ADCV9=0,ADCV8=0,ADCV7=0,ADCV6=0,ADCV5=0,ADCV4=0,ADCV3=0,ADCV2=0,ADCV1=0,ADCV0=0 */
    ADC1CV = 0x00;                                      
  /* ADC1SC1: COCO=0,AIEN=0,ADCO=0,ADCH4=1,ADCH3=1,ADCH2=1,ADCH1=1,ADCH0=1 */
    ADC1SC1 = 0x1F;     
}

//***********************************************************************
//** Function:      get_adc
//** Description:   Gets analogue value for selected channel
//** Parameters:    char chan - Analogue channel to read
//** Returns:       char      - ADC value
//*********************************************************************** 
char get_adc(char chan){

    ADC1SC1_ADCH = chan;
 
    while(!ADC1SC1_COCO)
        NULL_STATEMENT;
    return(ADC1RL);
}
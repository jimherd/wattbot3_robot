/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        spi.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#include "sci.h"
#include "global.h"

//***********************************************************************
//** Function:      init_sci
//** Description:   Initialises the SCI port for RS232 communication
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void init_sci(){
  SCI1BD = busclk/16/baud; 	//Set baud based on bus clock
  PTEDD_PTEDD0 = 1;					//Tx pin as output
  PTED_PTED0 = 1;
  SCI1C1 = 0x00;            //RS232 operation
  SCI1C2 = 0x00;
  SCI1C3 = 0x00;
}

//***********************************************************************
//** Function:      sci_tx_byte
//** Description:   SCI Tx function
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void sci_tx_byte(char s_char){
  char dummy;	            	// dummy var for reading SCI1S1
  SCI1C2_TE = 1;          	// enable Tx
  dummy = SCI1S1;          	// 1st half of TDRE clear procedure
  SCI1D = s_char;           // 2nd half of TDRE clear procedure
  while(!SCI1S1_TDRE);			// Wait until send buffer empty
  while(!SCI1S1_TC);       	// Wait until byte sent
  SCI1C2_TE = 0;
}

//***********************************************************************
//** Function:      sci_rx_byte
//** Description:   SCI Rx function
//** Parameters:    None
//** Returns:       None
//***********************************************************************
char sci_rx_byte(){
  char rec_char;
  unsigned int timeout=0;
  if (SCI1S1_RDRF)         	// 1st half of RDRF clear procedure
    rec_char = SCI1D;       // 2nd half of RDRF clear procedure
  SCI1C2_RE = 1;           	// enable Rx
  //while(!SCI1S1_RDRF);
  
  for(timeout=0 ; (!SCI1S1_RDRF & (timeout < 64000)); timeout++) asm("nop");
  if (timeout >= 64000) return(0x00);
  rec_char = SCI1D;        	// get received character
  SCI1C2_RE = 0;            // disable Rx
  return rec_char;			 			
}

//***********************************************************************
//** Function:      send_msg
//** Description:   SCI String Sender
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void send_msg(char msg[]){
  byte n=0;	   							// String pointer
  
  do{
    sci_tx_byte(msg[n]);
  	n++;
  }while(msg[n]);
}

//***********************************************************************
//** Function:      HexToAsc
//** Description:   Converts Byte to ASCII string
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void * HexToAsc(char byte, char number_str[]){
  char temp;
  temp = byte & 0xF0;
  temp = temp >> 4;
  if (temp <= 9) number_str[0]=(temp + '0');
  else number_str[0]=(temp + 'A' - 10);
  
  temp = byte & 0x0F;
  if (temp <= 9) number_str[1]=(temp + '0');
  else number_str[1]=(temp + 'A' - 10);
  number_str[2]=0x00;
  return number_str;      
}

void * HexToBin(char byte, char number_str[]){
  char n;
  for (n=0;n<8;n++){
    if (byte & 0b10000000) number_str[n]='1';
    else number_str[n]='0';
    byte = byte <<1;
  }
  number_str[n]=0x00;
  return number_str;
}

//***********************************************************************
//** Function:      bcd
//** Description:   Bin2Dec convertion function
//** Parameters:    None
//** Returns:       None
//***********************************************************************
void * bcd(char byte, char number_str[]){
	number_str[0] = ((byte - (byte % 100)) / 100) & 0xFF;
	byte -= number_str[0]*100;

	number_str[1] = ((byte - (byte % 10)) / 10) & 0xFF;
	byte -= number_str[1]*10;
	
	number_str[2] = byte;

	number_str[0] += '0';
	number_str[1] += '0';
	number_str[2] += '0';
	number_str[3] = 0x00;
	return number_str;
}
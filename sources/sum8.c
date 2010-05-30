/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        sum8.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  JNC sum8 checksum function
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/
 
#include "global.h"

//***********************************************************************
//** Function:      sum8calc
//** Description:   Computes checksum value
//** Parameters:    void *data - Pointer to array to compute checksum from
//**                char len   - Number of bytes in array
//** Returns:       char       - Checksum
//***********************************************************************
char sum8calc(void *data, char len){
  char checksum=0;
  char n;
  
  for(n=0 ; n<len ; n++){
    checksum += *(((char *)data)+n);
  }
  return(checksum);
}
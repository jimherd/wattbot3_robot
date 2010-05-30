/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        motor.h
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Transmits and receives packets using cypress wifi driver
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Alpha release
 ************************************************************************/

#include "global.h"
#include "packetiser.h"
#include "cypusb.h" 

#define DEADMAN_MAX_COUNT 30000

//***********************************************************************
//** Function:      packet_tx
//** 
//** Description:   Transmits a packet
//**
//** Parameters:    void *data - Pointer to data to transmit 
//**                char len   - Number of bytes to transmit
//** Returns:       None
//*********************************************************************** 
void packet_tx(void *data, char len)
{
    (void)radio_tx_data(len, data);
}

//***********************************************************************
//** Function:      packet_rx
//** 
//** Description:   Receives a packet
//**
//** Parameters:    void *data - Pointer to receive buffer 
//**                char len   - Length of buffer in bytes
//** Returns:       char       - Number of bytes received
//***********************************************************************
uint8_t  packet_rx(void *data, char len)
{
static char valid[20];
uint8_t   n, bytes_rx;
uint16_t  counter;
  
  /* Wait for some data */  
    do {
        for (counter = 0; (counter < DEADMAN_MAX_COUNT) && !bytes_rx ; counter++) {
            bytes_rx = radio_rx_data(len, data, valid);
        }
    
    /* If timeout - Wifi chip crashed; Reset Wifi chip */
        if (counter == DEADMAN_MAX_COUNT) {
            asm("stop");  // force system reset   // radio_rx_sm_rst();  
        }
    } while(!bytes_rx);
  
  /* Check all bytes received are valid */
    for(n = 0 ; n < bytes_rx ; n++){
        if (valid[n] != 0xFF){
            bytes_rx = 0;
        }
    }
    return(bytes_rx);  
}
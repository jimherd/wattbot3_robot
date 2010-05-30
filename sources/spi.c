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

#include "global.h"
#include "pindef.h"
#include "spi.h"

//***********************************************************************
//** Function:      init_spi_norm
//** Description:   Configures SPI module 1 for "normal" SPI operation
//** Parameters:    None
//** Returns:       None
//***********************************************************************
void init_spi_norm(void)
{
    SPI1C1=0b01010000;
    SPI1C2=0b00000000;
    SPI1BR=0b01000011;
}

//***********************************************************************
//** Function:      init_spi_psx
//** Description:   Configures SPI module 1 for PSX operation
//** Parameters:    None
//** Returns:       None
//***********************************************************************
void init_spi_psx(void)
{
    SPI1C1=0b01011101;
    SPI1C2=0b00000000;
    SPI1BR=0b01000011;
}

//***********************************************************************
//** Function:      spi_io
//** Description:   Activates SPI module 1 shift register
//** Parameters:    char data - data to shift out
//** Returns:       char - data shifted in
//***********************************************************************
uint8_t spi_io(uint8_t data)
{
uint8_t dummy;	          // dummy var for reading SCIS1

    while(!SPI1S_SPTEF) {
        NULL_STATEMENT;
    }
    dummy = SPI1S;        // 1st half of SPTEF clear procedure
    SPI1D = data;         // 2nd half of SPTEF clear procedure
    while(!SPI1S_SPTEF) {
        NULL_STATEMENT;   // Wait till data sent  
    }
    while(!SPI1S_SPRF) {
        NULL_STATEMENT;   // Wait till data received ready
    }
    return(SPI1D);
}

//***********************************************************************
//** Function:      spi_access
//** Description:   
//** Parameters:    SPI_DEVICE dev - Device to send data to (see spi.h) 
//**                char addr      - Register address 
//**                char data      - Payload
//** Returns:       char           - Data received
//***********************************************************************
uint8_t spi_access(SPI_DEVICE dev, uint8_t addr, uint8_t data)
{
    if(dev == CYP_RADIO) {
        CYP_RADIO_SS = 0;
    }
    (void)spi_io(addr);
    data=spi_io(data);
    if(dev == CYP_RADIO) {
        CYP_RADIO_SS = 1;  
    }
    return(data);
}
  
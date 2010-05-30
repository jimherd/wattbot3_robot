/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        spi.h
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Header for SPI driver 
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#ifndef __spi_H
#define __spi_H

typedef enum {
  CYP_RADIO,
} SPI_DEVICE;
 
void init_spi_norm(void);
void init_spi_psx(void);  
uint8_t spi_io(uint8_t data);
uint8_t spi_access(SPI_DEVICE dev, uint8_t addr, uint8_t data);

// Read/Write macros for SPI access
#define spi_tx(device, addr, data)  spi_access(device, (addr | 0x80), data)
#define spi_rx(device, addr)        spi_access(device, addr, 0xFF)

#endif  /* __spi_H */
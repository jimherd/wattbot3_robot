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
 *  Header for SCI driver
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#define busclk  20000000  //Bus clock frequency (Hz)
#define baud    57600     //Baud rate (BPS)

extern void init_sci(void);
extern void sci_tx_byte(char s_char);
extern char sci_rx_byte(void);
extern void send_msg(char msg[]);
extern void * HexToAsc(char byte, char *number_str);
extern void * HexToBin(char byte, char *number_str);
extern void * bcd(char byte, char number_str[]);


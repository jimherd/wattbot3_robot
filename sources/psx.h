/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        psx.h
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Header for Playstation Controller driver
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#ifndef __psx_H
#define __psx_H

#define PSX_CONFIG      0x43  //Enter config mode             
#define PSX_MODE_LOCK   0x44  //Enable mode lock  
#define PSX_VIBRATE_EN  0x4D  //Enable vibrate                              
#define PSX_STATUS      0x42  //Get PSX info

#define PSX_LOCK_ANA    0x01    
#define PSX_LOCK_DIG    0x00              

typedef struct {
	char random;
	char id;
	char header;
    struct{
		unsigned select		:1;
		unsigned joy_left	:1;
		unsigned joy_right  :1;
        unsigned start      :1;
        unsigned up         :1;
        unsigned right      :1;
        unsigned down       :1;
        unsigned left       :1;
        unsigned L2         :1;
        unsigned R2         :1;
        unsigned L1         :1;
        unsigned R1         :1;
        unsigned triangle   :1;
        unsigned circle     :1;
        unsigned cross      :1;
        unsigned square     :1;
	} buttons;
	char joy_right_x;
	char joy_right_y;
	char joy_left_x;
	char joy_left_y;
} psx_map;

void init_psx(void);
char psx_io(char tx, char *ack);
char psx_com(void *psx_tx, void *psx_rx, char len);
void psx_config_mode(char enable);
void psx_lock_en(char mode, char enable);
void psx_vib_en(char enable);
void psx_motor1_duty(char duty);
void psx_motor2_duty(char duty);
void psx_get_stat(void *rx_buff);

#endif  /* __psx_H */

	
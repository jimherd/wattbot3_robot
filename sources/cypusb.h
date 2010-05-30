/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        cypusb.h
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Header for Cypress Wireless USB driver
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#ifndef __cypusb_H
#define __cypusb_H

//******************************
// REG_ID
//******************************
#define REG_ID			    0x00
#define VERSION_MASK	    0x0F
#define MANUFACTURING_MASK	0xF0

//******************************
// REG_SYNTH_A_CNTR
//******************************
#define REG_SYNTH_A_CNTR    0x01  
#define REG_SYNTH_N_CNTR    0x02

//******************************
// REG_CONTROL
//******************************
#define REG_CONTROL	      	0x03    
#define RX_ENABLE      	  	0x80	
#define TX_ENABLE      	  	0x40	
#define PN_CODE_SELECT	  	0x20	
#define AUTO_SYNTH_COUNT  	0x10
#define AUTO_PA_DISABLE	  	0x08
#define PA_ENABLE		    0x04
#define AUTO_SYNTH_DISABLE	0x02
#define SYNTH_ENABLE	    0x01

//******************************
// REG_DATA_RATE
//******************************
#define REG_DATA_RATE     	0x04	
#define RADIO_MODE_NORM	  	0x00
#define CHIP_BITS_32	    0x04
#define CHIP_BITS_64	    0x00
#define NORMAL_DATA_RATE  	0x00
#define DOUBLE_DATA_RATE  	0x02
#define OVERSAMPLING_6X	    0x00
#define OVERSAMPLING_12X    0x01

//******************************
// REG_CONFIG
//******************************
#define REG_CONFIG          0x05	
#define RADIO_BYPASS	    0x20
#define RX_INVERT		    0x10
#define TX_INVERT		    0x08
#define IRQ_OD			    0x02
#define IRQ_CMOS		    0x00
#define IRQ_ACTIVE_HI	    0x01
#define IRQ_ACTIVE_LO	    0x00

//******************************
// REG_SERDES_CTL
//******************************
#define REG_SERDES_CTL	    0x06	
#define SERDES_ENABLE	    0x08

//******************************
// REG_RX_INT_EN
//******************************
#define REG_RX_INT_EN	    0x07
#define RX_UNDER_B		    0x80	
#define RX_OVER_B		    0x40	
#define RX_EOF_B		    0x20	
#define RX_FULL_B		    0x10	
#define RX_UNDER_A		    0x08	
#define RX_OVER_A		    0x04	
#define RX_EOF_A		    0x02	
#define RX_FULL_A		    0x01	

//******************************
// REG_RX_INT_STAT
//******************************
#define REG_RX_INT_STAT	    0x08
#define RX_VALID_B		    0x80	
#define RX_VALID_A		    0x08	

//******************************
// REG_DATA_RX_A
//******************************
#define REG_DATA_RX_A	    0x09
#define REG_VALID_RX_A	    0x0A
#define REG_DATA_RX_B	    0x0B
#define REG_VALID_RX_B	    0x0C

//******************************
// REG_TX_INT_EN
//******************************
#define REG_TX_INT_EN	    0x0D
#define TX_UNDER		    0x08
#define TX_OVER			    0x04
#define TX_EOF			    0x02
#define TX_EMPTY		    0x01

//******************************
// REG_TX_INT_STAT
//******************************
#define REG_TX_INT_STAT	    0x0E

//******************************
// REG_DATA_TX
//******************************
#define REG_DATA_TX		    0x0F
#define REG_VALID_TX	    0x10

//******************************
// REG_PN_CODE
//******************************
#define REG_PN_CODE		    0x11	

//******************************
// REG_THRESHOLD_LO
//******************************
#define REG_THRESHOLD_LO    0x19	

//******************************
// REG_THRESHOLD_HI
//******************************
#define REG_THRESHOLD_HI    0x1A	

//******************************
// REG_THRESHOLD_CNT
//******************************
#define REG_THRESHOLD_CNT   0x1B

//******************************
// REG_WAKE_EN
//******************************
#define REG_WAKE_EN  	    0x1C	
#define WAKE_EN    		    0x01	

//******************************
// REG_WAKE_STAT
//******************************
#define REG_WAKE_STAT     	0x1D	
#define WAKE_INT		    0x01

//******************************
// REG_ANALOG_CTL
//******************************
#define REG_ANALOG_CTL	    0x20	
#define AGC_RSSI_CTL        0x40	
#define MID_READ_EN         0x20	
#define PACTL_EN		    0x04
#define PACTL_INVERT	    0x02
#define SYSTEM_RESET        0x01

//******************************
// REG_CHANNEL
//******************************
#define REG_CHANNEL		    0x21

//******************************
// REG_RSSI
//******************************
#define REG_RSSI		    0x22
#define RSSI_VALID	        0x20
#define RSSI_MASK           0x1F

//******************************
// REG_PA
//******************************
#define REG_PA            	0x23	

//******************************
// REG_XTAL_ADJ
//******************************
#define REG_CRYSTAL_ADJ    	0x24
#define CLOCK_DISABLE	    0x40

//******************************
// REG_CAL_COUNT
//******************************
#define REG_CAL_COUNT	    0x25

//******************************
// REG_VCO_CAL
//******************************
#define REG_VCO_CAL			0x26
#define MINUS_5_PLUS_5      0xC0
#define MINUS_2_PLUS_3      0x80
#define VCO_CAL_MASK		0x1F

//******************************
// REG_AGC_CTL
//******************************
#define REG_AGC_CTL         0x2E
#define AGC_OFF             0x80

//******************************
// REG_CARRIER_DETECT
//******************************
#define REG_CARRIER_DETECT	0x2F
#define CD_OVERRIDE	        0x80

//******************************
// REG_CLOCK_MANUAL
//******************************
#define REG_CLOCK_MANUAL    0x32

//******************************
// REG_CLOCK_ENABLE
//******************************			
#define REG_CLOCK_ENABLE    0x33

//******************************
// REG_SYN_LOCK_CNT
//******************************
#define REG_SYN_LOCK_CNT    0x38	

//******************************
// REG_ID
//******************************
#define REG_MFG_ID_1        0x3C	// REG_MFG_ID
#define REG_MFG_ID_2        0x3D
#define REG_MFG_ID_3        0x3E
#define REG_MFG_ID_4        0x3F

void init_radio(void);
void radio_set_channel(uint8_t channel);
uint8_t radio_get_channel(void);
void radio_isr_enable(void);
void radio_isr_disable(void);
void radio_tx_on(void);
void radio_rx_on(void);
void radio_off(void);
void radio_rx_isr(void);
uint8_t  radio_rx_data(char buffer_length, char rx_buffer[], char valid_buffer[]);
void radio_rx_sm_rst(void);
char radio_tx_data(char buffer_length, char tx_buffer[]);
char radio_get_rssi(void);
char radio_get_id(void);

#endif  /* __cypusb_H */
/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        cypusb.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Cypress Wireless USB driver 
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#include "global.h"

#pragma MESSAGE DISABLE C1420 //Yes i know i'm chucking away unused SPI data
                              //!!FIX ME!! Use (void)spi_tx if SPI output not req'd

#define DEADMAN_MAX_COUNT 30000

static char rx_buff_size;      //Shared variable - size of buffers
static char rx_data_len;       //Shared variable - length of string received
static char *rx_data_buff;     //Pointer to data buffer
static char *rx_valid_buff;    //Pointer to valid buffer

static struct isr_status{
    unsigned radio_isr_active :1;
    unsigned radio_overflow   :1;
    unsigned radio_EOF        :1; 
} isr_status;

//***********************************************************************
//** Function:      init_radio
//** 
//** Description:   Initialises the Cypress radio to a default state
//**
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void init_radio(void)
{  
//
// Set data direction registers
//
    CYP_RADIO_RST_D = 1;
    CYP_RADIO_SS_D  = 1;
//  
// Setup IRQ pin
//
    IRQSC_IRQEDG = 1;     //IRQ on rising edge
    IRQSC_IRQMOD = 1;     //IRQ triggered on level and edge
    IRQSC_IRQPE = 1;      //Enable IRQ pin
//  
// Reset wireless chip
//
    CYP_RADIO_RST = 0;
    CYP_RADIO_SS = 1;
    delay_100us();
    CYP_RADIO_RST = 1;
    delay_1ms();
//  
// Initialize chip
//
    spi_tx(CYP_RADIO, REG_CLOCK_ENABLE, 0x41);
    spi_tx(CYP_RADIO, REG_CLOCK_MANUAL, 0x41);
    spi_tx(CYP_RADIO, REG_ANALOG_CTL, (AGC_RSSI_CTL|PACTL_EN));
    spi_tx(CYP_RADIO, REG_SERDES_CTL,(SERDES_ENABLE|3));
    spi_tx(CYP_RADIO, REG_VALID_TX, 0xFF);   
    spi_tx(CYP_RADIO, REG_PA,0x07);
    spi_tx(CYP_RADIO, REG_VCO_CAL, MINUS_5_PLUS_5);
    spi_tx(CYP_RADIO, REG_CRYSTAL_ADJ, CLOCK_DISABLE);
    spi_tx(CYP_RADIO, REG_CHANNEL, radio_channel);
//  
// Reset flags 
//
    isr_status.radio_isr_active = NO;
    isr_status.radio_overflow = NO;
    isr_status.radio_EOF = NO;
}

//***********************************************************************
//** Function:      radio_set_channel
//** 
//** Description:   Sets radio channel in use
//**
//** Parameters:    channel - Channel number to set
//** Returns:       None
//*********************************************************************** 
void radio_set_channel(uint8_t channel)
{
    spi_tx(CYP_RADIO, REG_CHANNEL, channel);
}

//***********************************************************************
//** Function:      radio_get_channel
//** 
//** Description:   Gets radio channel in use
//**
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
uint8_t radio_get_channel(void)
{
    return(spi_rx(CYP_RADIO, REG_CHANNEL));
}


//***********************************************************************
//** Function:      radio_isr_enable
//** 
//** Description:   Disable receive interrupt
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************
void radio_isr_enable(void)
{
    IRQSC_IRQACK = 1;   //Clear IRQ flag if set
    IRQSC_IRQIE = 1;    //Enable IRQ pin interrupt 
}

//***********************************************************************
//** Function:      radio_isr_disable
//** 
//** Description:   Enable receive interrupt
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************
void radio_isr_disable(void)
{
    IRQSC_IRQIE = 0;    //Disable IRQ pin interrupt 
}

//***********************************************************************
//** Function:      radio_tx_on
//** 
//** Description:   Puts radio into transmit mode
//**
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void radio_tx_on(void) 
{
    spi_tx(CYP_RADIO, REG_CONTROL, (TX_ENABLE | AUTO_SYNTH_COUNT | AUTO_PA_DISABLE | PA_ENABLE));
} 

//***********************************************************************
//** Function:      radio_rx_on
//** 
//** Description:   Puts radio into receive mode
//**
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void radio_rx_on(void) 
{
    spi_rx(CYP_RADIO, REG_DATA_RX_A);
    spi_rx(CYP_RADIO, REG_RX_INT_STAT);
    spi_tx(CYP_RADIO, REG_CONTROL, (RX_ENABLE | AUTO_SYNTH_COUNT)); 
}   

//***********************************************************************
//** Function:      radio_off
//** 
//** Description:   Turns off Tx and Rx modules
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************
void radio_off(void)
{ 
    spi_tx(CYP_RADIO, REG_CONTROL, 0);
    spi_tx(CYP_RADIO, REG_RX_INT_EN, 0);
    spi_tx(CYP_RADIO, REG_TX_INT_EN, 0);
}

//***********************************************************************
// Function:      radio_rx_isr
// 
// Description:   
//      ISR for receiving data - called from isr.c
//      Uses interupt output pin from CYPRESS chip.
//      There may be more than 1 interrupt, therefore check for all interrupts
//
// Parameters:    None
// Returns:       None
//*********************************************************************** 
void radio_rx_isr(void) 
{
static uint8_t radio_irq;

    while(CYP_RADIO_IRQ) {
        radio_irq = spi_rx(CYP_RADIO, REG_RX_INT_STAT);

    //******************************
    // Invalid interupt  : reset radio
    //******************************
        if ((radio_irq & (RX_FULL_A|RX_EOF_A)) == 0) {
            radio_rx_sm_rst();
        }

    //******************************
    // RX_FULL_A  : read data byte
    //******************************
        if(radio_irq & RX_FULL_A) {
            if (rx_data_len < rx_buff_size) {
                *(rx_data_buff + rx_data_len) = spi_rx(CYP_RADIO, REG_DATA_RX_A);
                if(radio_irq & RX_VALID_A) {
                    *(rx_valid_buff + rx_data_len) = 0xFF;
                } else {
                    *(rx_valid_buff + rx_data_len) = spi_rx(CYP_RADIO, REG_VALID_RX_A);
                }
                rx_data_len++;
            } else {
                isr_status.radio_overflow = YES; 
            }
        } 

    //******************************
    // RX_radio_EOF_A
    //******************************
        if(radio_irq & RX_EOF_A){
            if(isr_status.radio_overflow == YES) {
                rx_data_len = 0;   
            }
            isr_status.radio_EOF = YES;
            isr_status.radio_isr_active = NO;
        }
    }
}

//***********************************************************************
//** Function:      radio_rx_data
//** 
//** Description:   Activates receive statemachine 
//**
//** Parameters:    char buffer_length - Amount of data to receive
//**                char rx_buffer     - Pointer to receive buffer
//**                char valid_buffer  - Pointer to valid bit buffer
//** Returns:       char               - Number of bytes received
//*********************************************************************** 

uint8_t   radio_rx_data(char buffer_length, char rx_buffer[], char valid_buffer[]) 
{

    if (isr_status.radio_EOF == YES) {     /* Has data been received? */
    /* Disable receive mode */
        radio_isr_disable(); 
        radio_off();
        isr_status.radio_isr_active = NO;
        isr_status.radio_overflow = NO;
        isr_status.radio_EOF = NO;
        return(rx_data_len);
    } else {
//
//  check if data collection is active
//
        if (isr_status.radio_isr_active == NO) { 
        /* Setup receive buffers*/
            rx_buff_size = buffer_length;
            rx_data_buff = rx_buffer;
            rx_valid_buff = valid_buffer;
      
        /* Setup flags */
            isr_status.radio_isr_active = YES;
            rx_data_len = 0;
            isr_status.radio_EOF = NO;
            isr_status.radio_overflow = NO;
      
         /* Enable receive mode */  
            radio_rx_on(); 
            delay_1ms();
            spi_tx(CYP_RADIO,REG_RX_INT_EN, (RX_FULL_A|RX_EOF_A));
            radio_isr_enable();
        }
    }
    return(0);
}

//***********************************************************************
//** Function:      radio_rx_sm_rst
//** 
//** Description:   Force receive statemachine to idle (all data lost)
//**
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void radio_rx_sm_rst(void)
{
    radio_off();
    isr_status.radio_isr_active = NO;
    isr_status.radio_EOF = NO;
    init_radio();
}

//***********************************************************************
//** Function:      radio_tx_data
//** 
//** Description:   Transmits array tx_buffer
//**
//** Parameters:    char buffer_length - Amount of data to transmit
//**                char tx_buffer     - Pointer to transmit buffer
//** Returns:       char               - Number of bytes transmitted
//*********************************************************************** 
char radio_tx_data(char buffer_length, char tx_buffer[])
{
uint8_t   i;
int       counter;
uint8_t   timeout=0;
  
    radio_tx_on();
    spi_tx(CYP_RADIO, REG_TX_INT_EN, TX_EMPTY);
    for(i = 0; i < buffer_length; ++i) { 
        for (counter = 0; (counter < DEADMAN_MAX_COUNT) && (!CYP_RADIO_IRQ); counter++) {
            if(counter > (DEADMAN_MAX_COUNT-2)) {
                timeout=1;
            }
        }
        spi_tx(CYP_RADIO, REG_DATA_TX, tx_buffer[i]);
    }
    spi_tx(CYP_RADIO, REG_TX_INT_EN, TX_EOF);
    for (counter = 0; (counter < DEADMAN_MAX_COUNT) && (!CYP_RADIO_IRQ); counter++) {
        if(counter > (DEADMAN_MAX_COUNT-2)) {
            timeout=1;
        }
    }
    radio_off();
  
    if (!timeout) {
        return(buffer_length);
    } else {
        return(0);
    }
}   

//***********************************************************************
//** Function:      radio_get_rssi
//** 
//** Description:   Returns current signal strength
//**
//** Parameters:    None
//** Returns:       char - Signal strength
//***********************************************************************     
char radio_get_rssi() 
{
char rssi;

    delay_1ms();
    radio_rx_on();
    delay_1ms();
    rssi = spi_rx(CYP_RADIO, REG_RSSI);
    if (!(rssi & RSSI_VALID)) {
        spi_tx(CYP_RADIO, REG_CARRIER_DETECT, 0);
        spi_tx(CYP_RADIO, REG_CARRIER_DETECT, CD_OVERRIDE);
        do {
            delay_100us();
            rssi = spi_rx(CYP_RADIO, REG_RSSI);
        } while (!(rssi & RSSI_VALID));
        spi_tx(CYP_RADIO, REG_CARRIER_DETECT, 0);
    }
    radio_off();
    return(rssi & RSSI_MASK);
}

//***********************************************************************
//** Function:      radio_get_id
//** 
//** Description:   Returns Cypress radio ID 
//**
//** Parameters:    None
//** Returns:       char - ID
//*********************************************************************** 
char radio_get_id() 
{
char data;

    data = spi_rx(CYP_RADIO, REG_ID);
    return(data);
}
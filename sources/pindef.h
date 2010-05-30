//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// pindef.h   : definition of used pins
// ========
//
// Chip     MC9S08AW60    64-pins
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           31/07/2008
//                    13/08/08     Added pin list (1->64) + set of spare pins
//----------------------------------------------------------------------------
//
// Pin names

#ifndef __pindef_H
#define __pindef_H

char __isflag_int(void);

#define MOTOR1_A        PTDD_PTDD6
#define MOTOR1_A_D      PTDDD_PTDDD6
#define MOTOR1_B        PTDD_PTDD7
#define MOTOR1_B_D      PTDDD_PTDDD7

#define MOTOR2_A        PTDD_PTDD4
#define MOTOR2_A_D      PTDDD_PTDDD4
#define MOTOR2_B        PTDD_PTDD5
#define MOTOR2_B_D      PTDDD_PTDDD5

#define CYP_RADIO_RST   PTCD_PTCD4
#define CYP_RADIO_RST_D PTCDD_PTCDD4
#define CYP_RADIO_SS    PTED_PTED4
#define CYP_RADIO_SS_D  PTEDD_PTEDD4
#define CYP_RADIO_IRQ   __isflag_int()

//#define PSX_ACK         FAKE_PORT
//#define PSX_ACK_D       FAKE_PORT
//#define PSX_SS          FAKE_PORT
//#define PSX_SS_D        FAKE_PORT

#define RED_SWITCH_1        PTAD_PTAD0
#define RED_SWITCH_2        PTAD_PTAD1
#define RED_SWITCH_4        PTAD_PTAD2
#define RED_SWITCH_8        PTAD_PTAD3
#define BLUE_SWITCH_1       PTAD_PTAD4
#define BLUE_SWITCH_2       PTAD_PTAD5
#define BLUE_SWITCH_4       PTAD_PTAD6
#define BLUE_SWITCH_8       PTAD_PTAD7

#define RED_LED             PTGD_PTGD3
#define GREEN_LED           PTGD_PTGD4

#define BATTERY_VOLTS_PIN   PTB4_AD1P4          // [38][analogue]
#define M1_IN1_PIN          PTF0_TPM1CH2        // [ 4][Output]
#define M1_IN2_PIN          PTF1_TPM1CH3        // [ 5][Output]
#define M2_IN1_PIN          PTE2_TPM1CH0        // [15][Output]
#define M2_IN2_PIN          PTE3_TPM1CH1        // [16][Output]  



//----------------------------------------------------------------------------
// Pin listing
//
//  Pin  Name               Used     Feature         Description
//  ===  ====               ====     =======         ===========
//   1   PTC4                Y                       Reset to Cypress CY6934 chip
//   2   IRQ                 Y                       Interrupt line from CY6934 chip
//   3   ~RESET              *
//   4   PTF0/TPM1CH2        Y         TPM1CH2       PWM channel for right motor
//   5   PTF1/TPM1CH3        Y         TPM1CH3       PWM channel for right motor
//   6   PTF2/TPM1CH4        -H
//   7   PTF3/TPM1CH5        -
//   8   PTF4/TPM2CH0        Y         TPM2CH0       servo channel 1
//   9   PTC6                Y         
//  10   PTF7                Y         
//  11   PTF5/TPM2CH1        Y         TPM2CH1       servo channel 2
//  12   PTF6                -H
//  13   PTE0/TxD1           Y         TxD1          serial port transmit
//  14   PTE1/RxD1           Y         RxD1          serial port receive
//  15   PTE2/TPM1CH0        Y         TPM1CH0       PWM channel for left motor
//  16   PTE3/TPM1CH1        Y         TPM1CH1       PWM channel for left motor
//  17   PTE4/~SS1           Y                       SPI system select
//  18   PTE5/MISO1          Y                       SPI input
//  19   PTE6/MOSI1          Y                       SPI output
//  20   PTE7/SPSCK          Y                       SPI clock
//  21   Vss                 *
//  22   Vdd                 *
//  23   PTG0/KBI1P0         Y         
//  24   PTG1/KBI1P1         Y         
//  25   PTG2/KBI1P2         Y         
//  26   PTA0                Y         PTA0          RED switch 1
//  27   PTA1                Y         PTA1          RED switch 2
//  28   PTA2                Y         PTA2          RED switch 4
//  29   PTA3                Y         PTA3          RED switch 8
//  30   PTA4                Y         PTA4          BLUE switch 1
//  31   PTA5                Y         PTA5          BLUE switch 2
//  32   PTA6                Y         PTA6          BLUE switch 4
//  33   PTA7                Y         PTA7          BLUE switch 8
//  34   PTB0/AD1P0          Y         AD1P0         LEFT motor volts A
//  35   PTB1/AD1P1          Y         AD1P0         LEFT motor volts B
//  36   PTB2/AD1P2          Y         AD1P0         RIGHT motor volts A
//  37   PTB3/AD1P3          Y         AD1P0         RIGHT motor volts B
//  38   PTB4/AD1P4          Y         AD1P4         battery voltage
//  39   PTB5/AD1P5          Y         
//  40   PTB6/AD1P6          Y         
//  41   PTB7/AD1P7          Y         
//  42   PTD0/AD1P8          Y         
//  43   PTD1/AD1P9          Y         
//  44   Vddad               *
//  45   Vssad               *
//  46   PTD2/KBI1P5/AD1P10  Y         
//  47   PTD3/KBI1P6/AD1P11  Y         
//  48   PTG3/KBI1P3         Y         
//  49   PTG4/KBI1P4         -                          
//  50   PTD4/TPM2CLK/AD1P12 Y         
//  51   PTD5/AD1P13         Y         
//  52   PTD6/TPM1CLK/AD1P14 -  
//  53   PTD7/KBI1P7/AD1P15  Y         
//  54   Vrefh               *
//  55   Vrefl               *
//  56   BKGD/MS             *
//  57   PTG5/XTAL           -
//  58   PTG6/EXTAL          -
//  59   Vss                 *
//  60   PTC0/SCL1           -H        SCL1          I2C clock line
//  61   PTC1/SDA1           -H        SDA1          I2C data line
//  62   PTC2/MCLK           Y         
//  63   PTC3/TxD2           Y         
//  64   PTC5/RxD2           Y         
//
//----------------------------------------------------------------------------
// Current spare lines
// ===================
//
//  1. PTF2/TPM1CH4        [ 6]   on header
//  2. PTF3/TPM1CH5        [ 7]
//  3. PTF5/TPM2CH1        [11]   on header
//  4. PTF6                [12]   on header
//  5. PTG4/KBI1P4         [50]   ** place on header ??
//  6. PTD6/TPM1CLK/AD1P14 [49]   ** place on header ??
//  7. PTG5/XTAL           [57]
//  8. PTG6/EXTAL          [58]
//
//----------------------------------------------------------------------------
// Extension header
// ================
//
//  Header pin    Chip pin     Chip function           Description
//  ==========    ========     =============           ===========
//
//       1           21             Vss
//       2           21             Vss
//       3           22             Vdd
//       4           11             PTF5/TPM2CH1
//       5            6             PTF2/TPM1CH4
//       6           12             PTF6
//       7           60             PTC0/SCL1          I2C clock
//       8           14             PTE1/RxD1          serial receive
//       9           61             PTC1/SDA1          I2C data
//      10           13             PTE0/TxD1          serial transmit
//      11           17             PTE4/~SS1          SPI select
//      12           20             PTE7/SPSCK         SPI clock
//      13           18             PTE5/MISO1         SPI data in
//      14           19             PTE6/MOSI1         SPI data out
//
//----------------------------------------------------------------------------
// Analogue channel listing
// ========================
//
//   Channel     Name               Pin      Description
//   =======     ====               ===      ===========
//      0      PTB0/AD1P0            34      Battery voltage
//      1      PTB1/AD1P1            35      POT 1
//      2      PTB2/AD1P2            36      POT 2
//      3      PTB3/AD1P3            37      POT 3
//      4      PTB4/AD1P4            38      joystick left switch
//      5      PTB5/AD1P5            39      joystick right switch
//      6      PTB6/AD1P6            40      left line sensor
//      7      PTB7/AD1P7            41      right line sensor
//      8      PTD0/AD1P8            42      front bump sensor 1
//      9      PTD1/AD1P9            43      front bump sensor 2
//     10      PTD2/KBI1P5/AD1P10    46      front bump sensor 3
//     11      PTD3/KBI1P6/AD1P11    47      (interrupt for left wheel sensor)
//     12      PTD4/TPM2CLK/AD1P12   50      (interrupt for right wheel sensor)
//     13      PTD5/AD1P13           51      rear sensor
//     14      PTD6/TPM1CLK/AD1P14   52      ----
//     15      PTD7/KBI1P7/AD1P15    53      (IR data channel input)
//
//----------------------------------------------------------------------------
// Pin assignment for each of the digitaL I/O ports
//
// PTDA   0    RED switch 1         PTA0                // [26][Input]    
//        1    RED switch 2         PTA1                // [27][Input]
//        2    RED switch 4         PTA2                // [28][Input]
//        3    RED switch 8         PTA3                // [29][Input]
//        4    Blue switch 1        PTA4                // [30][Input]
//        5    Blue switch 2        PTA5                // [31][Input]
//        6    Blue switch 4        PTA6                // [32][Input]
//        7    Blue switch 8        PTA7                // [33][Input]
//
#define     PORTA_DIR       0b00000000 
#define     PORTA_PULLUP    0b00000000
#define     PORTA_SLEWRATE  0b00000000
#define     PORTA_OUT_DRIVE 0b11111111 
#define     PORTA_INIT      0b01010101 
//----------------------------------------------------------------------------
// PTDB   0     BATTERY_VOLTS       PTB0_AD1P0          // [34][analogue]
//        1                         PTB1_AD1P1          // [35][analogue]
//        2                         PTB2_AD1P2          // [36][analogue]
//        3                         PTB3_AD1P3          // [37][analogue]
//        4                         PTB4_AD1P4          // [38][analogue]
//        5                         PTB5_AD1P5          // [39][analogue]
//        6                         PTB6_AD1P6          // [40][analogue]
//        7                         PTB7_AD1P7          // [41][analogue]
//
#define     PORTB_DIR           0b00000000
#define     PORTB_PULLUP        0b00000000
#define     PORTB_SLEWRATE      0b00000000
#define     PORTB_OUT_DRIVE     0b11111111  
#define     PORTB_INIT          0b00000000 
#define     PORTB_AD_CHAN_0_7   0b11111111 
//----------------------------------------------------------------------------
// PTDC   0    
//        1
//        2                         PTC2_MCLK           // [62][Input]
//        3                         PTC3_TxD2           // [63][Input]
//        4                         PTC4                // [ 1][Output]
//        5                         PTC5_RxD2           // [64][Input] 
//        6                         PTC6                // [ 9][Output]
//
#define     PORTC_DIR       0b01010000
#define     PORTC_PULLUP    0b00111100
#define     PORTC_SLEWRATE  0b00000000
#define     PORTC_OUT_DRIVE 0b11111111   
#define     PORTC_INIT      0b00000000
//----------------------------------------------------------------------------
// PTDD   0                         PTD0_AD1P8          // [42][analogue]
//        1                         PTD1_AD1P9          // [43][analogue]
//        2                         PTD2_KBI1P5_AD1P10  // [46][analogue]
//        3                         PTD3_KBI1P6_AD1P11  // [47][analogue]
//        4     
//        5                         PTD5/AD1P13         // [51][Analogue]   
//        6
//        7                         PTD7/KBI1P7/AD1P15  // [53][Input]
//
#define     PORTD_DIR           0b00000000
#define     PORTD_PULLUP        0b00000000
#define     PORTD_SLEWRATE      0b00000000
#define     PORTD_OUT_DRIVE     0b11111111 
#define     PORTD_INIT          0b00000000
#define     PORTD_AD_CHAN_8_15  0b00110111   
//----------------------------------------------------------------------------
// PTDE   0                         PTE0/TxD1           // [13][Serial Tx]
//        1                         PTE1/RxD1           // [14][Serial Rx]
//        2     M2_IN1              PTE2_TPM1CH0        // [15][Output]
//        3     M2_IN2              PTE3_TPM1CH1        // [16][Output]  
//        4                         SS                  // [17][Output]
//        5
//        6
//        7
//
#define     PORTE_DIR       0b00011100
#define     PORTE_PULLUP    0b00000000
#define     PORTE_SLEWRATE  0b00000000
#define     PORTE_OUT_DRIVE 0b11111111 
#define     PORTE_INIT      0b00000000  
//----------------------------------------------------------------------------
// PTDF   0     M1_IN1              PTF0_TPM1CH2        // [ 4][Output]    
//        1     M1_IN2              PTF1_TPM1CH3        // [ 5][Output]
//        2
//        3
//        4                         PTF4_TPM2CH0        // [ 8][Output]
//        5
//        6
//        7                         PTF7                // [10][Output]
//
#define     PORTF_DIR       0b00000011
#define     PORTF_PULLUP    0b00000000
#define     PORTF_SLEWRATE  0b00000000
#define     PORTF_OUT_DRIVE 0b11111111   
#define     PORTF_INIT      0b00000000
//----------------------------------------------------------------------------
// PTDG   0                         PTG0_KBI1P0         // [23][Output]     
//        1                         PTG1_KBI1P1         // [24][Output]
//        2                         PTG2_KBI1P2         // [25][Output]
//        3     RED_LED             PTG3_KBI1P3         // [48][Output]
//        4     GTEEN_LED           PTG4_KBI1P4         // [49][Input]
//        5
//        6 
//
#define     PORTG_DIR       0b00011000
#define     PORTG_PULLUP    0b00000000
#define     PORTG_SLEWRATE  0b00000000
#define     PORTG_OUT_DRIVE 0b11111111 
#define     PORTG_INIT      0b00000000  

#endif  /* __pindef_H */


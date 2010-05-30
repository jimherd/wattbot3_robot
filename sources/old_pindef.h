/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        pindef.h
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

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

#define PSX_ACK         FAKE_PORT
#define PSX_ACK_D       FAKE_PORT
#define PSX_SS          FAKE_PORT
#define PSX_SS_D        FAKE_PORT
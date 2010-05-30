//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// rti.c    handle RTI 8mS interrupt
// =====
//
// Description
//      RTI provides a simple regular 8mS interrupt that is used to execute
//      a series of actions that need to be handled on a regular basis.
//
//          Task 1 : count time units
//          Task 2 : sample set of switches and debounce
//          Task 3 : implement display flashing
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           31/07/2008    
//----------------------------------------------------------------------------

#include "global.h"

uint32_t    tick_count;         // 32-bit 8mS  counter

//----------------------------------------------------------------------------
// rti_isr : handle rti interrupt
// =======
//
// Description
//
// Notes
//         
//----------------------------------------------------------------------------
void rti_isr(void) 
{
//
// Timer interrupt occurs every 8mS.
//
// Task 1 : count time units
// 
//      Can be used by any routines that needs background timing (e.g. timeouts)
//      32-bit value that goes back to 0 after about 397 days      
//
    tick_count++;
  
}

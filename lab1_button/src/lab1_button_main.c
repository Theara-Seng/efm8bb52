//=========================================================
// src/lab1_button_main.c: generated by Hardware Configurator
//
// This file will be updated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!!
//=========================================================

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB52_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
// [Generated Includes]$

sbit led = P1^3;
sbit button = P1^4;
//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void
SiLabs_Startup (void)
{
  // $[SiLabs Startup]
  // [SiLabs Startup]$
}

void disable_watchdog(){
  WDTCN = 0xAD;
  WDTCN = 0xDE;
}
//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int
main (void)
{
  // Call hardware initialization routine
  enter_DefaultMode_from_RESET ();
  disable_watchdog();
  XBR2 |= XBR2_XBARE__ENABLED;
  P1MDIN |= P1MDIN_B3__DIGITAL | P1MDIN_B4__DIGITAL;
  P1MDOUT |= P1MDOUT_B3__PUSH_PULL;

  while (1)
    {
      if (button == 0 ){
          led = 1;
      }else{
          led  = 0;
      }
// $[Generated Run-time code]
// [Generated Run-time code]$
    }
}

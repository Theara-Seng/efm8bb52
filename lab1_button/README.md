# Push Button

In this lab, we will use a push button with an led. 

## Concept

When the button is pressed, the led will be on. Else the led will be off

## Programming 

* Disable the watchdog timer

```sh
void disable_watchdog(){
  WDTCN = 0xAD;
  WDTCN = 0xDE;
}
```

* Enable crossbar

```sh
 XBR2 |= XBR2_XBARE__ENABLED;
 ```
 
 * Declare as digital (P1_B3 as Led and P1_B4 as Button)

```sh
  P1MDIN |= P1MDIN_B3__DIGITAL | P1MDIN_B4__DIGITAL;
  ```

* Declare as push pull output (since led is P1_B3)
```sh
P1MDOUT |= P1MDOUT_B3__PUSH_PULL;
```

* Declare variable for P1_B3(LED) and P1_B4(BUTTON)

```sh
sbit led = P1^3;
sbit button = P1^4;
```

* Loop 

```sh 
if (button == 0 ){
          led = 1;
      }else{
          led  = 0;
      }
```
 The button is pull-up, so when the button is pressed , the led is on, else it is off
## The whole program 

 ```sh
 #include <SI_EFM8BB52_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"

sbit led = P1^3;
sbit button = P1^4;

void
SiLabs_Startup (void)
{
  // $[SiLabs Startup]
  // [SiLabs Startup]$
}

void 
disable_watchdog(){
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
```
 ##  Result
 
 As shown in the image below, everytime the button is low the led turns on 
 
 
![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab1_button/lab1_image/result.png)

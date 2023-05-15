# LED Blink


In this lab, we will blink an led using register of the efm8bb52 using debugger


## Watchdog Timer (WDT0)

We need to disable the watchdog timer as detail in the datasheet 

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab1_led/lab1_image/watchdog.png)

To disable the watchdog timer, we will use the **WDTCN** register as detailed in the image below

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab1_led/lab1_image/disable_watchdog.png)

So we will need to write 

```sh
  WDTCN = 0xAD;
  WDTCN = 0xDE;
 ```
 ## Function Description for Output
First we need to understand the function description of the efm8bb52 datasheet

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab1_led/lab1_image/function_description.png)


So the import thing to do first is to 

1. Declare as digital Mode
2. Push pull Output register
3. Enable the crossbar


## Declare as Digital Mode


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab1_led/lab1_image/digital_output.png)

So to declare as digital Mode, we need the register PnMDIN.n = 1 

Then we can go to the port register and select P1MDIN (we use PORT1 Bit 0 to Blink led) and declare as input 

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab1_led/lab1_image/digital.png)

```sh 
P1MDIN |= P1MDIN_B0__DIGITAL;
```

## Push Pull Output

To declare as push pull output, we need the register PnMDOUT.n = 1

Then we can go to the port register and select P1MDOUT and declare as output

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab1_led/lab1_image/push_pull.png)

```sh
P1MDOUT |= P1MDOUT_B0__PUSH_PULL;
```

## Enable the crossbare

To enable the crossbar, we can go to the XBR2 register and enable the XBAR as shown in the image below


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab1_led/lab1_image/xbar.png)

```sh
XBR2 |= XBR2_XBARE__ENABLED;
```

## Program 
The whole program as shown below

```sh
#include <SI_EFM8BB52_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"


void
SiLabs_Startup (void)
{
  disable_watchdog ()
  {
    WDTCN = 0xAD;
    WDTCN = 0xDE;
  }

}
void delay(){
  uint32_t i = 1;
  for ( i = 1; i<=400000; i++){

  }

}
//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int
main (void)
{

  enter_DefaultMode_from_RESET ();
  XBR2 |= XBR2_XBARE__ENABLED;  
  P1MDIN |= P1MDIN_B0__DIGITAL;
  P1MDOUT |= P1MDOUT_B0__PUSH_PULL;
  while (1)
    {
      P1_B0 = 1;
      delay();
      P1_B0 = 0;
      delay();

    }
}
```

## Result
Click Build and Debug, then we will see the result as the image below


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab1_led/lab1_image/output.png)

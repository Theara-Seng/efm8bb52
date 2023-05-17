# External Interrupt (using push button and a LED)

In this lab, we will use a push button with a led. Every time the button  is pressed, we use the external interrupt to detect the falling edge or rising edge, then the led will change the state.

But before we go into the program, we need to understand some register of the external interrupt.

## Interrupt Control Register 

There are two external interrupt with efm8bb52 which are EX0 and EX1, but before we enable it, we need to enable the global interrupt which is EA, 
![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab2_button_int/lab2_image/IE.png)
So we need to enable the global interrupt First 

```sh
IE_EA = 0;
```

After that we can enable the external interrupt EX0 or EX1, depend on which one you want to use. In this case, I use external interrupt 0.

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab2_button_int/lab2_image/EX0.png)

So we enable it by set:

```sh
IE_EX0 = 1;
```

## INT0 and INT1

The table below shows the configuration on what we want the external interrupt to detect, there are 4 configuration, which are:

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab2_button_int/lab2_image/detect.png)
1. Interrupt on falling Edge (TCON_IT0 = 1 and IN0PL = 0)
2. Interrupt on Rising edge (TCON_IT0 = 1 and IN0PL = 1)
3. Interrupt on low level (TCON_IT0 = 0 and IN0PL = 0)
4. Interrupt on high level (TCON_IT0 = 0 and IN0PL = 1)

So in order to use these 4 configuration, we need to check both register **TCON and IT01CF** 

## TCON (Timer Control)

So in order to detect falling edge or rising edge of the external interrupt 0, we need to set IT0 to 1.


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab2_button_int/lab2_image/TCON.png)

So, we can set the IT0 to 1 by:

```sh
TCON_IT0=1;
```

## IT01CF 

To detect falling edge we need to set IN0PL to 0 andIN0PL for rising edge 



![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab2_button_int/lab2_image/IT01CF.png)

So we can write a function to detect a rising edge

```sh
void detect_rising_edge(){
  TCON_IT0 = 1;
  IT01CF |= IT01CF_IN0PL__ACTIVE_HIGH | IT01CF_IN0SL__P0_3;
}
```

and falling edge 

```sh
void detect_falling_edge(){
  TCON_IT0 = 1;
  IT01CF |= IT01CF_IN0SL__P0_3;
}
```

## Interrupt Service routine

```sh
SI_INTERRUPT(INT0_ISR, INT0_IRQn){
   led = ~led;
}
```
for the interrupt service routine, we change the state of the led when it is falling edge or rising edge detect

## Programming

So the whole program can be found below:

```sh
//=========================================================
// src/lab2_button_main.c: generated by Hardware Configurator
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

sbit led = P0^4;
sbit button = P0^3;

void
SiLabs_Startup (void)
{
  // $[SiLabs Startup]
  // [SiLabs Startup]$
}

void
disable_watchdog(){
  WDTCN = 0xDE;
  WDTCN = 0XAD;
}

void
enable_interrupt(){
  IE_EA = 1;
  IE_EX0 = 1;

}
void
detect_rising_edge(){
  TCON_IT0 = 1;
  IT01CF |= IT01CF_IN0PL__ACTIVE_HIGH | IT01CF_IN0SL__P0_3;
}

void 
detect_falling_edge(){
  TCON_IT0 = 1;
  IT01CF |= IT01CF_IN0SL__P0_3;
}

SI_INTERRUPT(INT0_ISR, INT0_IRQn){
   led = ~led;
}

int
main (void)
{
  // Call hardware initialization routine
  enter_DefaultMode_from_RESET ();
  disable_watchdog();
  XBR2 |= XBR2_XBARE__ENABLED;
  P0MDIN |= P0MDIN_B3__DIGITAL | P0MDIN_B4__DIGITAL;
  P0MDOUT |= P0MDOUT_B4__PUSH_PULL;

  enable_interrupt();
  detect_rising_edge(); //change to falling edge if you want to detect falling edge
  while (1)
    {

    }
}
```

## Result 

### Falling edge detect

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab2_button_int/lab2_image/falling_edge.png)

So when the button is pressed, it detect the falling edge of the push button and change the state of the led

### Rising edge detect

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab2_button_int/lab2_image/rising_edge.png)

Detect the rising edge of the push button and change the state of the led.
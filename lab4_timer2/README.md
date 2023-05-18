# TIMER 2 INTERRUPT (16-BIT AUTO RELOAD)

In this lab, we will use timer 2 interrupt with 16 bit auto reload to generate a delay of 10HZ or 100ms 


## Clock Selection 
First we select the prescale clock by 


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab4_timer2/lab4_image/clock_sel.png)

So we chose the system clock of 24.5MHz with 8 prescaled clock which is equal to 3.0625MHz

we can write 

```sh
CLKSEL = CLKSEL_CLKSL__HFOSC0_clk24p5 | CLKSEL_CLKDIV__SYSCLK_DIV_8; // clksel= 30625000
```

Then we need to choose the timer2 clock control, as state in the image below 


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab4_timer2/lab4_image/clock_selection.png)

So we will use the system clock divide by 12 using the register TRM2CNO, so we will get timer2 clock control = 30625000/12 = 255208 :


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab4_timer2/lab4_image/t2xclk.png)

So we write:

```sh
TMR2CN0 |= TMR2CN0_T2XCLK__SYSCLK_DIV_12;  // timer2 clock control = 30625000/12 = 255208
```

##  interrupt 

Then we can enable the global interrupt and the timer2 interrupt using this register IE

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab4_timer2/lab4_image/interrupt.png)


## Timer 2 auto reload 

For the timer 2 auto reload, we need to find the value of TMR2RLL and TMR2RLH

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab4_timer2/lab4_image/16bit.png)

By the formula

$$F_{timer2} = \dfrac{F_{input clock}}{2^{16}-TMR2RLH:TMR2RLL}=> TMR2RLH:TMR2RLL= 65536-\dfrac{F_{timer2}}{F_{input clock}}=65536-\dfrac{255208}{10} = 40015= 0x9C4F$$

So we need to assign the value of TMR2RLL and TMR2RLH

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab4_timer2/lab4_image/tmr2rlh.png)
![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab4_timer2/lab4_image/tmr2rll.png)

we can write 

```sh
  TMR2RLL = 0x4F; // timer 2 reload low byte
  TMR2RLH = 0x9C; // timer 2 reload high byte
  ```
## Start the Timer2 

Then we can start the timer by the TMR2CN0 register
![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab4_timer2/lab4_image/start.png)

we can write 

```sh
 TMR2CN0_TR2 = 1; // start the timer2
```

## Interrupt Service Routine

In the interrupt service routine we need to clear flag after the timer is overflow 
![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab4_timer2/lab4_image/flag.png)

we can write 

```sh
SI_INTERRUPT(TIMER2_ISR, TIMER2_IRQn){
  TMR2CN0_TF2H = 0;  // clear the flag
  led = ~led; // Toggle the led
}
```

## Code
The whole program can be found below 

```sh
#include <SI_EFM8BB52_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
// [Generated Includes]$
sbit led = P1^3;
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

void
disable_watchdog(){
  WDTCN = 0xAD;
  WDTCN = 0xDE;
}
void crossbar_enable(){
  XBR2 = XBR2_XBARE__ENABLED;
  P1MDIN = P1MDIN_B3__DIGITAL;
  P1MDOUT = P1MDOUT_B3__PUSH_PULL;
}

void clock_select(){
  CLKSEL = CLKSEL_CLKSL__HFOSC0_clk24p5 | CLKSEL_CLKDIV__SYSCLK_DIV_8; // clksel= 30625000
  TMR2CN0 |= TMR2CN0_T2XCLK__SYSCLK_DIV_12;  // timer2 clock control = 30625000/12 = 255208
}

SI_INTERRUPT(TIMER2_ISR, TIMER2_IRQn){
  TMR2CN0_TF2H = 0;  // clear the flag
  led = ~led; // Toggle the led
}
// Generate a 10Hz
void timer2_16bit(){
  IE_EA = 1;  // Enable Global Interrupt
  IE_ET2 = 1; // Enable timer2 Interrupt

  // F_timer2 = (F_timer2_clock_control/(2^16 - TMR2RLH:TMR2RLL))=> TMR2RLH:TMR2RLL= 65536 - (F_timer2_clock_control/F_timer2)
  // TMR2RLH:TMR2RLL = 65536 - (255208/10) = 40015 = 0x9C4F
  TMR2RLL = 0x4F; // timer 2 reload low byte
  TMR2RLH = 0x9C; // timer 2 reload high byte
  TMR2CN0_TR2 = 1; // start the timer2

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
  crossbar_enable();
  clock_select();
  timer2_16bit();
  while (1)
    {
// $[Generated Run-time code]
// [Generated Run-time code]$
    }
}

```

## Result 

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab4_timer2/lab4_image/result1.png)

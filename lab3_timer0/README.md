# Timer 0 (Mode 0 13-bit and Mode 1 16-bit counter and timer)

In this lab, we will generate a delay using Timer 0 mode 0 and mode 1 which are 13-bit and 16-timer respectively

Before we take deeply into the timer, let's check the clock of the EFM8

## Clock 

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/clksel.png)

First we need to select the clock selection register. There are different type of clock selection as shown in the CLKSEL below


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/clksl.png)

So, we will choose the HFOSCO_clk24p5 which is the internal high frequency Oscillator 24.5MHz

Then we will use a clock source divider to devide the clock by using SYSCLK_DIV_32


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/divided.png)

So we can write 

```sh
 CLKSEL = CLKSEL_CLKSL__HFOSC0_clk24p5 | CLKSEL_CLKDIV__SYSCLK_DIV_32;
 ```
 
 It mean that the clock now is : $$CLKSEL = \dfrac{24.5\times 10^{6}}{32} = 765625$$
 
 ## Timer 0

There are 4 mode in Timer 0 and Timer 1 such as

* 8 bit auto-reload counter/timer mode
* 13 bit counter/timer mode
* 16 bit counter/timer mode
* Dual 8-bit counter/timer mode (Timer 0)

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/timer0.png)

but before we are going to discuss about the counter/timer mode we need to select the clock control which is used with the timer 0 and 1 first

### CKCON

First we need to select the clock control which is used with the timer 0 in this lab, the register is stated below

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/ckcon0.png)

In this CKCON0, we need to select, the system clock that we want to use, in this case, I select the prescale clock with 48 system clock divided

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/SCA.png)

So it mean the clock control frequency now is equal to 

$$\dfrac{765625}{48} = 15950$$

now the Finput clock is equal to 15950

In the code we can write 

```sh
CKCON0 = CKCON0_T0M__PRESCALE | CKCON0_SCA__SYSCLK_DIV_48;
```

After that we need to select the timer mode which we want to use which is TMOD register

### TMOD 

In this case since we want to use the timer, we need to select the CT0 TIMER and also T0M is selected for bot (MODE0 and MODE1) for both 13-bit and 16-bit 


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/tmod.png)

In the code we can write 

For 13-bit timer mode 0

```sh
TMOD = TMOD_CT0__TIMER | TMOD_T0M__MODE0 ; // select mode 0 (13 bit timer)
```

For 16-bit Timer Mode 1

```sh
 TMOD = TMOD_CT0__TIMER | TMOD_T0M__MODE1;  // Mode 1 timer 0 (16 Bit)
 ```
 
## 13-bit Counter/Timer (TH0:TL0)

For the 13 bit timer and counter we can find the formula by the image below 


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/mode0.png)
We see that for the 13-bit timer the formula is 

$$F_{TIMER0}= \dfrac{F_{Input Clock}}{2^{13}-TH0:TL0}= \dfrac{F_{Input Clock}}{8192-TH0:TL0}$$

So if we want to create a 10 millisecond delay we will get

$$ TH0:TL0=8192-\dfrac{F_{Input_Clock}}{F_{TIMER0}}= 8192-\dfrac{15950}{100}= 8032= 0x1F60 $$


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/13bit_timer.png)

As shown in the image above, the 13 bit timer is: TH0 is for 8 bits lenght and TL0 only from bit 0 to bit 4

So we need to shift the data by 3 bits to the left by 

```sh
0x1F60<<3 = FB00
```

Then we get the data now is FB00, by the TL0 is only for bit 0 to bit 4. so, we need to shift right for 3 for the TL0 

The code is 

```sh
TL0 = 0x00>>3;
TH0 = 0xFB;
```

## 16-bit Counter/Timer (TH0:TL0)

For the 16 bit Counter/Timer (TH0:TL0) mode, the formula can found in the image below


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/mode1.png)


We have 

$$ F_{TIMER0}=\dfrac{F_{Input Clock}}{2^{16}-TH0:TL0}= \dfrac{F_{Input Clock}}{65536-TH0:TL0}$$

So if want to generate a one second delay, we can find the 

$$ TH0:TL0 = 65536- \dfrac{F_{Input Clock}}{F_{Timer0}} = 65536 - 15950 = 49586 = 0xC1B2 $$

Then we can write

```sh
TL0 = 0xB2;
TH0 = 0xC1;
```
 
## TCON

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/TCON.png)

TCON register is the timer control register, when we set the TCON_TR0 = 1, the timer start counting up until the overflow from 0xFFFF for 16 bit timer to 0, but when there is a overflow the TF0 is set to 1

so we need to clear the TF0 also TR0 when there is a overflow, the program can be written as 

```sh
  TCON_TR0 = 1;
  while (TCON_TF0 == 0);
  TCON_TR0 = 0;
  TCON_TF0 = 0;
```

##  Program

The whole program can be found in the script below 

```sh
#include <SI_EFM8BB52_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
// [Generated Includes]$
sbit led = P1^3;
uint8_t low_bit;
uint8_t high_bit;
--------------------
void
SiLabs_Startup (void)
{
  // $[SiLabs Startup]
  // [SiLabs Startup]$
}
void
disable_watchdog ()
{
  WDTCN = 0xDE;
  WDTCN = 0xAD;
}
void
enable_crossbar ()
{
  XBR2 |= XBR2_XBARE__ENABLED;
  P1MDIN |= P1MDIN_B3__DIGITAL;
  P1MDOUT |= P1MDOUT_B3__PUSH_PULL;
}



// Timer 0 Mode 0 (13 Bit counter/Timer)

void
timer0_mode0(){
  // Generate a 10 millis second
  CKCON0 = CKCON0_T0M__PRESCALE | CKCON0_SCA__SYSCLK_DIV_48;  // clock control = 765625/48= 15950
 
  TMOD = TMOD_CT0__TIMER | TMOD_T0M__MODE0 ; // select mode 0 (13 bit timer)

  // time_delay = (Fckcon/(2^13 - TH0:TL0) => TH0:TL0 = 8192 - (Fckcon/time_delay) = 8192- (15950/100)= 8032= 1F60

  // since the data is 13 bit we need to shift left by 3 -> 1F60<<3 =FB00 , TH0 = 0xFB and TL0 = 00>>3;
  TL0 = 0x00>>3;
  TH0 = 0xFB;
  TCON_TR0 = 1; // start the timer
  while (TCON_TF0 == 0);
  TCON_TR0 = 0;
  TCON_TF0 = 0;
}

// Timer 0 Mode 1 (16 bit counter/Timer)
void
timer0_mode1 ()
{
  // Generate a 1 second delay.
  CKCON0 = CKCON0_T0M__PRESCALE | CKCON0_SCA__SYSCLK_DIV_48; //clock control = 765625/48 = 15,950
  TMOD = TMOD_CT0__TIMER | TMOD_T0M__MODE1;  // Mode 1 timer 0 (16 Bit)

  // time = (Fckcon/(65536-TH0:TL0))=> TH0:TL0 = 65536-Fckcon = 65536 - 15950= 49586 -> TH0=0xC1 and TL0=0xB2

  TL0 = 0xB2;
  TH0 = 0xC1;
  TCON_TR0 = 1;
  while (TCON_TF0 == 0);
  TCON_TR0 = 0;
  TCON_TF0 = 0;

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
  enable_crossbar ();

  CLKSEL = CLKSEL_CLKSL__HFOSC0_clk24p5 | CLKSEL_CLKDIV__SYSCLK_DIV_32 ; // clksel = 24.5MHz/32 =765625

  while (1)
    {
      led = 1;
      timer0_mode0 ();
      led = 0;
      timer0_mode1 ();
// $[Generated Run-time code]
// [Generated Run-time code]$
    }
}
```

So we write a code that turn on the led of 10ms and turn off the led for 1 second.

# Result


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/lab3_timer0/lab3_image/result.png)


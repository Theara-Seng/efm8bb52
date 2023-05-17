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


# LED Blink


In this lab, we will blink an led using register of the efm8bb52 using debugger

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



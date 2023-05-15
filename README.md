# efm8bb52

Configure the EFM8 to program from the usb-to-ttl

## Simplicity Studio Configuration

After Install Simplicity Studio then we need to need to add a product so that we dont need to create new project and select the IC every time

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/product.png)

As shown in the image above, after create a new product, we can choose the product name with the target chip which you use (this lab is used EFM8BB52F16G-C-QFN32)

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/product_name.png)

Then we can select on the the product name as shown in the image below and choose create new project


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/create_project.png)

Then we can choose si8051 Configurator Project as shown below


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/configuration.png)

Then give a project name 


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/project_name.png)

Then right click on the project and choose properties then you will see the properties setting, and click on the retarget serial as shown in the image below


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/target_serial.png)


## CustomMode Port I/O

Custom EFM8 by click on the custom_efm8.. as shown below

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/custom.png)

First we need to enable the crossbar by select on the PORT I/O  and enable crossbar


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/enable_crossbar.png)


After that click on the UART0


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/uart0.png)

Then Click on the pin P0.4 and select it **Digital Push-Pull Output**


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/p0_4.png)

and P0.5 with **Digital OpenDrain I/O**


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/p0_5.png)


## DefaultMode Peripherals

The defaultMode peripheral is next to defaultmode PORT I/O


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/peripheral.png)

First click on the clock control and change the clock source divider to **SYSCLK_PREDIV/1**


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/clock_control.png)

Then click on UART0 and WatchDog Timer and disable the watchdog timer as shown below

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/watchdog.png)

Go to timer and choose Timer 1 mode to **Mode 2: 8 bit counter/Timer** and change clock source to **use SYSCLK**


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/timer.png)

And change the **Target Overflow Frequency** to 230400 (115200 * 2) buadrate 


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/overflow_frequency.png)

Then you will see the baudrate in the UART0 is  115566 with is around 115200 


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/baudrate.png)

## Configure the path of efm8load 

Goes to efm8load which is in the **dist** of the efm8load main and copy the path 


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/dist_part.png)

Then go to advance setting in your computer 


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/advanced_setting.png)

and in the system properties choose **Environment Variables**


![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/environment_variable.png)

Then create new path and paste the path that you copied from the dist of efm8load

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/path.png)

## Code 

First we include the **retargetserial.h**

```sh
#include "retargetserial.h"
```

Then in the main function, let  SCON0_TI = 1 and print **Hello 8051**

```sh
 SCON0_TI = 1;
 RETARGET_PRINTF("Hello 8051\n");
```

**Then right click on the project and click build**

## Program the efm8

Right click on the project and click **Show In -> System Explorer** and then find the .hex file of your project.

In that path, right click and choose open in terminal then 

1. List the port with ``` efm8load -l```
2. Identified the CHIP with ``` efm8load -p COM11 -i```
3. Flash the chip with ``` efm8load -p COM11 -w .\hello_8051.hex```

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/list_port.png)
Then to print the message we can do ``` efm8load -p COM11 -m ```

![efm8bb52](https://github.com/Theara-Seng/efm8bb52/blob/main/image/print_message.png)



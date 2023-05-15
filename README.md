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


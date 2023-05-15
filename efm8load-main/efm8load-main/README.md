# EFM8 Bootloader and Serial Terminal Utility
This tool combines the `efm8load.py` created by [fishpepper](https://github.com/fishpepper/efm8load) with additional to which automatically set the device into bootloader mode, inspired by ESP32 auto-programmer circuit. Another key feature in this utility is allowing extra input argument to open serial terminal, so that the user can program and debug the device by printing the message on the terminal. This serial terminal is taken from [pyserial](https://github.com/pyserial/pyserial/blob/master/serial/tools/miniterm.py) miniterm example.

# Installation
To install this tool, download/clone the precompiled binary `efm8load.exe` located in `dist` directory, then add it to environment variable path on your computer. For example, if you clone the project in `D:\git\efm8load`, add this `D:\git\efm8load\dist` to your environment variable path, so that you can access `efm8load.exe` anywhere in your computer.

# Wiring
```
 UART-to-USB               EFM8 Device
+-----------+             +------------+
|        RTS| ----------> |RTS(C2K)    |
|           |             |            |
|        DTR| ----------> |DTR(C2D)    |
|           |             |            |
|        RXD| <---------- |TXD(P0.4)   |
|           |             |            |
|        TXD| ----------> |RXD(P0.5)   |
|           |             |            |
|        GND| ----------> |GND         |
|           |             |            |
|        3V3| ----------> |3V3         |
+-----------+             +------------+
```

# Usage
List available ports connected to your PC using the following command.
```
efm8load --list-port
```
You will get something like this:
```
> Available ports:
>  1: COM3                 'Silicon Labs CP210x USB to UART Bridge (COM3)'
>  2: COM11                'JLink CDC UART Port (COM11)'
```
In this example, UART-to-USB converter is connected to `COM3`. We can use the following command to flash the device:
```
efm8load -p COM3 -w filename.hex
```
`filename.hex` is the binary you obtain when building the project in Simplicity Studio. If you include UART print function in your program, you can open Serial terminal to view the log messages by using command below:
```
efm8load -p COM3 -m
```
You can also flash and open the terminal at the same time using the following command:
```
efm8load -p COM3 -m -w filename.hex
```

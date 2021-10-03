# BinaryClock


## Project Intro
This project was formed because most binary clocks are not actually that binary. I found it was necessary to make one in order to avoid a mix of binary and decimal in the display.
The PCB fits into a business card form factor and is effectively a few neopixels and an arduino. There are some pictures in the subfolder.

## Directions for use

### Power on
The device will display the time a few seconds after being plugged in
It will display the time in R:G:B in hours:minutes:seconds. The decimal values labelled beneath each light can be adde to convert to regular 24hr format.

### Set the time
The RTC is initiated with the time at noon. This can be altered wit hthe two buttons. SW1 adds an hour, SW2 adds a minute.

### Change the mode
If the standard mode is too easy to read, why not try a different on.
Press both buttons together to change the display mode. It will cycle through  
* RGB hours:minutes:seconds  
* scrolling rainbow hours:minutes:seconds  
* RGB hours:minutes:seconds with automatic dimming   
* Daily epoch mode. This is the number of seconds since the beginning of the day as a 17bit binary number  

## Hardware
This code goes with a PCB which can be viewed here https://oshwlab.com/mrmukukuchu/binary-business-card  
The microcontroller is an ATmega328 running the minicore bootloader with flags set to an internal 4MHz clock.
Some of the boards do not hold good enough clock timing to communicate properly so must be programmed via the ICSP header with an external crystal. This can be done using another arduino and no other hardware.  
There is a real time clock with temperature compensation. The package isn't ideal as it is quite thick but there was a chip shortage.  
There is a light sensor attached to A1 to allow the LED brightness to adapt to light in the room.  
Serial comms are handled by a CH340C which you may need to download the driver for. This also has an internal oscillator (chip shortage strikes again) so may be an alternate reason why some of the boards required the use of ICSP. The oscillator pins are broken out too and can be driven using an external crystal or an arduino if using arduino as ISP 

The pin numbering matches that of the arduino boards so it should meet the needs of future clock based projects.  
This was fabricated and populated by JLCPCB. EasyEDA was used to produce the board which is the software they provide. The built in component library helps avoid sourcing issues and has a filter for basic components which are on the SMT line anyway and therefore avoid a loading fee.

## Code
Visit https://github.com/MCUdude/MiniCore#getting-started-with-minicore before attempting to change the code. Your compiler must be setup with the right board definitions to allow functioning without an external oscillator.  
The boards is set to 4MHz which is the slowest it will run with the FastLED library. The leds are compatible with the neopixel library from adafruit but this implementation requires a higher clock speed. The reason for not using 8MHz is I found the serial comms more stable.  






MSX Virtual Printer v1.1
by cloudree@naver.com

It's a virtual printer for MSX.
All of your printing is stored to SD memory (txt, bin) and can be checked the contents via OLED display.

-------

Connect Printer cable with MSX as listed

MSX Printer - STM32F103 (bluepill)
PD0 - PB3
PD1 - PA15
PD2 - PA8
PD3 - PB14
PD4 - PB13
PD5 - PB12
PD6 - PB8
PD7 - PB4
STROBE - PB5
BUSY - PB15
GND - GND

SD memory - STM32F103 (bluepill)
MOSI(CMD) - PA7
MISO(DAT0) - PA6
SCK(CLK) - PA5
CS(DAT3/CD) - PA4 (pull up via 1K Ohm to 3.3V)
VCC - 3.3V
GND - GND

Piezo Buzzer - STM32F103 (bluepill)
PLUS - PB9
GND - GND

Arduino Source is at Arduino Folder. 
You need the "STM32duino" board library and standard SD library.
If you can program for MSX Graphics Printing, Please go ahead and let me know !

/*
  msxprardus : msx printer by arduino 
  msx virtual printer v1.0
  by cloudree@naver.com
  
  UART support : "Enabled generic Serial" is required to compile
*/

#include <Arduino.h>

#include "Common.h"
#include "Debug.h"
#include "Display.h"
#include "Storage.h"
#include "Printer.h"

void setup() 
{
    g_debug.setup();
    g_storage.setup();
    g_printer.setup();
    g_display.setup();
}

void loop() 
{
    g_debug.loop();
    g_storage.loop();
    g_display.loop();
    g_printer.loop();
}

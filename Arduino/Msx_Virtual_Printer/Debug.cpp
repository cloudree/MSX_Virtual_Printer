/*
 *  Debug.cpp
 *  by cloudree@naver.com
 */

#include <Arduino.h>
#include <String.h>
#include "Common.h"
#include "Debug.h"

CDebug g_debug;

inline void LED_setup() { pinMode( LED_BUILTIN, OUTPUT ); }
inline void LED_loop()  { digitalWrite( LED_BUILTIN, (millis()%1000)<500 ? LOW : HIGH ); }

#ifdef _DEBUG

# ifdef _DEBUG_BLE
#  include <SoftwareSerial.h>
SoftwareSerial Serial(PIN_BLE_RX,PIN_BLE_TX);
# endif

void CDebug::setup()
{
    LED_setup();
    Serial.begin( SERIAL_SPEED);
    // while ( !Serial.available() );  // wait until teminal action
    Serial.println( String(PRODUCT) + String(" ") + String(VERSION) + String(" by ") + String(CREATOR) );
}

void CDebug::loop()
{
    LED_loop();
    if( Serial.available() > 0)   // echo
    {
        int ch = Serial.read();
        Serial.write(ch);
    }
}
void CDebug::DBG(String msg)          { Serial.print(msg); }
void CDebug::DBGHEX(long int data)    { Serial.print( String(data, HEX) + " "); }
void CDebug::DBG(int num)             { Serial.print( String(num) + " "); }
void CDebug::DBGLN(String msg)        { Serial.println(msg); }
void CDebug::DBGHEXLN(long int data)  { Serial.print( String(data, HEX) + " "); }
void CDebug::DBGLN(int num)           { Serial.print( String(num) + " "); }
void CDebug::Dump(uint8_t len, uint8_t *buf)
{
  	for (int i = 0; i<len; i++) {
    		Serial.print(buf[i], HEX);
        if( i % 32 == 31 )
            Serial.println("");
        else
    		    Serial.print(",");
  	}
  	Serial.println("");
}
#else 
// not DEBUG
void CDebug::setup()  { LED_setup(); }
void CDebug::loop()   { LED_loop(); }
void CDebug::DBG(String msg)          {}
void CDebug::DBGHEX(long int data)    {}
void CDebug::DBG(int num)             {}
void CDebug::DBGLN(String msg)        {}
void CDebug::DBGHEXLN(long int data)  {}
void CDebug::DBGLN(int num)           {}
void CDebug::Dump(uint8_t len, uint8_t *buf) {}
#endif  // _DEBUG

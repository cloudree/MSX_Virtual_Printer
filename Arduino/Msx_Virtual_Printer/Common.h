/*
 *  Common.h
 *  by cloudree@naver.com
 */

// ======== Debug
//#define _DEBUG
//#define _DEBUG_BLE

#define PRODUCT   "MSX VPRN"
#define VERSION   "v1.1"
#define CREATOR   "cloudree"

const int PIN_LED         = PC13;
const int SERIAL_SPEED    = 9600;

// ======== Printer
const int pinBusy = PB15;
const int pinSTBb = PB5;
const int pinData[8] = { PB3,PA15,PA8,PB14, PB13,PB12,PB8,PB4 };  // D0~D7

// ======== Display
const int pinSCL = PB6;
const int pinSDA = PB7;

// ======== SD 
const int pinMOSI = PA7;
const int pinMISO = PA6;
const int pinSCK = PA5;
const int pinCS = PA4;
#define SD_DETECT_PIN pinCS

// ======== Buzzer
const int pinBuzzer = PB9;

inline bool CheckTime(int tick)
{
    return ( millis() % tick ) > ( tick / 2 );
}

// ======== SD State
const int nameLen = 8+1+3+1;

enum SD_State
{
    ERR_CANNOT = -2,    
    ERR_INIT = -1,
    ERR_YET = 0,
    NORMAL = 1
};

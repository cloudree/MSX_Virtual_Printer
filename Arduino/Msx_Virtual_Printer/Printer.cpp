/*
 *  Printer.cpp
 *  by cloudree@naver.com
 */

#include <Arduino.h>
#include "Common.h"
#include "Debug.h"
#include "Printer.h"
#include "Display.h"
#include "Storage.h"

CPrinter g_printer;

// buffer
volatile int recvChar = 0;

void setBusy( bool isBusy )
{
    recvChar = 0;
    digitalWrite( pinBusy, isBusy ? HIGH : LOW );
}

void ISR_read() 
{
    setBusy( true );     // WAIT
    int data = 0;
    for( int i=7; i>=0; i-- )
    {
        int rd = (digitalRead( pinData[i] ) == HIGH) ? 1 : 0;
        data = (data << 1) | rd;
    }
    recvChar = data;
}

void CPrinter::buzzer()
{
    digitalWrite( pinBuzzer, HIGH );
    delay(1);
    digitalWrite( pinBuzzer, LOW );
}

void CPrinter::setup()
{
    for(int i=0; i<8; i++ )
    {
        pinMode( pinData[i], INPUT );
    }
    pinMode( pinBusy, OUTPUT );
    pinMode( pinSTBb, INPUT_PULLUP );
    attachInterrupt( digitalPinToInterrupt( pinSTBb ), ISR_read, FALLING );
    setBusy( false );     // ready to RECV

    pinMode( pinBuzzer, OUTPUT );
    buzzer();
    posc_ = 0;
}

const int lineFeed = 10;
inline bool isLineMove(int c)
{
    return ( c == lineFeed );
}

void CPrinter::loop()
{
    // yet no data
    if( recvChar == 0 ) return;
    int ch = recvChar;
    setBusy( false );     // continue RECV
    
    // special char
    switch( ch )
    {
    case 8 : // BS
        if( posc_ > 0 )
            lineBuf_[ --posc_ ] = 0;
    case 1 : // special cde
    case 9 : // TAB
    case 12 : // FF
    case 14 : // double width
    case 15 : // normal width
    case 29 : // Start Setting
    case 30 : // End Setting
    case 31 :
        return;

    case 27 : // ESC sequence
        return;           
                    
    case 11 : // VTAB
        recvChar = 13;    // CR
        break;
    case 10 : // LF
    case 13 : // CR
        break;
    }
    
    addChar( ch );
}

void CPrinter::addChar( char ch )
{    
    // char processing
    if( posc_ < prirter_columns ) 
    {
        lineBuf_[ posc_ ] = ch;
        lineBuf_[ ++posc_ ] = 0;
        buzzer();
        
        // SD bin log
        g_storage.copyChar( ch );
    }

    // line processing
    if( posc_ >= prirter_columns || isLineMove(ch) )
    {
        // SD txt log
        g_storage.copyLine( lineBuf_ );
        
        // oled line buffer
        g_display.copyLine( lineBuf_ );

        // debug
        g_debug.DBG( lineBuf_ );
        
        // buffer clear
        memset( lineBuf_, 0, sizeof(lineBuf_) );
        posc_ = 0;
    }
}

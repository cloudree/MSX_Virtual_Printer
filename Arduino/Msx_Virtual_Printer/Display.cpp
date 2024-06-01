/*
 *  Display.cpp
 *  by cloudree@naver.com
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include "Common.h"
#include "Debug.h"
#include "Display.h"
#include "Printer.h"
#include "Storage.h"

CDisplay g_display;

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void CDisplay::setup()
{
    u8g2.begin();
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    
    // initial OLED message
    strcpy( screenBuf_[0], PRODUCT " " VERSION );
    strcpy( screenBuf_[1], " by " CREATOR);
    SD_State st = g_storage.getSD_State();
    if( st != NORMAL )
    {
        char buf[30];
        sprintf( buf, "SD ERROR %d", st );
        strcpy( screenBuf_[2], buf);
    }
    line_ = -1;   // startup msg
}

void CDisplay::loop()
{
    u8g2.firstPage();
    do {
        for( int i=0; i<display_lines; i++ )
        {
            if( i == line_ && line_ >= 0 )
            {
                u8g2.drawStr( 0, i*11, g_printer.getLine() );
                break;
            }
            else
                u8g2.drawStr( 0, i*11, screenBuf_[i] );            
        }
    } while( u8g2.nextPage() );
}

void CDisplay::copyLine( char *szLine )
{
    if( line_ < 0 )
        line_ = 0;    // remove startup msg
        
    if( line_ < display_lines-1 )   // 0,1,2,3
    {
        copyBuffer( line_, szLine );
    }

    if( line_ == display_lines-1 )    // 4
    {
        // scroll
        for( int i=0; i<display_lines-2; i++ )   // 0,1,2
        {
            strcpy( screenBuf_[i], screenBuf_[i+1] );       // [0,1,2] <= [1,2,3]
        }
        copyBuffer( line_-1, szLine );    // 3 <= old lineBuf_
    }
    else
        line_ ++;    
}

void CDisplay::copyBuffer( int line, char *szLine )
{
    strncpy( screenBuf_[line], szLine, display_columns );     // 3 <= old lineBuf_
    screenBuf_[line][display_columns-1] = 0;  // cut at screen end
}

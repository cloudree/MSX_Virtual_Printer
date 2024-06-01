/*
  Storage.cpp
  by cloudree@naver.com
  with stm32SD
*/

#include <Arduino.h>
#include <SD.h>
#include "Common.h"
#include "Debug.h"
#include "Storage.h"
#include "Printer.h"

CStorage g_storage;

const int  maxNum = 999;
const char *filenameTxt = "msx_%03d.txt";
const char *filenameBin = "msx_%03d.bin";

void CStorage::setup()
{
    eSD_ = ERR_YET;

    pinMode(PC13, OUTPUT);
    if (!SD.begin(pinCS)) {
        g_debug.DBG("Card failed, or not present, NO File logging");
        eSD_ = ERR_INIT;
        return;
    }

    // search an available file name
    for( int i=0; i<=maxNum; i++ )
    {
        sprintf( szTxtFilename_, filenameTxt, i );
        sprintf( szBinFilename_, filenameBin, i );
        if( SD.exists( szTxtFilename_ ) == 0 && SD.exists( szBinFilename_ ) == 0 )
        {
            g_debug.DBG( szTxtFilename_ );
            g_debug.DBG( szBinFilename_ );
            eSD_ = NORMAL;
            return;
        }
    }
    eSD_ = ERR_CANNOT;
}

void CStorage::loop()
{
    
}

void CStorage::copyChar( char c )
{
    if( eSD_ != NORMAL )
        return;
        
    File fd = SD.open(szBinFilename_, FILE_WRITE);
    fd.print( c );
    fd.close();  
}

void CStorage::copyLine( char *szLine )
{
    if( eSD_ != NORMAL )
        return;
        
    File fd = SD.open(szTxtFilename_, FILE_WRITE);
    fd.print( szLine );
    fd.close();
}

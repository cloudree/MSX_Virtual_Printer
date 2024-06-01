/*
 *  Display.h
 *  by cloudree@naver.com
 */

const int display_columns = 16;    // width
const int display_lines = 5;       // height
    
class CDisplay
{
public:
    void setup();
    void loop();  

    void copyLine( char *szLine );
    
protected:
    int   line_;
    char  screenBuf_ [display_lines-1] [display_columns];
    void  copyBuffer( int line, char *szLine );
};

extern CDisplay g_display;

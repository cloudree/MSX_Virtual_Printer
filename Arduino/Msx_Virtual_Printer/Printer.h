/*
 *  Printer.h
 *  by cloudree@naver.com
 */

const int prirter_columns = 136;

class CPrinter
{
public:
    void  setup();
    void  loop();
    void  buzzer();
    char  *getLine()  { return lineBuf_; }

protected:
    void  addChar( char ch );
    int   posc_;
    char  lineBuf_[ prirter_columns+1 ];
};

extern CPrinter g_printer;

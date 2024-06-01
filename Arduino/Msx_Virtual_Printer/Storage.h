/*
 *  Storage.h
 *  by cloudree@naver.com
 */

class CStorage
{
public:
    void  setup();
    void  loop();
    void  copyChar( char c );
    void  copyLine( char *szLine );
    SD_State  getSD_State()   { return eSD_; }

protected:
    SD_State  eSD_;
    char  szTxtFilename_[nameLen];    // ...Txt
    char  szBinFilename_[nameLen];    // ...Bin
};

extern CStorage g_storage;

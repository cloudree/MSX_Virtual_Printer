/*
 *  Debug.h
 *  by cloudree@naver.com
 */

class CDebug
{
public:    
    void setup();
    void loop();
    
    void DBG(String msg);
    void DBGHEX(long int data);
    void DBG(int num);
    void DBGLN(String msg);
    void DBGHEXLN(long int data);
    void DBGLN(int num);
    void Dump(uint8_t len, uint8_t *buf);
};

extern CDebug g_debug;

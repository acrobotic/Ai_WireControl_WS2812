#ifndef _SYSTEM_STATE_H_
#define _SYSTEM_STATE_H_
#include <Adafruit_NeoPixel.h>

enum {SYS_ERR_BUF_SZ=50};

class SystemState {

    public:
        SystemState();
        void initialize();
        Adafruit_NeoPixel blinker;
        bool setPixel(uint16_t i, uint8_t r, uint8_t g, uint8_t b);
        uint16_t getNumPixels();

        void setErrMsg(char *);
        char errMsg[SYS_ERR_BUF_SZ];        
    private:
        uint16_t 
          _numPixels,
          _devPin;
};

extern SystemState systemState;

#endif

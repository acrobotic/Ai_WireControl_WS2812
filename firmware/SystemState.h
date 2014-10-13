#ifndef _SYSTEM_STATE_H_
#define _SYSTEM_STATE_H_
#include "NeoPixel.h"

class SystemState {

    public:
        SystemState();
        void initialize();
        NeoPixel blinker;
        bool setPixel(uint16_t i, uint8_t r, uint8_t g, uint8_t b);
        uint16_t getNumPixels();

        void setErrMsg(char *);
        char errMsg[50];        
    private:
        uint16_t 
          _numPixels,
          _devPin;
};

extern SystemState systemState;

#endif

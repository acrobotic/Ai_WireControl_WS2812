#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "SystemState.h"

SystemState::SystemState() : 
    blinker(constants::numPixels,
            constants::devPin) 
{
    _numPixels = constants::numPixels;
    _devPin = constants::devPin;
}

void SystemState::initialize() 
{
    blinker.begin();
    blinker.show();
}

bool SystemState::setPixel(uint16_t i, uint8_t r, uint8_t g, uint8_t b)
{
    blinker.setPixelColor(i, r, g, b);
    blinker.show();
    return true;
}

bool SystemState::setPixel(uint16_t i, uint32_t c)
{
    blinker.setPixelColor(i, c);
    blinker.show();
    return true;
}

bool SystemState::setPixels(uint8_t r, uint8_t g, uint8_t b)
{
    for(;;)
    {}
    return true;
}

bool SystemState::clearPixels()
{
    for(int i=0; i<_numPixels; i++)
      blinker.setPixelColor(i,0);    
    blinker.show();
    return true;
}

uint16_t SystemState::getNumPixels()
{
    return _numPixels;
}

SystemState systemState;

#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "SystemState.h"

SystemState::SystemState() : 
    blinker(60,
            1,NEO_GRB + NEO_KHZ800) 
{
    _numPixels = 60;
    _devPin = 0;
}

void SystemState::initialize() 
{
    blinker.begin();
    blinker.show();
    blinker.setPixelColor(5,blinker.Color(0,0,255));
    blinker.setPixelColor(10,blinker.Color(255,0,255));
    blinker.show();
}

bool SystemState::setPixel(uint16_t i, uint8_t r, uint8_t g, uint8_t b)
{
    blinker.setPixelColor(i, r, g, b);
    blinker.show();
    return true;
}

uint16_t SystemState::getNumPixels()
{
    return _numPixels;
}

SystemState systemState;

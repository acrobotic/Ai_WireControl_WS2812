#include <Adafruit_NeoPixel.h>
#include <TinyWireS.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 1, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  TinyWireS.begin(4);
  TinyWireS.onReceive(receiveEvent);
}

void loop() { 
  TinyWireS_stop_check();
}

void receiveEvent(uint8_t howMany)
{
}

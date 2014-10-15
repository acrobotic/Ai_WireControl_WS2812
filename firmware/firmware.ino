//#include <SerialReceiver.h>
#include "Adafruit_NeoPixel.h"
//#include "MessageHandler.h"
//#include "SystemState.h"
//#include <SoftwareSerial.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 1, NEO_GRB + NEO_KHZ800);


void setup() {

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'


  //messageHandler.initialize();
  //systemState.initialize();
}

void loop() { 
  //messageHandler.processMsg(); 
  strip.setPixelColor(2, strip.Color(127, 127, 127));
  strip.show();
  delay(100);
}

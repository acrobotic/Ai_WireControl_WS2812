#include <Adafruit_NeoPixel.h>

#include <TinyWireS.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 1, NEO_GRB + NEO_KHZ800);

void setup() {
  TinyWireS.begin(4);                // join i2c bus with address #4
  TinyWireS.onReceive(receiveEvent); // register event
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(uint8_t howMany)
{
  while(1 < TinyWireS.available()) // loop through all but the last
  {
    //char c = TinyWireS.read(); // receive byte as a character
  }
  //int x = TinyWireS.read();    // receive byte as an integer
}


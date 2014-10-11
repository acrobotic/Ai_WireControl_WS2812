#include <SerialReceiver.h>
#include <DictPrinter.h>
#include <Adafruit_NeoPixel.h>
#include "MessageHandler.h"
#include "SystemState.h"
#include <SoftwareSerial.h>

#define __AVR_ATtiny85__

void setup() {
  systemState.initialize();
  messageHandler.initialize();
}

void loop() { 
  messageHandler.processMsg(); 
}

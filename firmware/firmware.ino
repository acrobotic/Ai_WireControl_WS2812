#include <SerialReceiver.h>
#include <DictPrinter.h>
#include <Adafruit_NeoPixel.h>
#include "MessageHandler.h"
#include "SystemState.h"
#include "constants.h"

void setup() {
  Serial.begin(constants::baudrate);
  systemState.initialize();
}

void loop() { 
  messageHandler.processMsg(); 
}

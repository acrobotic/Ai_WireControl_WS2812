#include <SerialReceiver.h>
#include "NeoPixel.h"
#include "MessageHandler.h"
#include "SystemState.h"
#include <SoftwareSerial.h>

void setup() {
  systemState.initialize();
}

void loop() { 
  messageHandler.processMsg(); 
}

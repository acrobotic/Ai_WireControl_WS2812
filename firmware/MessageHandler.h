#ifndef _MESSAGE_HANDER_H_
#define _MESSAGE_HANDER_H_
#include <SerialReceiver.h>
#include "SystemState.h"
#include <SoftwareSerial.h>

#define rxPin 3
#define txPin 4

class MessageHandler : public SerialReceiver {

  public:
    void processMsg();
    void initialize();

  private:
    void msgSwitchYard();

    bool checkNumberOfArgs(int num);
    void systemCmdRsp(bool flag);

    void handleSetPixel();
    void handleSetNumPixels();

};

extern MessageHandler messageHandler;
#endif

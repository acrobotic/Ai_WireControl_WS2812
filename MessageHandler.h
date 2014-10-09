#ifndef _MESSAGE_HANDER_H_
#define _MESSAGE_HANDER_H_
#include <SerialReceiver.h>
#include <DictPrinter.h>
#include "constants.h"

class MessageHandler : public SerialReceiver {

  public:
    void processMsg();
    void processMsgBLE(char *data, int len);

  private:
    DictPrinter dprint;
    void msgSwitchYard();

    bool checkNumberOfArgs(int num);
    void systemCmdRsp(bool flag);

    void handleGetDevInfo();
    void handleGetCmds();
    void handleGetRspCodes();
    void handleSetPixel();
    void handleSetPixelPacked();
    void handleClearPixels();
    void handleGetNumPixels();
    void handleSetNumPixels();

    // DEV
    void handleDebug();
};

extern MessageHandler messageHandler;
#endif

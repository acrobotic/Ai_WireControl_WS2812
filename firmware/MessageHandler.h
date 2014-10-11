#ifndef _MESSAGE_HANDER_H_
#define _MESSAGE_HANDER_H_
#include <SerialReceiver.h>
#include <DictPrinter.h>

class MessageHandler : public SerialReceiver {

  public:
    void processMsg();
    void initialize();

  private:
    DictPrinter dprint;
    void msgSwitchYard();

    bool checkNumberOfArgs(int num);
    void systemCmdRsp(bool flag);

    void handleSetPixel();
    void handleSetNumPixels();

};

extern MessageHandler messageHandler;
#endif

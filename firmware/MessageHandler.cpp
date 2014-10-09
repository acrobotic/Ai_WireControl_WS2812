#include "MessageHandler.h"
#include "SystemState.h"

enum 
{
  cmdGetDevInfo,              // Done
  cmdGetCmds,                 // Done
  cmdGetRspCodes,             // Done
  cmdSetPixel,                // Done
  cmdSetPixelPacked,          // Not done
  cmdClearPixels,             // Done
  cmdGetNumPixels,            // Done
  cmdSetNumPixels,            // Not done

  // DEV
  cmdDebug,                   // Done
};

const int rspSuccess = 1;
const int rspError = 0;

void MessageHandler::processMsg() 
{
  while (Serial.available() > 0) 
  {
    process(Serial.read());
    if (messageReady()) 
    {
        msgSwitchYard();
        reset();
    }   
  }
  return;
}

void MessageHandler::msgSwitchYard() 
{
  int cmd = readInt(0); 
  dprint.start();
  dprint.addIntItem("cmdId", cmd);

  switch (cmd) 
  {
    case cmdGetDevInfo:
      handleGetDevInfo();
      break;

    case cmdGetCmds:
      handleGetCmds();
      break;

    case cmdGetRspCodes:
      handleGetRspCodes();
      break;

    case cmdSetPixel:
      handleSetPixel();
      break;

    case cmdSetPixelPacked:
      handleSetPixelPacked();
      break;

    case cmdClearPixels:
      handleClearPixels();
      break;

    case cmdGetNumPixels:
      handleGetNumPixels();
      break;

    case cmdSetNumPixels:
      handleSetNumPixels();
      break;

    //DEV
    case cmdDebug:
      handleDebug();
      break;

    default:
      dprint.addIntItem("status", rspError);
      dprint.addStrItem("errMsg", "unknown command");
      break;
    }              
    dprint.stop();
}

void MessageHandler::handleGetDevInfo() 
{
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("ModelNumber",  constants::deviceModelNumber);
  dprint.addIntItem("SerialNumber", constants::deviceSerialNumber); 
}

void MessageHandler::handleGetCmds() 
{
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("getDevInfo", cmdGetDevInfo);
  dprint.addIntItem("getCmds", cmdGetCmds); 
  dprint.addIntItem("getRspCodes", cmdGetRspCodes);
  dprint.addIntItem("setPixel", cmdSetPixel);
  dprint.addIntItem("setPixelPacked", cmdSetPixelPacked);
  dprint.addIntItem("clearPixels", cmdClearPixels);
  dprint.addIntItem("getNumPixels", cmdGetNumPixels);

  // DEV
  dprint.addIntItem("cmdDebug", cmdDebug);
}

void MessageHandler::handleGetRspCodes() 
{
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("rspSuccess",rspSuccess);
  dprint.addIntItem("rspError", rspError);
}

void MessageHandler::systemCmdRsp(bool flag) 
{
    if (flag) 
    {
        dprint.addIntItem("status", rspSuccess);
    }
    else 
    {
        dprint.addIntItem("status", rspError);
        dprint.addStrItem("errMsg", systemState.errMsg); 
    }
} 

// TO-DO: validate r, g, b ranges
void MessageHandler::handleSetPixel() 
{
    if (!checkNumberOfArgs(5)) {return;}
    uint16_t i = readInt(1);
    //uint16_t y = readInt(1);
    uint8_t r = readInt(2);
    uint8_t g = readInt(3);
    uint8_t b = readInt(4);
    systemCmdRsp(systemState.setPixel(i,r,g,b));
}

void MessageHandler::handleSetPixelPacked() 
{
}

void MessageHandler::handleClearPixels() 
{
    systemCmdRsp(systemState.clearPixels());
}

void MessageHandler::handleGetNumPixels() 
{
    dprint.addIntItem("numPixels", systemState.getNumPixels());
    dprint.addIntItem("status", rspSuccess);
}

void MessageHandler::handleSetNumPixels() 
{
}

bool MessageHandler::checkNumberOfArgs(int num) 
{
    bool flag = true;
    if (numberOfItems() != num) {
        dprint.addIntItem("status", rspError);
        dprint.addStrItem("errMsg", "incorrect number of arguments");
        flag = false;
    }
    return flag;
}

// DEV
void MessageHandler::handleDebug() 
{
  char name[20];
  dprint.addIntItem("status", rspSuccess);
}

MessageHandler messageHandler;

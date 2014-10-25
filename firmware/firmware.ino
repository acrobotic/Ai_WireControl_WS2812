#include <Adafruit_NeoPixel.h>
// Get this from https://github.com/rambo/TinyWire
#include <TinyWireS.h>

// the 7-bit address (remember to change this when adapting this example)
#define I2C_SLAVE_ADDRESS 0x4 

// The default buffer size, Can't recall the scope of defines right now
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif

//Character variable used to echo data back. 
char chrSendData;

//Variables used in getting and parsing data.
char rxChrData; //Receives the data.
char rxString[12];  //Varbiable for holding one string of data.
int rxIndex = 0; //Used to index rxString.

//Integer for holding the pwm value received from master.
int index;
uint8_t pin = 3;
uint16_t numPixels = 60;
int status = 1;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel *strip_ptr = &strip;

void requestEvent(){  
  TinyWireS.send(status);
}

//Handles receiving i2c data.
void receiveEvent(uint8_t howMany)
{
    status = 1;
    if (TinyWireS.available()){  
      if (howMany < 1)
      {   // Sanity-check
          return;
      }
      if (howMany > TWI_RX_BUFFER_SIZE)
      {   // Also insane number
          return;
      }
  
      howMany--;
      if (!howMany)
      {   // This write was only to set the buffer for next read
          return;
      }

      while(howMany--)
      {   //Gets i2c data. 
        uint16_t idx;
        uint8_t cmd,r,g,b;

        if (TinyWireS.receive() == '[')
        {
          cmd = TinyWireS.receive();
          switch(cmd)
          {
            case 0:
              idx = TinyWireS.receive();
              r = TinyWireS.receive();
              g = TinyWireS.receive();
              b = TinyWireS.receive();
              strip_ptr->setPixelColor(idx,r,g,b);
              break;

            case 1:
              r = TinyWireS.receive();
              g = TinyWireS.receive();
              b = TinyWireS.receive();
              for(int i=0; i<strip_ptr->numPixels(); i++)
              {
                strip_ptr->setPixelColor(i,r,g,b);
              }
              break;

            case 2:
              for(int i=0; i<strip.numPixels(); i++)
              {
                strip_ptr->setPixelColor(i,0,0,0);
              }
              break;

            default:
              break;
          }
          if (TinyWireS.receive() == ']')
          {
            strip.show();
            status = 0;
            break;
          }
        }
      }
    }
}

void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

    TinyWireS.begin(I2C_SLAVE_ADDRESS);
    //Sets up the onReceive function (what we do if we get stuff).
    TinyWireS.onReceive(receiveEvent);
    //Sets up the onRequest function (what we do if asked to send something).
    TinyWireS.onRequest(requestEvent);
}

void loop()
{
  //Detects a stop sending command.
  TinyWireS_stop_check();
}

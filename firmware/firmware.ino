#include <Adafruit_NeoPixel.h>
#include <TinyWireS.h>

// the 7-bit address (remember to change this when adapting this example)
#define I2C_SLAVE_ADDRESS 0x4 

// Get this from https://github.com/rambo/TinyWire
#include <TinyWireS.h>

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

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 3, NEO_GRB + NEO_KHZ800);

void requestEvent(){  
  TinyWireS.send(chrSendData);
}

//Handles receiving i2c data.
void receiveEvent(uint8_t howMany)
{
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
          rxChrData = TinyWireS.receive();
          //Places the characters in an array one at a time.
          rxString[rxIndex] = char(rxChrData);
          //Increment the data array.
          rxIndex++;

          //If a stop character is read, parse the char array and convert it to a single integer.  
          if (char(rxChrData) == ']'){
          //if (1){
              //This is a low memory form of parsing the char array into an intger
              //index = int(100*rxString[0]+10*rxString[3]+rxString[4]);

              index = rxString[rxIndex-1];

              //Resets the char array index.
              rxIndex = 0;  

              strip.setPixelColor(rxString[0],rxString[1],rxString[2],rxString[3]);
              strip.show();
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

  //Puts the data we got into a variable to send back for error checking.
  chrSendData = char(rxChrData);
}

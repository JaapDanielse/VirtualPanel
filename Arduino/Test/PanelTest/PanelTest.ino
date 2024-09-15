#include "VirtualPanel.h"

// Clock (using PanelOne) 
// for SAM architecture (Arduino Due) redefine the F() macro 
// #ifdef ARDUINO_ARCH_SAM 
//   #undef F
//   #define F(string_literal) (string_literal) 
// #endif

#include <TimeLib.h>  

boolean Graphmode = false;
boolean Monmode = false;
boolean Infomode = false;

#define MaxColNum 8 //

const char * Color[] = {"$WHITE","$YELLOW","$ORANGE","$RED","$GREEN","$BLUE","$PURPLE","$BROWN","$GRAY"};
int ColNum = 0;

byte GraphValue=0;

void setup()
{

#ifdef ARDUINO_SAMD_ZERO
  Panel.begin(SerialUSB);
#else
  Panel.begin();
#endif


  randomSeed(analogRead(0));
}

void loop()
{
  Panel.receive(); // handle panel data coming in
  delay(50);
}

// Clock (using PanelOne) 

#include "PanelOne.h"
#include <TimeLib.h>  

boolean Graphmode = false;
boolean Monmode = false;

byte GraphValue=0;

void setup()
{
	Panel.Init(); // init port and protocol
  randomSeed(analogRead(0));
}

void loop()
{
  Panel.Receive(); // handle panel data coming in
  delay(50);
}




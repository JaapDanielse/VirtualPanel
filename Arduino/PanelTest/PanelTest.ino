// Clock (using PanelOne) 

#include "PanelOne.h"
#include <TimeLib.h>  

byte GraphValue=0;
boolean yellow = true;
boolean orange = true;
boolean red = true;
boolean blue = true;

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




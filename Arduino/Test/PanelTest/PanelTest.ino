// Clock (using PanelOne) 

#include "VirtualPanel.h"
#include <TimeLib.h>  

boolean Graphmode = false;
boolean Monmode = false;
boolean Infomode = false;

#define MaxColNum 8 //

char * Color[] = {"$WHITE","$YELLOW","$ORANGE","$RED","$GREEN","$BLUE","$PURPLE","$BROWN","$GRAY"};
int ColNum = 0;

byte GraphValue=0;

void setup()
{
	Panel.begin(); // init port and protocol
  randomSeed(analogRead(0));
}

void loop()
{
  Panel.receive(); // handle panel data coming in
  delay(50);
}

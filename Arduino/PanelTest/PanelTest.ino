// Clock (using PanelOne) 

#include "PanelOne.h"
#include <TimeLib.h>  

void setup()
{
	Panel.Init(); // init port and protocol
}

void loop()
{
	Panel.Receive(); // handle panel data coming in
}




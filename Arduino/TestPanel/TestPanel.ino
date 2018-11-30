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

void PanelCallback(int channel, int type) 
{ 
  // PanelCallback is called when a message is received from the panel 
  // only channel and type are passed as parameters. Panel data available as public library vars
  
  switch (channel) 
  {
    case PanelConnected: // receive panel connected message
    { 
      // initialize panel layout
      Panel.Send(ApplicationName,"Clock"); // set the application name
      Panel.Send(Display_1, "$BIG");       // set display 1 (time) to big font
      Panel.Send(Display_1, "$BOLD");      // set display 1 (time) to bold 
      Panel.Send(Display_2, "$BLACK");     // set display 2 (date) to black
      Panel.Send(DynamicDisplay,true);     // enable dynamic display request
      Panel.Send(UnixTime, true);          // request time
      break; 
    }

    case UnixTime: // receive (local) time in unix timestamp 
    {
      setTime(Panel.vpr_ulong); // set time using received unsigend long from panel
    }

    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      Panel.Sendf(Display_1,"%02d:%02d:%02d",hour(), minute(), second()); // Output time to display 1
      Panel.Sendf(Display_2,"%02d-%02d-%04d",day(), month(), year()); // Output date to display 2
      break;
    }
  }
}



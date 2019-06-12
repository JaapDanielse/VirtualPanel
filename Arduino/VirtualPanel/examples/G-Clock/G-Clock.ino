// VirtualPanel G-Clock example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include <VirtualPanel.h>
#include <TimeLib.h>

void setup()
{
	Panel.begin(); // init port and protocol
}

void loop()
{
	Panel.receive(); // handle panel data coming in
}

void PanelCallback(vp_channel channel) 
{ 
  // PanelCallback is called when a message is received from the panel 
  // only channel and type are passed as parameters. Panel data available as public library vars
  
  switch (channel) 
  {
    case PanelConnected: // receive panel connected message
    { 
      // initialize panel layout
      Panel.send(ApplicationName,"Clock"); // set the application name
      Panel.send(Display_1, "$BIG");       // set display 1 (time) to big font
      Panel.send(Display_1, "$BOLD");      // set display 1 (time) to bold 
      Panel.send(Display_2, "$BLACK");     // set display 2 (date) to black
      Panel.send(DynamicDisplay,(int16_t)1000);     // enable dynamic display request
      Panel.send(UnixTime, (bool)true);          // request time
      break; 
    }

    case UnixTime: // receive (local) time in unix timestamp 
    {
      setTime(Panel.vpr_ulong); // set time using received unsigend long from panel
    }

    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      Panel.sendf(Display_1,"%02d:%02d:%02d", hour(), minute(), second()); // Output time to display 1
      Panel.sendf(Display_2,"%02d-%02d-%04d", day(), month(), year()); // Output date to display 2
      break;
    }
  }
}


// VirtualPanel A-Button example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool    Power = false; // Power status
int16_t Value = 0;  // Integer variabel

void setup() 
{
  Panel.begin(); // init port and protocol
}

void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
  if (Power) Value = random(1,100); else Value = 0; // my own proces
  Panel.send(Display_1,Value); // Show Value on display_1
  delay(250); // delay 
}

void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.send(ApplicationName,"Minimal"); // set the application name
      Panel.send(Led_1,"$OFF"); // Turn Led_1 off (black)
      Panel.send(Button_3,"on/off"); // Button_3 visible and set text "on/off"
    break;

    case Button_3: // Catch button pressed
      if (Panel.vpr_type == vp_type::vp_void) Power = !Power;

      if (Power)
        Panel.send(Led_1,"$RED"); // Turn Led_1 on (red)
      else
        Panel.send(Led_1,"$OFF"); // Turn Led_1 off (black)
    break;

  }
}

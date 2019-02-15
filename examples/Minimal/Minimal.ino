// VirtualPanel Minimal example 

#include "VirtualPanel.h"

bool    Power = false; // Power status
int16_t Value = 0;  // Integer variabel

void setup() 
{
  Panel.Init(); // init port and protocol
}

void loop() 
{
  Panel.Receive(); // handle panel events form the panel (must be in the loop)
  if (Power) Value = random(1,100); else Value = 0; // my own proces
  Panel.Send(Display_1,Value); // Show Value on display_1
  delay(250); // delay 
}

void PanelCallback(int event, int type) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.Send(ApplicationName,"Minimal"); // set the application name
      Panel.Send(Led_1,"$OFF"); // Turn Led_1 off (black)
      Panel.Send(Button_3,"on/off"); // Button_3 visible and set text "on/off"
    break;




    case Button_3: // Catch button pressed
      Power = !Power;
      if (Power)
        Panel.Send(Led_1,"$RED"); // Turn Led_1 on (red)
      else
        Panel.Send(Led_1,"$OFF"); // Turn Led_1 off (black)
    break;

  }
}


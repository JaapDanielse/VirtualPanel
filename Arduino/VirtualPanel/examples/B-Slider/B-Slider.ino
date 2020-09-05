// VirtualPanel B-Slider example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool    Power = false; // Power status
int16_t Value = 0;  // Integer variabel
int16_t Factor = 50; //

void setup() 
{
  Panel.begin(); // init port and protocol
}

void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
  if (Power) Value = random(1,100); else Value = 0; // my own proces
  Panel.sendf(Display_1, "Value %d",  Value); // Show Value on display_1
  Panel.sendf(Display_3, "Factor %d", Factor); // Show Factor on display_3
  Panel.sendf(Display_2, "Result %d", Value*Factor); // Multiplication of Value and Factor on display 2
  delay(250); // delay 
}

void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.send(ApplicationName,"ScrollBar"); // set the application name
      Panel.send(Led_1,"$OFF"); // Turn Led_1 off (black)
      Panel.send(Button_3,"on/off"); // Button_3 visible and set text "on/off"
      Panel.send(Slider_2, "factor"); // Set Slider label
      Panel.send(MaxSlider_2, (int16_t)100); // Set Slider maximum value
      Panel.send(Slider_2, Factor); // Set Slider initial Value
      break;

    case Button_3: // Catch button pressed
      Power = !Power;
      if (Power)
        Panel.send(Led_1,"$RED"); // Turn Led_1 on (red)
      else
        Panel.send(Led_1,"$OFF"); // Turn Led_1 off (black)
      break;

    case Slider_2: // Catch Slider change
      Factor = Panel.vpr_int;
      Panel.sendf(Display_3, "Factor %d", Factor); // Show Factor on display_3
      break;
      
      default: break;
  }
}

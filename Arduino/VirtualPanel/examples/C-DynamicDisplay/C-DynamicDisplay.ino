// VirtualPanel DynamicDisplay example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool    Power = false; // Power status
int16_t Value = 0;  // Integer variabel
int16_t Factor = 50; //

void setup() 
{
  Panel.Init(); // init port and protocol
}

void loop() 
{
  Panel.Receive(); // handle panel events form the panel (must be in the loop)
  if (Power) Value = random(1,100); else Value = 0; // my own proces
  // there is no delay here!
}

void PanelCallback(int event, int type) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.Send(ApplicationName,"DynamicDisplay"); // set the application name
      Panel.Send(Led_1,"$OFF"); // Turn Led_1 off (black)
      Panel.Send(Button_3,"on/off"); // Button_3 visible and set text "on/off"
      Panel.Send(Slider_2, "factor"); // Set Slider label
      Panel.Send(MaxSlider_2, 100); // Set Slider maximum value
      Panel.Send(Slider_2, Factor); // Set Slider initial Value

      Panel.Send(DynamicDisplay, 500); // Switch on DynamicDisplay at 250 mS interval
    break;

    case Button_3: // Catch button pressed
      Power = !Power;
    break;

    case Slider_2: // Catch Slider change
      Factor = Panel.vpr_int; 
    break;

    case DynamicDisplay: // Catch Dynamic display event
      // although numbers are generated fast display is at a resonable pace controlled by the panel
      Panel.Sendf(Display_1, "Value %d",  Value); // Show Value on display_1
      Panel.Sendf(Display_3, "Factor %d", Factor); // Show Factor on display_3
      Panel.Sendf(Display_2, "Result %d", Value*Factor); // Multiplication of Value and Factor on display 2
    break;
  }
  
  StaticChange(); // catch changes because of buttons or sliders
}


void StaticChange()
{
  if (Power)
    Panel.Send(Led_1,"$RED"); // Turn Led_1 on (red)
  else
    Panel.Send(Led_1,"$OFF"); // Turn Led_1 off (black)
}


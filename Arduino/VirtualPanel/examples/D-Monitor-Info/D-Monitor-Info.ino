// VirtualPanel D-Monitor-Info example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

// VirtualPanel has an extra panel called monitor providing extra 
// display space. It comes particularly handy when debugging.
// In the monitor panel is also a scrollbox for logging-like purposes.
// The contents of the scroll box can bes saved to file.
// The info panel is to provide info on the experiment
// (function, which pins are used for what etc.

#include "VirtualPanel.h"

bool    Power = false; // Power status
bool    MonitorVisible = false; // Power status
bool    InfoVisible = false; // Power status
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
}

void PanelCallback(int event, int type) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.Send(ApplicationName,"Monitor-Info"); // set the application name
      Panel.Send(Led_1,"$OFF"); // Turn Led_1 off (black)
      Panel.Send(Button_3,"on/off"); // Button_3 visible and set text "on/off"
      Panel.Send(Button_7,"moni\ntor"); // Button_3 visible and set text "on/off"
      Panel.Send(Button_8,"info"); // Button_3 visible and set text "on/off"
      Panel.Send(Slider_2, "factor"); // Set Slider label
      Panel.Send(MaxSlider_2, 100); // Set Slider maximum value
      Panel.Send(Slider_2, Factor); // Set Slider initial Value

      Panel.Send(InfoTitle,F("Monitor and Info")); // Info Title the F() macro can be used to force strings in program memory
      Panel.Send(InfoText, F("The Monitor can be used for extra displays"));
      Panel.Send(InfoText, F("particularly handy for debugging."));
      Panel.Send(InfoText, F("The monitor scrollbox can be used for logging-like purposes"));
      Panel.Send(InfoText, F("Info is for informational texts like this."));
      Panel.Send(InfoText, F("Both can also be activated from the menu (▼)"));
      
      Panel.Send(DynamicDisplay, 500); // Switch on DynamicDisplay at 250 mS interval
    break;

    case Button_3: // Catch button pressed
      Power = !Power;
      if (Power) 
        Panel.Send(MonitorLogPanel, "Power On"); // log action
      else
        Panel.Send(MonitorLogPanel, "Power Off"); // log action
     
    break;

    case Button_7: // Catch button pressed
      MonitorVisible = !MonitorVisible;
    break;

    case Button_8: // Catch button pressed
      InfoVisible = !InfoVisible;
    break;

    case Slider_2: // catch slider change
      Factor = Panel.vpr_int; 
      Panel.Sendf(MonitorLogPanel, "Factor change (%d)", Factor); // log action
    break;

    case DynamicDisplay: // Catch Dynamic display event
      // although numbers are generated fast display is at a resonable pace controlled by the panel
      Panel.Sendf(Display_1, "Value %d",  Value); // Show Value on display_1
      Panel.Sendf(Display_3, "Factor %d", Factor); // Show Factor on display_3
      Panel.Sendf(Display_2, "Result %d", Value*Factor); // Multiplication of Value and Factor on display 2
      
      Panel.Sendf(MonitorField_1, "Factor %d", Factor); // Show Value on display_1
      Panel.Sendf(MonitorField_2, "Value %d", Value); // Show Value on display_1
      Panel.Sendf(MonitorField_3, "Calculated: %d", Value * Factor ); // Show Value on display_1
    break;
  }
  
  if ( event != DynamicDisplay) StaticChange(); // handle changes because of button click
}

void StaticChange()
{
  if (Power)
    Panel.Send(Led_1,"$RED"); // Turn Led_1 on (red)
  else
    Panel.Send(Led_1,"$OFF"); // Turn Led_1 off (black)
    
  if (MonitorVisible)
    Panel.Send(Monitor,true); // set monitor panel visible
  else
    Panel.Send(Monitor,false); // set monitor panel invisible

  if (InfoVisible)
    Panel.Send(Info, true); // set info panel visible
  else
    Panel.Send(Info, false); // set info panel invisible
}


// VirtualPanel L-FMacro example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

// Duplicate of D-Monitor-Info but using the F() macro.
// This example will not work on Arduino Due.
// If you compare the Global variable bytes 
// this sketch will use approximately 18% dynamic memory where D-Monitor-Info will use 34%


#include "VirtualPanel.h"

bool    Power = false; // Power status
bool    MonitorVisible = false; // Power status
bool    InfoVisible = false; // Power status
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
}

void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.send(ApplicationName,"F-Macro"); // set the application name
      Panel.send(Led_1,F("$OFF")); // Turn Led_1 off (black)
      Panel.send(Button_3,F("on/off")); // Button_3 visible and set text "on/off"
      Panel.send(Button_7,F("moni\ntor")); // Button_3 visible and set text "on/off"
      Panel.send(Button_8,F("info")); // Button_3 visible and set text "on/off"
      Panel.send(Slider_2, F("factor")); // Set Slider label
      Panel.send(MaxSlider_2, (int16_t)100); // Set Slider maximum value
      Panel.send(Slider_2, Factor); // Set Slider initial Value

      Panel.send(InfoTitle,F("Monitor and Info")); // Info Title 
      Panel.send(InfoText, F("The Monitor can be used for extra displays"));
      Panel.send(InfoText, F("particularly handy for debugging."));
      Panel.send(InfoText, F("The monitor scrollbox can be used for logging-like purposes"));
      Panel.send(InfoText, F("Info is for informational texts like this."));
      Panel.send(InfoText, F("Both can also be activated from the menu (▼)"));
      
      Panel.send(DynamicDisplay, (int16_t)500); // Switch on DynamicDisplay at 250 mS interval
      break;

    case Button_3: // Catch button pressed
      Power = !Power;
      if (Power) 
        Panel.send(MonitorLog, F("Power On")); // log action
      else
        Panel.send(MonitorLog, F("Power Off")); // log action
      break;

    case Button_7: // Catch button pressed
      MonitorVisible = !MonitorVisible;
      break;

    case Button_8: // Catch button pressed
      InfoVisible = !InfoVisible;
      break;

    case Slider_2: // catch slider change
      Factor = Panel.vpr_int; 
      Panel.sendf(MonitorLog, F("Factor change (%d)"), Factor); // log action
      break;

    case DynamicDisplay: // Catch Dynamic display event
      // although numbers are generated fast display is at a resonable pace controlled by the panel
      Panel.sendf(Display_1, "Value %d",  Value); // Show Value on display_1
      Panel.sendf(Display_3, "Factor %d", Factor); // Show Factor on display_3
      Panel.sendf(Display_2, "Result %d", Value*Factor); // Multiplication of Value and Factor on display 2
      
      Panel.sendf(MonitorField_1, "Factor %d", Factor); // Show Value on display_1
      Panel.sendf(MonitorField_2, "Value %d", Value); // Show Value on display_1
      Panel.sendf(MonitorField_3, "Calculated: %d", Value * Factor ); // Show Value on display_1
      break;
  }
  
  if ( event != DynamicDisplay) StaticChange(); // handle changes because of button click
}

void StaticChange()
{
  if (Power)
    Panel.send(Led_1,F("$RED")); // Turn Led_1 on (red)
  else
    Panel.send(Led_1,F("$OFF")); // Turn Led_1 off (black)
    
    Panel.send(Monitor, MonitorVisible); // set monitor panel visible
    Panel.send(Info, InfoVisible); // set info panel visible
}

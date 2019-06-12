// VirtualPanel F-Input example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool    Power = false; // Power status
bool    MonitorVisible = false; // Power status
bool    InfoVisible = false; // Power status
float   Frequency = 500.023;  // Integer variabel
int16_t Duration  = 400;  // Integer variabel

void setup() 
{
  Panel.begin(); // init port and protocol
}

void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
  delay(250); // delay 
}

void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.send(ApplicationName,"Beep"); // set the application name
      
      Panel.send(Button_8,"info"); // Button_3 visible and set text "on/off"
      Panel.send(Button_15,"beep\ndefault"); // Button_3 visible and set text "on/off"
      Panel.send(Button_16,"beep\nfreq"); // Button_3 visible and set text "on/off"
      Panel.send(Button_17,"beep\nfrq+dur"); // Button_3 visible and set text "on/off"
      
      Panel.send(InfoTitle, "Input"); // Info Title the F() macro can be used to force strings in program memory
      Panel.send(InfoText, "Same example as Beep");
      Panel.send(InfoText, "But now the scrollbars have been changed to input");
      Panel.send(InfoText, "You can access them by double clicking the display");
      Panel.send(InfoText, "Frequency is limited between 37 and 1000Hz");
      Panel.send(InfoText, "Duration can be set between 10 and 1000mS");
    break;

    case Button_8: // Catch button pressed
      InfoVisible = !InfoVisible;
    break;

    case Button_15: // Catch button pressed
     Panel.send(Beep); // Beep default 300 Hz, 
    break;

    case Button_16: // Catch button pressed
      Panel.send(Beep, (int16_t)Frequency); //
    break;

    case Button_17: // Catch button pressed
      Panel.send(Beep,_Sound((int)Frequency, Duration));
    break;

    case Display_1: // display has been double clicked 
      Panel.send(MinPanelInput_1, (float)37.5); // 
      Panel.send(MaxPanelInput_1, (float)10000.0); // 
      Panel.send(PanelInputLabel_1, "Frequency:"); // 
      Panel.send(PanelInput_1, Frequency); // 
    break;

    case Display_2: // display has been double clicked 
      Panel.send(MinPanelInput_2, (int16_t)10); // 
      Panel.send(MaxPanelInput_2, (int16_t)1000); // 
      Panel.send(PanelInputLabel_2, "Duration:"); // 
      Panel.send(PanelInput_2, Duration); // 
    break;

    case MonitorField_1: // display has been double clicked 
      Panel.send(MinMonitorInput_1, (float)37.5); // 
      Panel.send(MaxMonitorInput_1, (float)10000.0); // 
      Panel.send(MonitorInputLabel_1, "Frequency:"); // 
      Panel.send(MonitorInput_1, Frequency); // 
    break;

    case PanelInput_1:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        Frequency = Panel.vpr_float; // ok, store
    break;

    case PanelInput_2:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        Duration = Panel.vpr_int;
    break;

    case MonitorInput_1:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        Frequency = Panel.vpr_float;
    break;
  }

  StaticChange();
}


void StaticChange()
{
  Panel.send(Display_1, Frequency); // write display_1
  Panel.send(Display_3, "Frequency"); // write display_1
  Panel.sendf(Display_2, "Duration. %d mS", Duration); // write display_2
  Panel.send(MonitorField_1, Frequency); // write display_1

  Panel.send(Info, InfoVisible); // set info panel visible
}

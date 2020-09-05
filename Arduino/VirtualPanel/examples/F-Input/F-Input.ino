// VirtualPanel F-Input example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool    Power = false; // Power status
bool    MonitorVisible = false; // Power status
bool    InfoVisible = false; // Power status
int16_t Frequency = 500;  // Integer variabel
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
      Panel.send(ApplicationName,"Beep-Inputs"); // set the application name
      
      Panel.send(Button_5,"beep\ndefault");
      Panel.send(Button_6,"beep\nfreq");
      Panel.send(Button_7,"beep\nfrq+dur");
      Panel.send(Button_14,"moni-\ntor");
      Panel.send(Button_17,"info");

      // Panel input 1
      Panel.send(MinPanelInput_1, (int16_t)38); // set input minimum
      Panel.send(MaxPanelInput_1, (int16_t)10000.0); // set input maximum
      Panel.send(PanelInputLabel_1, "Frequency:"); // set input label

      // Panel input 2
      Panel.send(MinPanelInput_2, (int16_t)10); // set input minimum
      Panel.send(MaxPanelInput_2, (int16_t)1000); // set input maximum
      Panel.send(PanelInputLabel_2, "Duration:"); // set input label

      // Monitor input 1
      Panel.send(MinMonitorInput_1, (int16_t)38); // minimum value
      Panel.send(MaxMonitorInput_1, (int16_t)10000); // maximum value
      Panel.send(MonitorInputLabel_1, "Frequency:"); // label
      Panel.send(MonitorInput_1, Frequency); // value
      Panel.send(MonitorInput_1, (bool)true); // set permanent

      // Monitor input 2
      Panel.send(MinMonitorInput_2, (int16_t)10); // minimum value
      Panel.send(MaxMonitorInput_2, (int16_t)1000); // maximum value
      Panel.send(MonitorInputLabel_2, "Duration:"); // label
      Panel.send(MonitorInput_2, Duration); // value
      Panel.send(MonitorInput_2, (bool)true); // set permanent

      // Info screen 
      Panel.send(InfoTitle, "Input"); // Info Title the F() macro can be used to force strings in program memory
      Panel.send(InfoText, "Same example as Beep");
      Panel.send(InfoText, "But now the scrollbars have been changed to input");
      Panel.send(InfoText, "You can access them by double clicking the display");
      Panel.send(InfoText, "Frequency is limited between 38 and 10.000 Hz");
      Panel.send(InfoText, "Duration can be set between 10 and 1000 mS");
      break;

    case Button_5: // Catch button pressed
      Panel.send(Beep); // Beep default 500Hz 400ms
      break;

    case Button_6: // Catch button pressed
      Panel.send(Beep, (int16_t)Frequency); // Beep set frequency 400ms
      break;

    case Button_7: // Catch button pressed
      Panel.send(Beep,_Sound((int)Frequency, Duration)); // Beep set frequency and duration
      break;

    case Button_14: // Catch button pressed
      MonitorVisible = !MonitorVisible; // togle inof pannel
      Panel.send(Monitor, MonitorVisible); // send to panel
      break;

    case Button_17: // Catch button pressed
      InfoVisible = !InfoVisible; // togle inof pannel
      Panel.send(Info, InfoVisible); // send to panel
      break;

    case Display_1: // display 1 has been double clicked 
      Panel.send(PanelInput_1, Frequency); // set current frequency value
      break;

    case Display_2: // display 2 has been double clicked 
      Panel.send(PanelInput_2, Duration); // set current duration value
      break;

    case PanelInput_1:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        Frequency = Panel.vpr_int; // ok, store
    break;

    case PanelInput_2:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        Duration = Panel.vpr_int;
    break;

    case MonitorInput_1:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        Frequency = Panel.vpr_int;
    break;

    case MonitorInput_2:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        Duration = Panel.vpr_int;
    break;
    
    default: break;
  }
  
  // code for all panel evnents
  Panel.sendf(Display_1, "Frequency: %d Hz", Frequency); // write display_1
  Panel.sendf(Display_2, "Duration: %d mS", Duration); // write display_2
  Panel.send(MonitorField_1, Frequency); // write display_1
}

// VirtualPanel Beep example 

#include "VirtualPanel.h"

bool    Power = false; // Power status
bool    MonitorVisible = false; // Power status
bool    InfoVisible = false; // Power status
float   Frequency = 500.023;  // Integer variabel
int16_t Duration  = 400;  // Integer variabel

void setup() 
{
  Panel.Init(); // init port and protocol
}

void loop() 
{
  Panel.Receive(); // handle panel events form the panel (must be in the loop)
  delay(250); // delay 
}

void PanelCallback(int event, int type) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.Send(ApplicationName,"Beep"); // set the application name
      
      Panel.Send(Button_8,"info"); // Button_3 visible and set text "on/off"
      Panel.Send(Button_15,"beep\ndefault"); // Button_3 visible and set text "on/off"
      Panel.Send(Button_16,"beep\nfreq"); // Button_3 visible and set text "on/off"
      Panel.Send(Button_17,"beep\nfrq+dur"); // Button_3 visible and set text "on/off"
      
      Panel.Send(InfoTitle,F("Input")); // Info Title the F() macro can be used to force strings in program memory
      Panel.Send(InfoText, F("Same example as Beep"));
      Panel.Send(InfoText, F("But now the scrollbars have been changed to input"));
      Panel.Send(InfoText, F("You can access them by double clicking the display"));
      Panel.Send(InfoText, F("Frequency is limited between 37 and 1000Hz"));
      Panel.Send(InfoText, F("Duration can be set between 10 and 1000mS"));
    break;

    case Button_8: // Catch button pressed
      InfoVisible = !InfoVisible;
    break;

    case Button_15: // Catch button pressed
     Panel.Send(Beep); // Beep default 300 Hz, 
    break;

    case Button_16: // Catch button pressed
      Panel.Send(Beep, (int)Frequency); //
    break;

    case Button_17: // Catch button pressed
      Panel.Send(Beep,_Sound((int)Frequency, Duration));
    break;

    case Display_1: // display has been double clicked 
      Panel.Send(MinPanelInput_1, (float)37.5); // 
      Panel.Send(MaxPanelInput_1, (float)10000.0); // 
      Panel.Send(PanelInputLabel_1, "Frequency:"); // 
      Panel.Send(PanelInput_1, Frequency); // 
    break;

    case Display_2: // display has been double clicked 
      Panel.Send(MinPanelInput_2, 10); // 
      Panel.Send(MaxPanelInput_2, 1000); // 
      Panel.Send(PanelInputLabel_2, "Duration:"); // 
      Panel.Send(PanelInput_2, Duration); // 
    break;

    case MonitorField_1: // display has been double clicked 
      Panel.Send(MinMonitorInput_1, (float)37.5); // 
      Panel.Send(MaxMonitorInput_1, (float)10000.0); // 
      Panel.Send(MonitorInputLabel_1, "Frequency:"); // 
      Panel.Send(MonitorInput_1, Frequency); // 
    break;

    case PanelInput_1:
      Frequency = Panel.vpr_float;
    break;

    case PanelInput_2:
      Duration = Panel.vpr_int;
    break;

    case MonitorInput_1:
      Frequency = Panel.vpr_float;
    break;
  }

  StaticChange();
}


void StaticChange()
{
  Panel.Send(Display_1, Frequency); // write display_1
  Panel.Send(Display_3, "Frequency"); // write display_1
  Panel.Sendf(Display_2, "Duration. %d mS", Duration); // write display_2
  Panel.Send(MonitorField_1, Frequency); // write display_1

  if (InfoVisible)
    Panel.Send(Info, true); // set info panel visible
  else
    Panel.Send(Info, false); // set info panel invisible
}


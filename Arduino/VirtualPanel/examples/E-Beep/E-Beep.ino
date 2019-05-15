// VirtualPanel Beep example 

#include "VirtualPanel.h"

bool    Power = false; // Power status
bool    MonitorVisible = false; // Power status
bool    InfoVisible = false; // Power status
int16_t Frequency = 500;  // Integer variabel
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
      
      Panel.Send(Slider_2,"Freq."); // Set Slider label
      Panel.Send(MaxSlider_2, 10000-37); // Set maximum value (10000 Hz - minimum freq.
      Panel.Send(Slider_2, Frequency); // Set initial value
      
      Panel.Send(Slider_3,"Dur."); // Set Slider label
      Panel.Send(MaxSlider_3,1000-1); // Set maximum value (1000 mS - minimum (1 mS)
      Panel.Send(Slider_3, Duration); // Set initial value

      Panel.Send(InfoTitle, F("Beep")); // Info Title the F() macro can be used to force strings in program memory
      Panel.Send(InfoText, F("Beep requests a standard console beep function on the pc"));
      Panel.Send(InfoText, F("Sent void it will beep 400Hz for 500mS"));
      Panel.Send(InfoText, F("With just one parameter (int16_t) you set the frequency"));
      Panel.Send(InfoText, F("Using the _Sound helper function"));
      Panel.Send(InfoText, F("you can set both frequency and duration"));
    break;

    case Button_8: // Catch button pressed
      InfoVisible = !InfoVisible;
    break;

    case Button_15: // Catch button pressed
     Panel.Send(Beep); // Beep default 300 Hz, 
    break;

    case Button_16: // Catch button pressed
      Panel.Send(Beep, Frequency); //
    break;

    case Button_17: // Catch button pressed
      Panel.Send(Beep,_Sound(Frequency, Duration));
    break;

    case Slider_2: // Catch Slider change
      Frequency = Panel.vpr_int+37; // get Slider value and add minimum
    break;

    case Slider_3: // Catch Slider change
      Duration = Panel.vpr_int+1; // get Slider value and add minimum
     break;
   }

   StaticChange();
}


void StaticChange()
{
  Panel.Sendf(Display_1, "Freq. %d Hz", Frequency); // write display_1
  Panel.Sendf(Display_2, "Duration. %d mS", Duration); // write display_2

  if (InfoVisible)
    Panel.Send(Info, true); // set info panel visible
  else
    Panel.Send(Info, false); // set info panel invisible
}


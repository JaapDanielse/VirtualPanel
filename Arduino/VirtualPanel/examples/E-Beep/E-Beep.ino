// VirtualPanel E-Beep example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2020 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool    Power = false; // Power status
bool    MonitorVisible = false; // Power status
bool    InfoVisible = false; // Power status

int16_t Frequency = 500;  // Integer variabel
int16_t Herz = (Frequency % 1000);
int16_t KiloHerz = (Frequency / 1000);
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
      
      Panel.send(Button_17,"info"); // Button_3 visible and set text "on/off"
      Panel.send(Button_5,"beep\ndefault"); // Button_3 visible and set text "on/off"
      Panel.send(Button_6,"beep\nfreq"); // Button_3 visible and set text "on/off"
      Panel.send(Button_7,"beep\nfrq+dur"); // Button_3 visible and set text "on/off"
      
      Panel.send(Slider_1,"Dur."); // Set Slider label
      Panel.send(MaxSlider_1,(int16_t)(1000-1)); // Set maximum value (1000 mS - minimum (1 mS)
      Panel.send(Slider_2, Duration); // Set initial value

      Panel.send(Slider_2,"KHz"); // Set Slider label
      Panel.send(MaxSlider_2, (int16_t)9); // Set maximum value (9 KHz) 
      Panel.send(Slider_2, KiloHerz); // Set initial value - minimum 

      Panel.send(Slider_3,"Hz"); // Set Slider label
      Panel.send(MaxSlider_3, (int16_t)(1000)); // Set maximum value 1000 Hz).
      Panel.send(Slider_3, (Herz)); // Set initial value - minimum 

      Panel.send(InfoTitle, "Beep"); // Info Title the F() macro can be used to force strings in program memory
      Panel.send(InfoText, "Beep requests a standard console beep function on the pc");
      Panel.send(InfoText, "Sent void it will beep 500Hz for 400mS");
      Panel.send(InfoText, "With just one parameter (int16_t) you set the frequency");
      Panel.send(InfoText, "Using the _Sound helper function");
      Panel.send(InfoText, "you can set both frequency and duration");
    break;

    case Button_5: // Catch button pressed
      Panel.send(Beep); // Beep default 500 Hz, 
      break;

    case Button_6: // Catch button pressed
      Panel.send(Beep, Frequency); // beep set frequency for 400 ms
      break;

    case Button_7: // Catch button pressed
      Panel.send(Beep,_Sound(Frequency, Duration)); // beep set frequency and duration
      break;

    case Button_17: // Catch button pressed
      InfoVisible = !InfoVisible; // toggle infoscreen
      Panel.send(Info,InfoVisible); // set info panel visible   StaticChange();
      break;

    case Slider_1: // Catch Slider change
        Duration = Panel.vpr_int+1; // get Slider value and add minimum
      break;

    case Slider_2: // Catch Slider change
      KiloHerz = (Panel.vpr_int); // get KHz Slider value
      Herz = 0; // on KHz step reset Hz to 0 
      Panel.send(Slider_3, (Herz)); // Send (0)Hz to slider
      break;

    case Slider_3: // Catch Slider change
       Herz = (Panel.vpr_int); // get Slider value
      break;
   }

   // Next code for all panel events
   Frequency = (KiloHerz*1000) + Herz; // calculate frequecy

   // Minimum frequency 37 Hz
   if(Frequency < 38)
   { 
     Frequency = 38; // set minimum Freq
     Herz = 38; // set minimum Hz
     Panel.send(Slider_3, (Herz)); // move slider to minimum
   }

   Panel.sendf(Display_1, "Freq. %d Hz", Frequency); // write display_1
   Panel.sendf(Display_2, "Duration. %d mS", Duration); // write display_2
} 

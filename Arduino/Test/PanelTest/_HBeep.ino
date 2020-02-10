

int16_t Frequency = 500;  // Integer variabel
int16_t Duration  = 400;  // Integer variabel

void BeepCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.send(ApplicationName,F("PanelTest - Beep")); // set the application name
      Panel.send(Button_4,F("next\npanel"));
      Panel.send(Button_15,F("beep\ndefault")); // Button_3 visible and set text "on/off"
      Panel.send(Button_16,F("beep\nfreq")); // Button_3 visible and set text "on/off"
      Panel.send(Button_17,F("beep\nfrq+dur")); // Button_3 visible and set text "on/off"
      
      Panel.send(Slider_2,F("Freq.")); // Set Slider label
      Panel.send(MaxSlider_2, (int16_t)(10000-37)); // Set maximum value (10000 Hz - minimum freq.
      Panel.send(Slider_2, Frequency); // Set initial value
      
      Panel.send(Slider_3,F("Dur.")); // Set Slider label
      Panel.send(MaxSlider_3,(int16_t)(1000-1)); // Set maximum value (1000 mS - minimum (1 mS)
      Panel.send(Slider_3, Duration); // Set initial value
     
      WriteInfo();
      break;

    case Button_4:
      if( ++PanelMode == Endmode ) PanelMode = 0;
      Panel.send(Reset);
      break;
      
    case Button_15: // Catch button pressed
      Panel.send(Beep); // Beep default 300 Hz, 
      break;
  
    case Button_16: // Catch button pressed
      Panel.send(Beep, Frequency); //
      break;
  
    case Button_17: // Catch button pressed
      Panel.send(Beep,_Sound(Frequency, Duration));
      break;
  
    case Slider_2: // Catch Slider change
      Frequency = Panel.vpr_int+37; // get Slider value and add minimum
      Panel.sendf(Display_1, "Freq. %d Hz", Frequency); // write display_1
      break;
  
    case Slider_3: // Catch Slider change
      Duration = Panel.vpr_int+1; // get Slider value and add minimum
      Panel.sendf(Display_2, "Duration. %d mS", Duration); // write display_2
      break;
  }

}

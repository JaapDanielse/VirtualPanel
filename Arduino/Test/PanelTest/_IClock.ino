
 void ClockCallback(vp_channel event)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
     // initialize panel layout
      Panel.send(ApplicationName,F("PanelTest - Clock")); // set the application name
      Panel.send(Button_4,  F("next\npanel"));
      Panel.send(Display_1, F("$BIG"));       // set display 1 (time) to big font
      Panel.send(Display_1, F("$BOLD"));      // set display 1 (time) to bold 
      Panel.send(Display_2, F("$BLACK"));     // set display 2 (date) to black
      Panel.send(DynamicDisplay,(int16_t)500);     // enable dynamic display request
      Panel.send(UnixTime, (bool)true);          // request time

      WriteInfo();
      break; 

    case Button_4:
      if( ++PanelMode == Endmode ) PanelMode = 0;
      Panel.send(Reset);
      break;

    case DynamicDisplay: // dynamic display request (requested every 500ms)
      Panel.sendf(Display_1,F("%02d:%02d:%02d"),hour(), minute(), second()); // Output time to display 1
      Panel.sendf(Display_2,F("%02d-%02d-%04d"),day(), month(), year()); // Output date to display 2
      break;
    
    case UnixTime: // receive (local) time in unix timestamp 
      setTime(Panel.vpr_ulong); // set time using received unsigend long from panel
      break;
      
    default: break;
  }
}
 

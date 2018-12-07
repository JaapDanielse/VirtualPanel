
 void ClockCallback(int event, int type)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
     // initialize panel layout
      Panel.Send(ApplicationName,"PanelTest - Clock"); // set the application name
      Panel.Send(Display_1, "$BIG");       // set display 1 (time) to big font
      Panel.Send(Display_1, "$BOLD");      // set display 1 (time) to bold 
      Panel.Send(Display_2, "$BLACK");     // set display 2 (date) to black
      Panel.Send(DynamicDisplay,500);     // enable dynamic display request
      Panel.Send(Button_4,  "next");
      Panel.Send(UnixTime, true);          // request time
      break; 
    }

    case Button_4:
    {
      PanelMode = AllButton;
      Panel.Send(Reset);
      break;
    }


    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      Panel.Sendf(Display_1,"%02d:%02d:%02d",hour(), minute(), second()); // Output time to display 1
      Panel.Sendf(Display_2,"%02d-%02d-%04d",day(), month(), year()); // Output date to display 2
      break;
    }
    
    case UnixTime: // receive (local) time in unix timestamp 
    {
      setTime(Panel.vpr_ulong); // set time using received unsigend long from panel
      break;
    }

    default:
      break;
  }
}
 


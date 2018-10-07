//

#define NextButton Button_4 //


void PanelCallback(int channel, int type) 
{ 
  // PanelCallback is called when a message is received from the panel 
  // only channel and type are passed as parameters. Panel data available as public library vars
  
  switch (channel) 
  {
    case PanelConnected: // receive panel connected message
    { 
      // initialize panel layout
      Panel.Send(ApplicationName,"Panel Test"); // set the application name
      Panel.Send(Display_1, "$BIG");       // set display 1 (time) to big font
      Panel.Send(Display_1, "$BOLD");      // set display 1 (time) to bold 
      Panel.Send(Display_2, "$BLACK");     // set display 2 (date) to black
      Panel.Send(DynamicDisplay,true);     // enable dynamic display request
      Panel.Send(Button_4,  "next");
      Panel.Send(UnixTime, true);          // request time
      break; 
    }

    case UnixTime: // receive (local) time in unix timestamp 
    {
      setTime(Panel.vpr_ulong); // set time using received unsigend long from panel
      break;
    }

    case NextButton:
    {
      SwitchPanel();
      break;
    }

    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      Panel.Sendf(Display_1,"%02d:%02d:%02d",hour(), minute(), second()); // Output time to display 1
      Panel.Sendf(Display_2,"%02d-%02d-%04d",day(), month(), year()); // Output date to display 2
      break;
    }

    default:
    {
       if (channel > 4 && channel < 22) 
         Panel.Sendf(StatMonitor,"ChannelId %d Button_%d Pressed", channel, channel-4 );
       if (channel > 21 && channel < 27)
         Panel.Sendf(StatMonitor,"ChannelId %d ScrollBar_%d Value %d", channel, channel-21, Panel.vpr_int );
    }
  }
}


void SwitchPanel()
{
  static int panelnum = 0;
  const int  panelcount = 3;
    
  ClearPanel();

  switch ( panelnum )
  {
    case 0:
    {
      AllButtonPanel();
      break;
    }

    case 1:
    {
      ScrollbarPanel();
      break;
    }

    case 2:
    {
      ControlPanel();
      break;
    }
  
  }

  panelnum++;
  if (panelnum == panelcount) panelnum = 0;  
}


void AllButtonPanel()
{
  Panel.Send(StatMonitor, "AllButtonPanel");
  Panel.Send(StatField_1, false);
  Panel.Send(StatField_2, (byte)254 );
  Panel.Send(StatField_3, (int)-32768 );
  Panel.Send(StatField_4, (unsigned int)65535 );
  Panel.Send(StatField_5, (long)-2147483648 );
  Panel.Send(StatField_6, (unsigned long)4294967295 );
  
  Panel.Send(Display_1, "display 1");
  Panel.Send(Display_2, "display 2");
  Panel.Send(Display_3, "display 3");
  Panel.Send(Display_4, "display 4");




  
  Panel.Send(Button_1,  "button 1");
  Panel.Send(Button_2,  "button 2");
  Panel.Send(Button_3,  "button 3");
  Panel.Send(Button_4,  "button 4");
  Panel.Send(Button_5,  "button 5");
  Panel.Send(Button_6,  "button 6");
  Panel.Send(Button_7,  "button 7");
  Panel.Send(Button_8,  "button 8");
  Panel.Send(Button_9,  "button 9");
  Panel.Send(Button_10, "button 10");
  Panel.Send(Button_11, "button 11");
  Panel.Send(Button_12, "button 12");
  Panel.Send(Button_13, "button 13");
  Panel.Send(Button_14, "button 14");
  Panel.Send(Button_15, "button 15");
  Panel.Send(Button_16, "button 16");
  Panel.Send(Button_17, "button 17");


  Panel.Send(Led_1,  "$OFF");
  Panel.Send(Led_2,  "$OFF");
  Panel.Send(Led_3,  "$YELLOW");
  Panel.Send(Led_4,  "$YELLOW");
  Panel.Send(Led_5,  "$ORANGE");
  Panel.Send(Led_6,  "$ORANGE");
  Panel.Send(Led_7,  "$RED");
  Panel.Send(Led_8,  "$RED");
  Panel.Send(Led_9,  "$GREEN");
  Panel.Send(Led_10,  "$YELLOW");
  Panel.Send(Led_11,  "$YELLOW");
  Panel.Send(Led_12,  "$GREEN");
  Panel.Send(Led_13,  "$GREEN");

}


void ScrollbarPanel()
{
  Panel.Send(StatMonitor, "ScrollBarPanel");
  Panel.Send(StatField_1);
  Panel.Send(StatField_2, (byte)0 );
  Panel.Send(StatField_3, (int)32767 );
  Panel.Send(StatField_4, (unsigned int)65535 );
  Panel.Send(StatField_5, (long)2147483647 );
  Panel.Send(StatField_6, (unsigned long)4294967295 );

  Panel.Send(Display_1, "display 1");
  Panel.Send(Display_2, "display 2");
  Panel.Send(Display_3, "display 3");
  Panel.Send(Display_4, "display 4");

  Panel.Send(ScrollBar_1, true);
//  Panel.Send(MaxScrollBar_1, 50);
  Panel.Send(ScrollBar_2, true);
  Panel.Send(ScrollBar_3, true);
  Panel.Send(ScrollBar_4, true);

  Panel.Send(ScrollBar_1, "scrlab1");
  Panel.Send(ScrollBar_2, "scrlab2");
  Panel.Send(ScrollBar_3, "scrlab3");
  Panel.Send(ScrollBar_4, "scrlab4");

  Panel.Send(Button_4,  "button 4");
  Panel.Send(Button_5,  "button 5");
  Panel.Send(Button_6,  "button 6");
  Panel.Send(Button_7,  "button 7");
  Panel.Send(Button_8,  "button 8");

  Panel.Send(Led_2,  "$YELLOW");
  Panel.Send(Led_3,  "$YELLOW");
  Panel.Send(Led_4,  "$YELLOW");
  Panel.Send(Led_5,  "$ORANGE");
  Panel.Send(Led_6,  "$ORANGE");

  Panel.Send(Led_10,  "$YELLOW");
  Panel.Send(Led_11,  "$YELLOW");
  Panel.Send(Led_12,  "$GREEN");
  Panel.Send(Led_13,  "$GREEN");
}


void ControlPanel()
{
  Panel.Send(StatMonitor, "ControlPanel");
  Panel.Send(StatField_1, false);
  Panel.Send(StatField_2, (byte)254 );
  Panel.Send(StatField_3, (int)-32768 );
  Panel.Send(StatField_4, (unsigned int)65535 );
  Panel.Send(StatField_5, (long)-2147483648 );
  Panel.Send(StatField_6, (unsigned long)4294967295 );

  Panel.Send(Display_1, "display 1");
  Panel.Send(Display_2, "display 2");
  Panel.Send(Display_3, "display 3");
  Panel.Send(Display_4, "display 4");
  
  Panel.Send(Button_1,  "$YELLOW");
  Panel.Send(Button_1,  "$UP");
  Panel.Send(Button_2,  "$ORANGE");
  Panel.Send(Button_2,  "$DOWN");
  Panel.Send(Button_3,  "$ONOFF");

  Panel.Send(Button_4,  "next");
  
  Panel.Send(Button_5,  "$RUN");
  Panel.Send(Button_6,  "$PAUSE");
  Panel.Send(Button_7,  "$STOP");
  Panel.Send(Button_8,  "$SET");

  Panel.Send(Button_9,  "$LTURN");
  Panel.Send(Button_10, "$LEFT");

  Panel.Send(Button_11, "$GREEN");
  Panel.Send(Button_11, "$DOT" );

  Panel.Send(Button_12, "$UP" );
  Panel.Send(Button_13, "$DOT");
  Panel.Send(Button_14, "$DOWN");
  Panel.Send(Button_15, "$RTURN");
  Panel.Send(Button_16, "$RIGHT");
  
  Panel.Send(Button_17, "$RED");
  Panel.Send(Button_17, "$DOT");


}


void ClearPanel()
{
  //
  Panel.Send(Display_1, "$NORMAL");
  Panel.Send(Display_1, "$WHITE");
  Panel.Send(Display_1, "");
  Panel.Send(Display_1, false);
  //
  Panel.Send(Display_2, "$NORMAL");
  Panel.Send(Display_2, "$WHITE");
  Panel.Send(Display_2, "");
  Panel.Send(Display_2, false);
  //
  Panel.Send(Display_3, "$NORMAL");
  Panel.Send(Display_3, "$WHITE");
  Panel.Send(Display_3, "");
  Panel.Send(Display_3, false);
  //
  Panel.Send(Display_4, "$NORMAL");
  Panel.Send(Display_4, "$WHITE");
  Panel.Send(Display_4, "");
  Panel.Send(Display_4, false);
  //
  Panel.Send(Button_1, false);
  Panel.Send(Button_2, false);
  Panel.Send(Button_3, false);
  Panel.Send(Button_4, false);
  Panel.Send(Button_5, false);
  Panel.Send(Button_6, false);
  Panel.Send(Button_7, false);
  Panel.Send(Button_8, false);
  Panel.Send(Button_9, false);
  Panel.Send(Button_10, false);
  Panel.Send(Button_11, false);
  Panel.Send(Button_12, false);
  Panel.Send(Button_13, false);
  Panel.Send(Button_14, false);
  Panel.Send(Button_15, false);
  Panel.Send(Button_16, false);
  Panel.Send(Button_17, false);
  //
  Panel.Send(Button_1, "$BLACK");
  Panel.Send(Button_2, "$BLACK");
  Panel.Send(Button_3, "$BLACK");
  Panel.Send(Button_4, "$BLACK");
  Panel.Send(Button_5, "$BLACK");
  Panel.Send(Button_6, "$BLACK");
  Panel.Send(Button_7, "$BLACK");
  Panel.Send(Button_8, "$BLACK");
  Panel.Send(Button_9, "$BLACK");
  Panel.Send(Button_10, "$BLACK");
  Panel.Send(Button_11, "$BLACK");
  Panel.Send(Button_12, "$BLACK");
  Panel.Send(Button_13, "$BLACK");
  Panel.Send(Button_14, "$BLACK");
  Panel.Send(Button_15, "$BLACK");
  Panel.Send(Button_16, "$BLACK");
  Panel.Send(Button_17, "$BLACK");
  //
  Panel.Send(ScrollBar_1, false);
  Panel.Send(ScrollBar_2, false);
  Panel.Send(ScrollBar_3, false);
  Panel.Send(ScrollBar_4, false);
  //
  Panel.Send(Led_1, false);
  Panel.Send(Led_2, false);
  Panel.Send(Led_3, false);
  Panel.Send(Led_4, false);
  Panel.Send(Led_5, false);
  Panel.Send(Led_6, false);
  Panel.Send(Led_7, false);
  Panel.Send(Led_8, false);
  Panel.Send(Led_9, false);
  Panel.Send(Led_10, false);
  Panel.Send(Led_11, false);
  Panel.Send(Led_12, false);
  Panel.Send(Led_13, false);
 //
  Panel.Send(DynamicDisplay,false);  
}


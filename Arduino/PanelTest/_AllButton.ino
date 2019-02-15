
void AllButtonCallback(int event, int type)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      AllButtonInit();
      break; 

    case Button_4:
      PanelMode = ScrollBar;
      Panel.Send(Reset);
      break;

    case Button_5:
      Graphmode = !Graphmode;
      Panel.Send(Graph,Graphmode);
      break;

    case Button_6:
      Monmode = !Monmode;
      Panel.Send(Monitor,Monmode);
      break;

    default:
      if (event >= 7 && event <= 23) 
        Panel.Sendf(MonitorScrollBox,F("ChannelId %d Button_%d Pressed"), event, event-6 );
      if (event >= 24 && event <= 28)
        Panel.Sendf(MonitorScrollBox,F("ChannelId %d ScrollBar_%d Value %d"), event, event-23, Panel.vpr_int );
      break;
  }
}


void AllButtonInit()
{
  Panel.Send(ApplicationName,F("ApplicationName")); // set the application name

  Panel.Send(Display_1, F("Display_1"));
  Panel.Send(Display_2, F("Display_2"));
  Panel.Send(Display_3, F("Display_3"));
  Panel.Send(Display_4, F("Display_4"));
  
  Panel.Send(Button_1,  F("button 1"));
  Panel.Send(Button_2,  F("button 2"));
  Panel.Send(Button_3,  F("button 3"));
  Panel.Send(Button_4,  F("button 4"));
  Panel.Send(Button_5,  F("button 5"));
  Panel.Send(Button_6,  F("button 6"));
  Panel.Send(Button_7,  F("button 7"));
  Panel.Send(Button_8,  F("button 8"));
  Panel.Send(Button_9,  F("button 9"));
  Panel.Send(Button_10, F("button 10"));
  Panel.Send(Button_11, F("button 11"));
  Panel.Send(Button_12, F("button 12"));
  Panel.Send(Button_13, F("button 13"));
  Panel.Send(Button_14, F("button 14"));
  Panel.Send(Button_15, F("button 15"));
  Panel.Send(Button_16, F("button 16"));
  Panel.Send(Button_17, F("button 17"));

  Panel.Send(Led_1, F("$OFF"));
  Panel.Send(Led_2, F("$WHITE"));
  Panel.Send(Led_3, F("$YELLOW"));
  Panel.Send(Led_4, F("$ORANGE"));
  Panel.Send(Led_5, F("$RED"));
  Panel.Send(Led_6, F("$BLUE"));
  Panel.Send(Led_7, F("$GREEN"));
  Panel.Send(Led_8, F("$YELLOW"));
  Panel.Send(Led_9, F("$ORANGE"));
  Panel.Send(Led_10,F("$BLUE"));
  Panel.Send(Led_11,F("$GREEN"));
  Panel.Send(Led_12,F("$YELLOW"));
  Panel.Send(Led_13,F("$ORANGE"));

  Panel.Send(MonitorScrollBox, F("Buttons"));
  Panel.Send(MonitorField_1, false);
  Panel.Send(MonitorField_2, (byte)254 );
  Panel.Send(MonitorField_3, (int)-32768 );
  Panel.Send(MonitorField_4, (unsigned int)65535 );
  Panel.Send(MonitorField_5, (long)-2147483648 );
  Panel.Send(MonitorField_6, (unsigned long)4294967295 );
}





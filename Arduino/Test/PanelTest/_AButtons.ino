
void ButtonsCallback(vp_channel event)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      AllButtonInit();
      break; 

    case Button_4:
      
      if( ++PanelMode == Endmode ) PanelMode = 0;
      Panel.send(Reset);
      break;

    default:
      if (event >= Button_1 && event <= Button_17) 
        Panel.sendf(MonitorLog,F("ChannelId %d Button_%d Pressed"), event, (event - Button_1) + 1 );
      if (event >= Slider_1 && event <= Slider_5)
        Panel.sendf(MonitorLog,F("ChannelId %d Slider_%d Value %d"), event, (event - Slider_1) + 1, Panel.vpr_int );
      break;
  }
}


void AllButtonInit()
{
  Panel.send(ApplicationName,F("ApplicationName")); // set the application name

  Panel.send(Display_1, F("Display_1"));
  Panel.send(Display_2, F("Display_2"));
  Panel.send(Display_3, F("Display_3"));
  Panel.send(Display_4, F("Display_4"));
  
  Panel.send(Button_1,  F("button 1"));
  Panel.send(Button_2,  F("button 2"));
  Panel.send(Button_3,  F("button 3"));
  Panel.send(Button_4,  F("button 4"));
  Panel.send(Button_5,  F("button 5"));
  Panel.send(Button_6,  F("button 6"));
  Panel.send(Button_7,  F("button 7"));
  Panel.send(Button_8,  F("button 8"));
  Panel.send(Button_9,  F("button 9"));
  Panel.send(Button_10, F("button 10"));
  Panel.send(Button_11, F("button 11"));
  Panel.send(Button_12, F("button 12"));
  Panel.send(Button_13, F("button 13"));
  Panel.send(Button_14, F("button 14"));
  Panel.send(Button_15, F("button 15"));
  Panel.send(Button_16, F("button 16"));
  Panel.send(Button_17, F("button 17"));

  Panel.send(Led_1, F("$OFF"));
  Panel.send(Led_2, F("$WHITE"));
  Panel.send(Led_3, F("$YELLOW"));
  Panel.send(Led_4, F("$ORANGE"));
  Panel.send(Led_5, F("$RED"));
  Panel.send(Led_6, F("$BLUE"));
  Panel.send(Led_7, F("$GREEN"));
  Panel.send(Led_8, F("$YELLOW"));
  Panel.send(Led_9, F("$ORANGE"));
  Panel.send(Led_10,F("$BLUE"));
  Panel.send(Led_11,F("$GREEN"));
  Panel.send(Led_12,F("$YELLOW"));
  Panel.send(Led_13,F("$ORANGE"));

  Panel.send(MonitorLog, F("MonitorLog"));
  Panel.send(MonitorField_1, F("MonitorField_1"));
  Panel.send(MonitorField_2, F("MonitorField_2"));
  Panel.send(MonitorField_3, F("MonitorField_3"));
  Panel.send(MonitorField_4, F("MonitorField_4"));
  Panel.send(MonitorField_5, F("MonitorField_5"));
  Panel.send(MonitorField_6, F("MonitorField_6"));

  Panel.send(InfoTitle, "PannelTest");
  Panel.send(InfoText, "Application specific help text");
  Panel.send(InfoText, "Can be changed run-time");
  Panel.send(InfoText, "Hyperlink to documenation pages\n");
  Panel.send(InfoText, "https://github.com/JaapDanielse/VirtualPanel");
  Infomode = false;
  Monmode = false;
  Graphmode = false;


}

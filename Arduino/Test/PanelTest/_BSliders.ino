
void SlidersCallback(vp_channel event)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      SlidersInit();
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


void SlidersInit()
{
  Panel.send(ApplicationName,F("PanelTest - Sliders")); // set the application name

  Panel.send(Display_1, F("Display_1"));
  Panel.send(Display_2, F("Display_2"));
  Panel.send(Display_3, F("Display_3"));
  Panel.send(Display_4, F("Display_4"));

  Panel.send(Slider_1, true);
  Panel.send(Slider_2, true);
  Panel.send(Slider_3, true);
  Panel.send(Slider_4, true);
  Panel.send(Slider_5, true);

  Panel.send(Slider_1, F("slider1"));
  Panel.send(Slider_2, F("slider2"));
  Panel.send(Slider_3, F("slider3"));
  Panel.send(Slider_4, F("slider4"));
  Panel.send(Slider_5, F("slider5"));

  Panel.send(Slider_2, 0);

  Panel.send(Button_4,  F("button\n4"));
  Panel.send(Button_8,  F("button\n8"));
 
  Panel.send(Led_2,  F("$WHITE"));
  Panel.send(Led_6,  F("$BLUE"));

  Panel.send(Led_10,  F("$BLUE"));
  Panel.send(Led_11,  F("$GREEN"));
  Panel.send(Led_12,  F("$YELLOW"));
  Panel.send(Led_13,  F("$ORANGE"));

  Panel.send(MonitorField_1, F("MonitorField_1"));
  Panel.send(MonitorField_2, F("MonitorField_2"));
  Panel.send(MonitorField_3, F("MonitorField_3"));
  Panel.send(MonitorField_4, F("MonitorField_4"));
  Panel.send(MonitorField_5, F("MonitorField_5"));
  Panel.send(MonitorField_6, F("MonitorField_6"));
  
  WriteInfo();
}

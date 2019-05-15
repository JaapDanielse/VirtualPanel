
void SliderCallback(int event, int type)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      SliderInit();
      break; 

    case Button_4:
      PanelMode = Draw;
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
      if (event >= Button_1 && event <= Button_17) 
        Panel.Sendf(MonitorLogPanel,F("ChannelId %d Button_%d Pressed"), event, (event - Button_1) + 1 );
      if (event >= Slider_1 && event <= Slider_5)
        Panel.Sendf(MonitorLogPanel,F("ChannelId %d Slider_%d Value %d"), event, (event - Slider_1) + 1, Panel.vpr_int );
      break;
  }
}


void SliderInit()
{
  Panel.Send(ApplicationName,F("ApplicationName")); // set the application name

  Panel.Send(MonitorLogPanel, F("MonitorLogPanel"));
  Panel.Send(MonitorField_1, F("MonitorField_1"));
  Panel.Send(MonitorField_2, F("MonitorField_2"));
  Panel.Send(MonitorField_3, F("MonitorField_3"));
  Panel.Send(MonitorField_4, F("MonitorField_4"));
  Panel.Send(MonitorField_5, F("MonitorField_5"));
  Panel.Send(MonitorField_6, F("MonitorField_6"));

  Panel.Send(Display_1, F("Display_1"));
  Panel.Send(Display_2, F("Display_2"));
  Panel.Send(Display_3, F("Display_3"));
  Panel.Send(Display_4, F("Display_4"));

  Panel.Send(Slider_1, true);
  Panel.Send(Slider_2, true);
  Panel.Send(Slider_3, true);
  Panel.Send(Slider_4, true);
  Panel.Send(Slider_5, true);

  Panel.Send(Slider_1, F("slider1"));
  Panel.Send(Slider_2, F("slider2"));
  Panel.Send(Slider_3, F("slider3"));
  Panel.Send(Slider_4, F("slider4"));
  Panel.Send(Slider_5, F("slider5"));

  Panel.Send(Slider_2, 0);

  Panel.Send(Button_4,  F("button 4"));
  Panel.Send(Button_8,  F("button 8"));
 
  Panel.Send(Led_2,  F("$WHITE"));
  Panel.Send(Led_6,  F("$BLUE"));

  Panel.Send(Led_10,  F("$BLUE"));
  Panel.Send(Led_11,  F("$GREEN"));
  Panel.Send(Led_12,  F("$YELLOW"));
  Panel.Send(Led_13,  F("$ORANGE"));

}




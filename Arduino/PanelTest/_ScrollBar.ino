
void ScrollBarCallback(int event, int type)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      ScrollBarInit();
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
      if (event >= 7 && event <= 23) 
        Panel.Sendf(MonitorScrollBox,F("ChannelId %d Button_%d Pressed"), event, event-6 );
      if (event >= 24 && event <= 28)
        Panel.Sendf(MonitorScrollBox,F("ChannelId %d ScrollBar_%d Value %d"), event, event-23, Panel.vpr_int );
      break;
  }
}


void ScrollBarInit()
{
  Panel.Send(ApplicationName,F("ApplicationName")); // set the application name

  Panel.Send(MonitorScrollBox, F("MonitorScrollBox"));
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

  Panel.Send(ScrollBar_1, true);
  Panel.Send(ScrollBar_2, true);
  Panel.Send(ScrollBar_3, true);
  Panel.Send(ScrollBar_4, true);
  Panel.Send(ScrollBar_5, true);

  Panel.Send(ScrollBar_1, F("scrlbar1"));
  Panel.Send(ScrollBar_2, F("scrlbar2"));
  Panel.Send(ScrollBar_3, F("scrlbar3"));
  Panel.Send(ScrollBar_4, F("scrlbar4"));
  Panel.Send(ScrollBar_5, F("scrlbar5"));

  Panel.Send(ScrollBar_2, 0);

  Panel.Send(Button_4,  F("button 4"));
  Panel.Send(Button_8,  F("button 8"));
 
  Panel.Send(Led_2,  F("$WHITE"));
  Panel.Send(Led_6,  F("$BLUE"));

  Panel.Send(Led_10,  F("$BLUE"));
  Panel.Send(Led_11,  F("$GREEN"));
  Panel.Send(Led_12,  F("$YELLOW"));
  Panel.Send(Led_13,  F("$ORANGE"));

}




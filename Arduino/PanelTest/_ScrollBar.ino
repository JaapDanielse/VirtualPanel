
void ScrollBarCallback(int event, int type)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
      ScrollBarInit();
      break; 
    }

    case Button_4:
    {
      PanelMode = Draw;
      Panel.Send(Reset);
      break;
    }

    case Button_5:
    {
      Graphmode = !Graphmode;
      Panel.Send(Graph,Graphmode);
      break;
    }

    case Button_6:
    {
      Monmode = !Monmode;
      Panel.Send(Monitor,Monmode);
      break;
    }

    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      AllButtonDynamic();
      break;
    }

    default:
    {
      if (event >= 8 && event <= 24) 
        Panel.Sendf(MonitorScrollBox,"ChannelId %d Button_%d Pressed", event, event-7 );
      if (event >= 25 && event <= 28)
        Panel.Sendf(MonitorScrollBox,"ChannelId %d ScrollBar_%d Value %d", event, event-24, Panel.vpr_int );
      break;
    }
  }
}



void ScrollBarInit()
{
  Panel.Send(MonitorScrollBox, "MonitorScrollBox");
  Panel.Send(MonitorField_1, "MonitorField_1");
  Panel.Send(MonitorField_2, "MonitorField_2");
  Panel.Send(MonitorField_3, "MonitorField_3");
  Panel.Send(MonitorField_4, "MonitorField_4");
  Panel.Send(MonitorField_5, "MonitorField_5");
  Panel.Send(MonitorField_6, "MonitorField_6");

  Panel.Send(Display_1, "display 1");
  Panel.Send(Display_2, "display 2");
  Panel.Send(Display_3, "display 3");
  Panel.Send(Display_4, "display 4");

  Panel.Send(ScrollBar_1, true);
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
 
  Panel.Send(Led_2,  "$WHITE");
  Panel.Send(Led_3,  "$YELLOW");
  Panel.Send(Led_4,  "$ORANGE");
  Panel.Send(Led_5,  "$RED");
  Panel.Send(Led_6,  "$BLUE");

  Panel.Send(Led_10,  "$BLUE");
  Panel.Send(Led_11,  "$GREEN");
  Panel.Send(Led_12,  "$YELLOW");
  Panel.Send(Led_13,  "$ORANGE");

}




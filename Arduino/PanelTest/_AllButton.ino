
void AllButtonCallback(int event, int type)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
      AllButtonInit();
      break; 
    }

    case Button_4:
    {
      PanelMode = ScrollBar;
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


void AllButtonInit()
{
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
  Panel.Send(Led_2,  "$WHITE");
  Panel.Send(Led_3,  "$YELLOW");
  Panel.Send(Led_4,  "$ORANGE");
  Panel.Send(Led_5,  "$RED");
  Panel.Send(Led_6,  "$BLUE");
  Panel.Send(Led_7,  "$GREEN");
  Panel.Send(Led_8,  "$YELLOW");
  Panel.Send(Led_9,  "$ORANGE");
  Panel.Send(Led_10,  "$BLUE");
  Panel.Send(Led_11,  "$GREEN");
  Panel.Send(Led_12,  "$YELLOW");
  Panel.Send(Led_13,  "$ORANGE");

  Panel.Send(MonitorScrollBox, "AllButtonPanel");
  Panel.Send(MonitorField_1, false);
  Panel.Send(MonitorField_2, (byte)254 );
  Panel.Send(MonitorField_3, (int)-32768 );
  Panel.Send(MonitorField_4, (unsigned int)65535 );
  Panel.Send(MonitorField_5, (long)-2147483648 );
  Panel.Send(MonitorField_6, (unsigned long)4294967295 );
}





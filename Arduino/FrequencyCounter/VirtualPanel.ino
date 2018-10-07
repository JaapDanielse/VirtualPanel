
//------------------------------------------------------------------------
void PanelCallback(int chanel, int type)
{
  // Called by Panel.Receive after receiving a panel event
  
  switch (chanel) 
  {
    case PanelConnected: // Pannel connected: Init Controls
    { // initialize panel layout
      MyPanelInit();
      break; 
    }

    case DynamicDisplay: // DynamicDisplay requested: Send Dynamic Data
    {   MyPanelDynamicDisplay(); 
      break; 
    }
    
    case Button_3:// (on/off) pressed
    { Power=!Power; 
      if(!Power) frequency = 0.0;
      if(Power) MyPanel.Send(Led_1,"$RED"); else MyPanel.Send(Led_1,"$OFF");
      break; 
    }

    break;
  }
}

//------------------------------------------------------------------------
void MyPanelInit()
{ // initialize panel layout
  MyPanel.Send(ApplicationName, "Arduino Frequency Counter" ); 
  MyPanel.Send(DynamicDisplay, true);
  MyPanel.Send(Button_3,"$ONOFF" );
  MyPanel.Send(Led_1,"$OFF");
  MyPanel.Send(Display_1,"$BOLD");
}

//------------------------------------------------------------------------
void MyPanelDynamicDisplay()
{ // output dynamic display data
  char temp[10];

  dtostrf(frequency, 4, 1, temp); // %f not supported in Sendf
  MyPanel.Sendf(Display_1,"Freq. %s Hz", temp);
  dtostrf((1000.0/frequency), 4, 1, temp); // %f not supported in Sendf
  if(frequency != 0.0) 
    MyPanel.Sendf(Display_2,"period %s ms", temp);
  else
    MyPanel.Send(Display_2,"");
}

     






//------------------------------------------------------------------------
void PanelCallback(int chanel, int type)
{
  // Called by Panel.Receive after receiving a panel event
  
  switch (chanel) 
  {
    case PanelConnected: // Pannel connected: Init Controls
    { // initialize panel layout
      PanelInit();
      break; 
    }

    case DynamicDisplay: // DynamicDisplay requested: Send Dynamic Data
    {   PanelDynamicDisplay(); 
      break; 
    }
    
    case Button_3:// (on/off) pressed
    { Power=!Power; 
      if(!Power) frequency = 0.0;
      if(Power) Panel.Send(Led_1,"$RED"); else Panel.Send(Led_1,"$OFF");
      break; 
    }

    break;
  }
}

//------------------------------------------------------------------------
void PanelInit()
{ // initialize panel layout
  Panel.Send(ApplicationName, "Frequency Counter" ); 
  Panel.Send(DynamicDisplay, true);
  Panel.Send(Button_3,"$ONOFF" );
  Panel.Send(Led_1,"$OFF");
  Panel.Send(Display_1,"$BIG");
  Panel.Send(Display_2,"$BLACK");
}

//------------------------------------------------------------------------
void PanelDynamicDisplay()
{ // output dynamic display data
  char temp[10];

  dtostrf(frequency, 6, 4, temp); // %f not supported in Sendf
  Panel.Sendf(Display_1,"Freq. %s Hz", temp);
  
  if (frequency > -0.0000)
  {
    dtostrf((1000000.0/frequency), 4, 2, temp); // %f not supported in Sendf
    Panel.Sendf(Display_2,"period %s µs", temp);
  }
  else
    Panel.Send(Display_2,"period 0.00 µs");
}

     





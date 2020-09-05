
//------------------------------------------------------------------------
void PanelCallback(vp_channel event)
{
  // Called by Panel.Receive after receiving a panel event
  
  switch (event) 
  {
    case PanelConnected: InitPanel(); break; 
    case DynamicDisplay: PanelDynamicDisplay(); break; 
    case Button_3: 
      Power=!Power; 
      if(!Power) frequency = 0.0;
      if(Power) Panel.send(Led_1,"$RED"); else Panel.send(Led_1,"$OFF");
      break; 
    case Button_4: InfoPanel=!InfoPanel; Panel.send(Info,InfoPanel); break;
    default: break;
  }
}

//------------------------------------------------------------------------
void InitPanel()
{ // initialize panel layout
  Panel.send(ApplicationName, "Frequency Counter" ); 
  Panel.send(DynamicDisplay, true);
  Panel.send(Button_3,"⚫⚪" );
  Panel.send(Button_4,"info" );
  Panel.send(Led_1,"$OFF");
  Panel.send(Display_1,"$BIG");
  Panel.send(Display_2,"$BLACK");

  Panel.send(InfoTitle,F("Frequency Counter")); // Info title
  Panel.send(InfoText, F("Virtual Panel showcase application")); // Info text
  Panel.send(InfoText, F("Jan & Jaap Daniëlse (2IΔ) 2019")); //
  Panel.send(InfoText, F("")); //
  Panel.send(InfoText, F("Signal input on D5 (not connected on Mega)")); //
  Panel.send(InfoText, F("Counts frequencies up to 4 MHz\n")); //
  Panel.send(InfoText, F("Documentation:")); //
  Panel.send(InfoText, F("https://github.com/JaapDanielse/VirtualPanel/wiki/Frequency-Counter-Example")); //

}

//------------------------------------------------------------------------
void PanelDynamicDisplay()
{
  if (frequency > -0.0000)
  {
    if (frequency >= 1000000)
    {
      Panel.sendf(Display_1,"%s Hz", _FString(frequency,0,0));
      Panel.sendf(Display_2,"period %s ns", _FString((1000000000.0/frequency),4,1));
    }
    else if (frequency >= 1000)   
    {
      Panel.sendf(Display_1,"%s Hz", _FString(frequency,0,1));
      Panel.sendf(Display_2,"period %s us", _FString((1000000.0/frequency),4,1));
    }
    else   
    {
      Panel.sendf(Display_1,"%s Hz", _FString(frequency,0,2));
      Panel.sendf(Display_2,"period %s ms",  _FString((1000.0/frequency),0,2));
    }
  }
  else
  {
    Panel.send(Display_1,"0.00 Hz");
    Panel.send(Display_2,"period 0.00 µs");
  }
}

     

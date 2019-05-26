
//------------------------------------------------------------------------
void PanelCallback(int chanel, int type)
{
  // Called by Panel.Receive after receiving a panel event
  
  switch (chanel) 
  {
    case PanelConnected: PanelInit(); break; 
    case DynamicDisplay: PanelDynamicDisplay(); break; 
    case Button_3: 
      Power=!Power; 
      if(!Power) frequency = 0.0;
      if(Power) Panel.Send(Led_1,"$RED"); else Panel.Send(Led_1,"$OFF");
      break; 
    case Button_4: InfoPanel=!InfoPanel; Panel.Send(Info,InfoPanel); break; 
  }
}

//------------------------------------------------------------------------
void PanelInit()
{ // initialize panel layout
  Panel.Send(ApplicationName, "Frequency Counter" ); 
  Panel.Send(DynamicDisplay, true);
  Panel.Send(Button_3,"⚫⚪" );
  Panel.Send(Button_4,"info" );
  Panel.Send(Led_1,"$OFF");
  Panel.Send(Display_1,"$BIG");
  Panel.Send(Display_2,"$BLACK");

  Panel.Send(InfoTitle,F("Frequency Counter")); // Info title
  Panel.Send(InfoText, F("Virtual Panel showcase application")); // Info text
  Panel.Send(InfoText, F("Jan & Jaap Daniëlse (2IΔ) 2019")); //
  Panel.Send(InfoText, F("")); //
  Panel.Send(InfoText, F("Signal input on D5")); //
  Panel.Send(InfoText, F("Counts frequencies up to 4 MHz\n")); //
  Panel.Send(InfoText, F("Documentation:")); //
  Panel.Send(InfoText, F("https://github.com/JaapDanielse/VirtualPanel/wiki/Frequency-Counter-Example")); //

}

//------------------------------------------------------------------------
void PanelDynamicDisplay()
{
  if (frequency > -0.0000)
  {
    if (frequency >= 1000000)
    {
      Panel.Sendf(Display_1,"%s Hz", _FString(frequency,0,0));
      Panel.Sendf(Display_2,"period %s ns", _FString((1000000000.0/frequency),4,1));
    }
    else if (frequency >= 1000)   
    {
      Panel.Sendf(Display_1,"%s Hz", _FString(frequency,0,1));
      Panel.Sendf(Display_2,"period %s us", _FString((1000000.0/frequency),4,1));
    }
    else   
    {
      Panel.Sendf(Display_1,"%s Hz", _FString(frequency,0,2));
      Panel.Sendf(Display_2,"period %s ms",  _FString((1000.0/frequency),0,2));
    }
  }
  else
  {
    Panel.Send(Display_1,"0.00 Hz");
    Panel.Send(Display_2,"period 0.00 µs");
  }
}

     

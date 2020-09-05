

// Callback
//-----------------------------------------------------------------------------------------------
void PanelCallback(vp_channel event)
{
  switch (event) 
  {
    case PanelConnected: InitPanel(); break; 

    case Button_3: Power=!Power; break; 
    case Button_4: InfoPanel=!InfoPanel; break; 
    case Slider_2: KiloHertz = Panel.vpr_int; SetKiloHertz(); break; 
    case Slider_3: HertzStep = Panel.vpr_int; SetHertz(); break; 
    case Slider_4: Duty = Panel.vpr_int; break;
    default: break;
  }
  StaticChange(); 
}

void InitPanel()
{ // initialize panel layout
  Panel.send(ApplicationName, "Signal Generator" ); 
  Panel.send(Display_1,"$BIG");
  Panel.send(Display_4,"$BLACK");

  Panel.send(Button_3,"⚫⚪" );
  Panel.send(Button_4,"info" );
  Panel.send(Led_1,"$OFF");

  Panel.send(Slider_2, "KHz" );
  Panel.send(MaxSlider_2, KiloHertzSteps);
  Panel.send(Slider_2, KiloHertz);
  Panel.send(Slider_3, "Hz" ); 
  Panel.send(MaxSlider_3, HertzStepCount);
  Panel.send(Slider_3, HertzStep);
  Panel.send(Slider_4, "duty%"  );
  Panel.send(MaxSlider_4, 100);
  Panel.send(Slider_4, Duty );

  Panel.send(InfoTitle,F("Signal Generator")); // Info title
  Panel.send(InfoText, F("Virtual Panel showcase application")); // Info text
  Panel.send(InfoText, F("Jan & Jaap Daniëlse (2IΔ) 2019\n")); //
  Panel.send(InfoText, F("Signal output on D9 (D11 on Mega2560)")); //
  Panel.send(InfoText, F("Generates blockwave from 1Hz to 50KHz")); //
  Panel.send(InfoText, F("Duty cycle can be set fro 0 to 100%")); //
  Panel.send(InfoText, F("In higher frequencies stepsize increases (indicated)\n")); //
  Panel.send(InfoText, F("Documentation:")); //
  Panel.send(InfoText, F("https://github.com/JaapDanielse/VirtualPanel/wiki/Signal-Generator-Example")); //

  SetKiloHertz();
  SetHertz();
  StaticChange();
}


//--------------------------------------------------------------------------------------------
void SetKiloHertz()
{
  if (KiloHertz == 0)
  {
    HertzStepOffset = ClockFrequency;
    HertzStepCount = HertzStepOffset;
  }
  else
  {
    HertzStepOffset = (unsigned int)((1.0/((float)KiloHertz*1000.0))/0.0000000625);
    HertzStepCount = HertzStepOffset;
    HertzStepCount -= (unsigned int)((1.0/((float)(KiloHertz+1)*1000.0))/0.0000000625)+1;
  }

  if( HertzStepCount < 1000)
     Panel.send(MaxSlider_3, HertzStepCount);
  else
     Panel.send(MaxSlider_3, 999);

  HertzStep = 0;
  SetHertz();

}


//--------------------------------------------------------------------------------------------
void SetHertz()
{
  if(KiloHertz == KiloHertzRange) HertzStep = 0;
  
  if( HertzStepCount > 999)
  {
    NextHertzStep = 1;
    Frequency = HertzStep + (KiloHertz*1000);
  }
  else
  {
    Frequency = ClockFrequency / (HertzStepOffset - HertzStep);
    NextHertzStep = ClockFrequency / (HertzStepOffset - (HertzStep+1));
    NextHertzStep -= Frequency;
  }
}


//--------------------------------------------------------------------------------------------
void StaticChange()
{
  char  outstr1[10]; // float conversion buffer 1

  if(Power) Panel.send(Led_1,"$RED"); else Panel.send(Led_1,"$OFF");
  if(InfoPanel) Panel.send(Info, true); else Panel.send(Info, false);

  Panel.sendf(Display_1,"%05ld Hz", Frequency ); // Return Static value for scrollbar only
  Panel.sendf(Display_2,"duty %03d %%", Duty ); // Return Static value for scrollbar only
  Panel.sendf(Display_4,"%dHz step", NextHertzStep ); // Return Static value for scrollbar only

  if (Frequency >= 245) Prescaler = 1;
  if (Frequency < 245 && Frequency >= 31) Prescaler = 8;
  if (Frequency < 31 && Frequency >= 4) Prescaler = 64;
  if (Frequency < 4 && Frequency >= 1) Prescaler = 256;

  TimeUnit = (ClockTime * (float)Prescaler);

  if (Frequency > 0) 
    Top = (unsigned int)((1.0 / (float)Frequency) / TimeUnit);
  else
    Top = 0;

  DutyValue = (Top/100) * Duty;

  if(Power)
    SetFrequency(Prescaler, Top, DutyValue);
  else
    SetFrequency(0, 0, 0);

  int HertzSliderSteps = HertzStepCount;
  if(HertzStepCount>999) HertzSliderSteps = 999;

  if ( NextHertzStep == 1 ) Panel.send(Led_11,"$GREEN");
  if ( NextHertzStep > 1 ) Panel.send(Led_11,"$BLUE");
  if ( NextHertzStep > 25 ) Panel.send(Led_11,"$ORANGE");
  if ( NextHertzStep > 100 ) Panel.send(Led_11,"$RED");
  
  Panel.sendf(MonitorField_1,"Hertz Steps: %d/%d", HertzStepCount, HertzSliderSteps ); 
  Panel.sendf(MonitorField_2,"Hertz Offset: %ld", HertzStepOffset ); //
  Panel.sendf(MonitorField_3,"Step: %d Hz", NextHertzStep ); //
  Panel.sendf(MonitorField_4,"Top Value: %u - Duty: %d ", Top, DutyValue ); // 
  dtostrf(TimeUnit * 1000000.0,0,4,outstr1); // convert float to string 
  Panel.sendf(MonitorField_5,"Prescaler: %d / TimeUnit: %s µS", Prescaler, outstr1 ); // Return Static value for scrollbar only

} 

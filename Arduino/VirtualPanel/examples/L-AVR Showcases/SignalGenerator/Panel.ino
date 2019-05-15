

// Callback
//-----------------------------------------------------------------------------------------------
void PanelCallback(int event, int type)
{
  switch (event) 
  {
    case PanelConnected: PanelInit(); break; 

    case Button_3: Power=!Power; break; 
    case Button_4: InfoPanel=!InfoPanel; break; 
    case Slider_2: KiloHertz = Panel.vpr_int; SetKiloHertz(); break; 
    case Slider_3: HertzStep = Panel.vpr_int; SetHertz(); break; 
    case Slider_4: Duty = Panel.vpr_int; break; 
  }
  StaticChange(); 
}

void PanelInit()
{ // initialize panel layout
  Panel.Send(ApplicationName, "Signal Generator" ); 
  Panel.Send(Display_1,"$BIG");
  Panel.Send(Display_4,"$BLACK");

  Panel.Send(Button_3,"$ONOFF" );
  Panel.Send(Button_4,"info" );
  Panel.Send(Led_1,"$OFF");

  Panel.Send(Slider_2, "KHz" );
  Panel.Send(MaxSlider_2, KiloHertzSteps);
  Panel.Send(Slider_2, KiloHertz);
  Panel.Send(Slider_3, "Hz" ); 
  Panel.Send(MaxSlider_3, HertzStepCount);
  Panel.Send(Slider_3, HertzStep);
  Panel.Send(Slider_4, "duty%"  );
  Panel.Send(MaxSlider_4, 100);
  Panel.Send(Slider_4, Duty );

  Panel.Send(InfoTitle,F("Signal Generator")); // Info title
  Panel.Send(InfoText, F("Virtual Panel showcase application")); // Info text
  Panel.Send(InfoText, F("Jan & Jaap Daniëlse (2IΔ) 2019")); //
  Panel.Send(InfoText, F("")); //
  Panel.Send(InfoText, F("Signal input on D9")); //
  Panel.Send(InfoText, F("Generates blockwave from 1Hz to 50KHz")); //
  Panel.Send(InfoText, F("Duty cycle can be set fro 0 to 100%")); //
  Panel.Send(InfoText, F("In higher frequencies stepsize increases (indicated)")); //

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
     Panel.Send(MaxSlider_3, HertzStepCount);
  else
     Panel.Send(MaxSlider_3, 999);

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

  if(Power) Panel.Send(Led_1,"$RED"); else Panel.Send(Led_1,"$OFF");
  if(InfoPanel) Panel.Send(Info, true); else Panel.Send(Info, false);

  Panel.Sendf(Display_1,"Freq. %05ld Hz", Frequency ); // Return Static value for scrollbar only
  Panel.Sendf(Display_2,"duty %03d %%", Duty ); // Return Static value for scrollbar only
  Panel.Sendf(Display_4,"%dHz step", NextHertzStep ); // Return Static value for scrollbar only

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

  if ( NextHertzStep == 1 ) Panel.Send(Led_11,"$GREEN");
  if ( NextHertzStep > 1 ) Panel.Send(Led_11,"$BLUE");
  if ( NextHertzStep > 25 ) Panel.Send(Led_11,"$ORANGE");
  if ( NextHertzStep > 100 ) Panel.Send(Led_11,"$RED");
  
  Panel.Sendf(MonitorField_1,"Hertz Steps: %d/%d", HertzStepCount, HertzSliderSteps ); 
  Panel.Sendf(MonitorField_2,"Hertz Offset: %ld", HertzStepOffset ); //
  Panel.Sendf(MonitorField_3,"Step: %d Hz", NextHertzStep ); //
  Panel.Sendf(MonitorField_4,"Top Value: %u - Duty: %d ", Top, DutyValue ); // 
  dtostrf(TimeUnit * 1000000.0,0,4,outstr1); // convert float to string 
  Panel.Sendf(MonitorField_5,"Prescaler: %d / TimeUnit: %s µS", Prescaler, outstr1 ); // Return Static value for scrollbar only

} 











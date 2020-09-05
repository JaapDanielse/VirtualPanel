// Calibrate Panel Module
//

 byte SetChannelId = 3;
 bool ChannelSelect = false;
 
 enum InputList 
{
  InputCalibration,
  InputInterval,
  InputAttenualtion,
  InputUpperAlarm,
  InputLowerAlarm,
  InputNotSet
};

InputList InputMode = InputNotSet;

//---------------------------------------------------------------
void SettingsCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: InitSettingsPanel(); break; 
    case Button_1:  SetChannelSelect(); break;
    case Button_2:  SetAttenuation(); break;
    case Button_8:  SetDigits(); break;
    case Button_9:  SetUpperAlarm(); break;
    case Button_10: SetLowerAlarm(); break;
    case Button_11: ClearAlarm(); break;
    case Button_12: SetInterval(); break;
    case Button_14: SetCalibration(); break;
    case Button_15: InfoPanel(); break;  
    case Button_16: GraphPanel(); break;  
    case Button_17: ReturnFromSettings(); break;
    case PanelInput_1: HandleInput(); break;
    case PanelInput_2: HandleInput(); break;
    default: break;
  }
}

//---------------------------------------------------------------
void SetCalibration()
{
  if(InputMode != InputNotSet) return;
  Panel.send(MinPanelInput_2, (float)4.40);
  Panel.send(MaxPanelInput_2, (float)5.25);
  Panel.send(PanelInputLabel_2, F("Input Arduino AREF"));
  Panel.send(PanelInput_2, VCCMeasured);
  Panel.send(Display_1, F("Calibrate meter"));
  Panel.send(Display_2, false);
  Panel.send(Display_3, false);
  Panel.send(Display_4, false);
  ChannelSelect = false;
  CalibrateInfo();
  InputMode = InputCalibration;
}

//---------------------------------------------------------------
void SetInterval()
{
  if(InputMode != InputNotSet) return;
  Panel.send(MinPanelInput_2, (int)100);
  Panel.send(MaxPanelInput_2, (int)2000);
  Panel.send(PanelInputLabel_2, F("Interval 100-2000"));
  Panel.send(PanelInput_2, MeasureInterval);
  Panel.send(Display_1, F("Measure interval"));
  Panel.send(Display_2, false);
  Panel.send(Display_3, false);
  Panel.send(Display_4, false); 
  InputMode = InputInterval;
}

//---------------------------------------------------------------
void SetUpperAlarm()
{
  if(!ChannelSelect) return;
  if(InputMode != InputNotSet) return;
  Panel.send(MinPanelInput_1, LowerAlarm[SetChannelId]);
  Panel.send(MaxPanelInput_1, VCCMeasured*Attenuation[SetChannelId]);
  Panel.send(PanelInputLabel_1, F("Set ▲! Voltage"));
  Panel.send(PanelInput_1, UpperAlarm[SetChannelId]);
  InputMode = InputUpperAlarm;
}

//---------------------------------------------------------------
void SetLowerAlarm()
{
  if(!ChannelSelect) return;
  if(InputMode != InputNotSet) return;
  Panel.send(MinPanelInput_2, (float)0.0);
  if(UpperAlarm[SetChannelId] > 0)
    Panel.send(MaxPanelInput_2, UpperAlarm[SetChannelId]);
  else
    Panel.send(MaxPanelInput_2, VCCMeasured*Attenuation[SetChannelId]);
  Panel.send(PanelInputLabel_2, F("Set ▼! Voltage"));
  Panel.send(PanelInput_2, LowerAlarm[SetChannelId]);
  InputMode = InputLowerAlarm;
}

//---------------------------------------------------------------
void ClearAlarm()
{
  if(!ChannelSelect) return;
  UpperAlarm[SetChannelId] = 0;
  LowerAlarm[SetChannelId] = 0;
  DisplaySelectedChannelData();
}

//---------------------------------------------------------------
void SetAttenuation()
{
  if(!ChannelSelect) return;
  if(InputMode != InputNotSet) return;
  Panel.send(MinPanelInput_2, (float)1.0);
  Panel.send(MaxPanelInput_2, (float)4.0);
  Panel.send(PanelInputLabel_2, F("Set att. factor"));
  Panel.send(PanelInput_2, Attenuation[SetChannelId]);
  InputMode = InputAttenualtion;
}


//---------------------------------------------------------------
void SetDigits()
{
  if(!ChannelSelect) return;

  if(Digits == 2)
  {
    Digits = 3;
    Panel.send(Button_8,  F("digits\n0.00"));
  }
  else
  {
    Digits = 2;
    Panel.send(Button_8,  F("digits\n0.000"));
  }
  DisplaySelectedChannelData();
}

//---------------------------------------------------------------
void HandleInput()
{
  if(Panel.vpr_type == vp_type::vp_void) 
  {
    if(Calibrated) DisplaySelectedChannelData();
    InputMode = InputNotSet;
    return;
  }
  
  switch(InputMode)
  {
     case InputCalibration:
       DoCalibrate();
       break;

     case InputInterval:
       MeasureInterval = Panel.vpr_int;
       break;
       
     case InputAttenualtion:
       Attenuation[SetChannelId] = Panel.vpr_float;
       CalculateScalefactors();
       break;
       
     case InputUpperAlarm: 
       UpperAlarm[SetChannelId] = Panel.vpr_float;
       break;
       
     case InputLowerAlarm: 
       LowerAlarm[SetChannelId] = Panel.vpr_float;
       break;

     default: break;
  }
  DisplaySelectedChannelData();
  InputMode = InputNotSet;
}

//---------------------------------------------------------------
void DoCalibrate()
{
  if(Panel.vpr_type == vp_type::vp_float)
  { 
    VCCMeasured = Panel.vpr_float;
    BandGapVolts = BandGapVoltage(VCCMeasured);
    CalculateScalefactors();
    InitADConverter();
    Calibrated = true;
    SaveSettings();
    Panel.sendf(MonitorLog, F("Calibrated"));
    Panel.sendf(MonitorLog, F(""));
    MonitorCalibrateValues();
    Panel.send(Led_8, F("$GREEN"));
    SettingInfo();
    Panel.send(Info, InfoMode);
    DisplaySelectedChannelData();
  }
}

//---------------------------------------------------------------
void SetChannelSelect()
{
  if(!Calibrated || InputMode != InputNotSet) return;
  
  if(++SetChannelId > 3) SetChannelId = 0;
  DisplaySelectedChannelData();
}

//---------------------------------------------------------------
void DisplaySelectedChannelData()
{
  if(!Calibrated) return;
    
  Panel.sendf(Display_3, F("CH%d"), SetChannelId+1);
  Panel.sendf(Display_1, F("▲! %s V"), _FString(UpperAlarm[SetChannelId], 0, Digits));     
  Panel.sendf(Display_2, F("▼! %s V"), _FString(LowerAlarm[SetChannelId], 0, Digits));     
  Panel.sendf(Display_4, F("Att. %sX"), _FString(Attenuation[SetChannelId],3,1));

  if(SetChannelId == 0) Panel.send(Led_10, F("$YELLOW"));
  if(SetChannelId == 1) Panel.send(Led_10, F("$GREEN"));
  if(SetChannelId == 2) Panel.send(Led_10, F("$BLUE"));
  if(SetChannelId == 3) Panel.send(Led_10, F("$PURPLE"));
  
  ChannelSelect = true;
}

//---------------------------------------------------------------
void ReturnFromSettings()
{
  SaveSettings();
  PanelMode = MeterMode; 
  Panel.send(Reset);
}

//---------------------------------------------------------------
void InitSettingsPanel()
{
  Panel.send(ApplicationName,F("4-Channel Voltmeter/Logger")); // set the application name
  Panel.send(PanelColor, F("$RED")); // set the application name
  Panel.send(Button_1,  F("chan.\nsel."));
  Panel.send(Button_2,  F("attenu-\nation"));
  
  if(Digits==2) Panel.send(Button_8,  F("digits\n0.000")); else Panel.send(Button_8,  F("digits\n0.00")); 
  
  Panel.send(Button_9,  F("upper\nalarm"));
  Panel.send(Button_10, F("lower\nalarm"));
  Panel.send(Button_11, F("clear\nalarm"));

  Panel.send(Button_12, F("inter-\nval"));
  Panel.send(Button_14, F("cali-\nbrate"));

  Panel.send(Button_15, F("info"));
  Panel.send(Button_17, F("return"));
  
  InputMode = InputNotSet;
  SetChannelId = 0;

  if(!Calibrated)
  {
    Panel.send(Led_8, F("$RED"));
    SetCalibration();
  }
  else
  {
    Panel.send(Led_8, F("$GREEN"));
    SettingInfo();
    DisplaySelectedChannelData();
  }
   Panel.send(Info, InfoMode);
}

//---------------------------------------------------------------
void CalibrateInfo()
{
  Panel.send(InfoTitle, F("4-Channel Voltmeter/Logger"));
  Panel.send(InfoText,  F("Calibrate requests you to input the Arduino AREF-pin voltage measured with a DMM"));
  Panel.send(InfoText,  F("With this value the actual voltage of this Arduino's band-gap can be measured."));
  Panel.send(InfoText,  F("The band gap value is not very precice, but very stable."));
  Panel.send(InfoText,  F("Once known (and saved in EEPROM) it can be used to dertermine"));
  Panel.send(InfoText,  F("the actual VCC. This is used as reference for AD measurements."));
  Panel.send(InfoText,  F("It can differ depending on the USB port used."));
  Panel.send(InfoText,  F("\nMore info:"));
  Panel.send(InfoText,  F("https://github.com/JaapDanielse/VirtualPanel/wiki/4-Channel-Voltmeter-Example"));
  Panel.send(Info, true);
}

//---------------------------------------------------------------
void SettingInfo()
{
  Panel.send(InfoTitle, F("4-Channel Voltmeter/Logger"));
  Panel.send(InfoText,  F("Measurment interval (all channels) 100ms - 2000 ms"));
  Panel.send(InfoText,  F("Channel specific settings (chan. sel.):"));
  Panel.send(InfoText,  F(" - Attenualtion 1x-4x (external attenuation needed))"));
  Panel.send(InfoText,  F(" - Upper/Lower Alarm (float) allowed. Values dependent on set attenuation"));
  Panel.send(InfoText,  F("\nMore info:"));
  Panel.send(InfoText,  F("https://github.com/JaapDanielse/VirtualPanel/wiki/4-Channel-Voltmeter-Example"));
}

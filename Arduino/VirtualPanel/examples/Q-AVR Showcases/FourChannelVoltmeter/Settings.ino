// Settings Module
// Saves properties that need remembering after power off.
// Uses the EepromSav Module. 
// Setting are invalidated after a new build.

struct FCVSettings
{
  bool Calibrated;
  float BandGapVolts;
  bool GraphMode;
  bool Sound;
  int MeasureInterval;
  float DigitCalcValue;
  int   Digits;
  bool ChannelOn[4];
  float Attenuation[4];
  float UpperAlarm[4];
  float LowerAlarm[4];
  bool AlarmLine[4];

} Settings;


//---------------------------------------------------------------
void SaveSettings()
{
  Settings.Calibrated = Calibrated;
  Settings.BandGapVolts = BandGapVolts;
  Settings.GraphMode = GraphMode;
  Settings.MeasureInterval = MeasureInterval;
  Settings.DigitCalcValue = DigitCalcValue;
  Settings.Digits = Digits;
  Settings.Sound = Sound;
  for(int i=0; i<4; i++)
  {
    Settings.ChannelOn[i]   = ChannelOn[i];
    Settings.Attenuation[i] = Attenuation[i];
    Settings.UpperAlarm[i]  = UpperAlarm[i];
    Settings.LowerAlarm[i]  = LowerAlarm[i];
    Settings.AlarmLine[i]   = AlarmLine[i];
  }
  WriteStructEEPROM(Settings);
}

//---------------------------------------------------------------
void ReadSettings()
{
  if ( ReadStructEEPROM(Settings))
  {
    Calibrated = Settings.Calibrated;
    BandGapVolts = Settings.BandGapVolts;
    GraphMode = Settings.GraphMode;
    MeasureInterval = Settings.MeasureInterval;
    DigitCalcValue = Settings.DigitCalcValue;
    Digits = Settings.Digits;
    Sound = Settings.Sound;
    for(int i=0; i<4; i++)
    {
      ChannelOn[i]   = Settings.ChannelOn[i];
      Attenuation[i] = Settings.Attenuation[i];
      UpperAlarm[i]  = Settings.UpperAlarm[i];
      LowerAlarm[i]  = Settings.LowerAlarm[i];
      AlarmLine[i]   = Settings.AlarmLine[i];
    }
  }
  else
    SaveSettings();
}

// MeterPanel Module
// Main meter display

//---------------------------------------------------------------
void MeterCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: InitMeterPanel(); break; 
    case Button_1:  ChannelToggle(0); break; 
    case Button_2:  ChannelToggle(1); break;
    case Button_3:  SoundToggle(); break;
    case Button_9:  ChannelToggle(2); break;
    case Button_10: ChannelToggle(3); break;
    case Button_11: ReqRecording(); break;
    case Button_14: LogViewPanel(); break;
    case Button_15: InfoPanel(); break;  
    case Button_16: GraphPanel(); break;  
    case Button_17: SettingsPanel(); break;  
    case OpenFile_1: OpenLogFile(); break;  
    case GraphLabel_1: ReqGraphInput(GraphInput_1, CHName[0]); break;  
    case GraphLabel_2: ReqGraphInput(GraphInput_2, CHName[1]); break;  
    case GraphLabel_3: ReqGraphInput(GraphInput_3, CHName[2]); break;  
    case GraphLabel_4: ReqGraphInput(GraphInput_4, CHName[3]); break;  
    case GraphInput_1: GraphInput(CHName[0]); break;
    case GraphInput_2: GraphInput(CHName[1]); break;
    case GraphInput_3: GraphInput(CHName[2]); break;
    case GraphInput_4: GraphInput(CHName[3]); break;
    case GraphButton_1: GraphAlarmLine(0); break;
    case GraphButton_2: GraphAlarmLine(1); break;
    case GraphButton_3: GraphAlarmLine(2); break;
    case GraphButton_4: GraphAlarmLine(3); break;
    case DynamicDisplay: DisplayDynamicValues(); break;
    default: break;
  }
}

//---------------------------------------------------------------
void DisplayDynamicValues()
{
  static bool BeepAlarm[4]={false, false, false, false};
  bool BeepNow[4];

  if(Recording) WriteLogData();

  BeepNow[0] = DisplayVoltage(Display_3, RealVoltage[0], &ChannelAlarm[0], &BeepAlarm[0], false);
  BeepNow[1] = DisplayVoltage(Display_4, RealVoltage[1], &ChannelAlarm[1], &BeepAlarm[1], false);
  BeepNow[2] = DisplayVoltage(Display_1, RealVoltage[2], &ChannelAlarm[2], &BeepAlarm[2], false);
  BeepNow[3] = DisplayVoltage(Display_2, RealVoltage[3], &ChannelAlarm[3], &BeepAlarm[3], false);
  if(BeepNow[0] || BeepNow[1] || BeepNow[2] || BeepNow[3])
  { 
    WriteAlarmToIndex();
    if(Sound) Panel.send(Beep);
  }

  if(ChannelOn[0]) Panel.send( GraphValue_1, (byte)map((int)(RealVoltage[0]*100.0),0,VMax,0,255));
  if(ChannelOn[1]) Panel.send( GraphValue_2, (byte)map((int)(RealVoltage[1]*100.0),0,VMax,0,255));
  if(ChannelOn[2]) Panel.send( GraphValue_3, (byte)map((int)(RealVoltage[2]*100.0),0,VMax,0,255));
  if(ChannelOn[3]) Panel.send( GraphValue_4, (byte)map((int)(RealVoltage[3]*100.0),0,VMax,0,255));
}

//---------------------------------------------------------------
void ChannelToggle(int ChannelNumber)
{
  if (!Recording)
  {
    ChannelOn[ChannelNumber] = !ChannelOn[ChannelNumber];
    ChannelIndicatorInit();
    InitGraph(false);
    SaveSettings();
  }
}

//---------------------------------------------------------------
void SoundToggle()
{
  Sound = !Sound;
  if(Sound) Panel.send(Led_1, F("$ORANGE")); else Panel.send(Led_1, F("$BLACK"));   
  SaveSettings();
}

//---------------------------------------------------------------
void SettingsPanel()
{
  if (!Recording)
  {
    PanelMode = SettingsMode; 
    Panel.send(Reset);  
  }
}

//---------------------------------------------------------------
void LogViewPanel()
{
  if(!Recording)
  {
    PanelMode = LogViewMode; 
    Panel.send(Reset);  
  }
}

//---------------------------------------------------------------
void ReqRecording()
{
  if(!Recording)
  { 
    if(UseSketchPath)
    { 
      char SketchPath[] = __FILE__; // 
      *(strrchr(SketchPath, '\\')+1)=0; // truncate to a path
      Panel.send(OpenFile_1, SketchPath);
    }
    Panel.send(FileOpenDialogTitle_1, F("Open Voltmeter Log File"));
    Panel.send(OpenFile_1, F("VoltmeterLog.vml"));
    
    // catch in OpenFile_1 > LogFileOpen()
  }
  else
  {
    WriteIndex();
    Recording = false;
    LogFileOpen = false;
    Panel.sendf(MonitorLog, F("Recording stopped"));
    Panel.send(Led_7, F("$BLACK"));
    Panel.send(Button_1, F("$BLACK"));
    Panel.send(Button_2, F("$BLACK"));
    Panel.send(Button_9, F("$BLACK"));
    Panel.send(Button_10, F("$BLACK"));
    Panel.send(Button_14, F("$BLACK"));
    Panel.send(Button_17, F("$BLACK"));
  }
}

//---------------------------------------------------------------
void OpenLogFile()
{
  if(Panel.vpr_type == vp_type::vp_long)
  {
    InitRecordLogData();
    Recording = true;
    LogFileOpen = true;
    Panel.send(Led_7, F("$RED"));
    Panel.send(Button_1, F("$GRAY"));
    Panel.send(Button_2, F("$GRAY"));
    Panel.send(Button_9, F("$GRAY"));
    Panel.send(Button_10, F("$GRAY"));
    Panel.send(Button_14, F("$GRAY"));
    Panel.send(Button_17, F("$GRAY"));
    Panel.sendf(MonitorLog, F("Recording started"));
  }
}


//---------------------------------------------------------------
void ReqGraphInput(vp_channel event, char * ChannelName)
{
  if(!Recording)
  {
    Panel.send( event, ChannelName);
  }
}

//---------------------------------------------------------------
void GraphInput(char * ChannelName)
{
  if(Panel.vpr_type == vp_type::vp_string)
  {
    strcpy( ChannelName, Panel.vpr_string);
    InitGraph(false);
  }   
}

//---------------------------------------------------------------
void GraphAlarmLine(int ChannelNum)
{
   AlarmLine[ChannelNum] = !AlarmLine[ChannelNum];
   InitGraph(false);
 }

//---------------------------------------------------------------
void InitMeterPanel()
{
  ReadSettings(); 
  MonitorCalibrateValues();    
  CalculateScalefactors();
  CommonPanelInit();
  ChannelIndicatorInit();
  InitGraph(false);
  VoltMeterInfo();

  if(Sound) Panel.send(Led_1, F("$ORANGE")); else Panel.send(Led_1, F("$BLACK"));   
  Panel.send(Led_7, F("$BLACK"));
  Panel.send(Button_3, F("alarm\nsound"));
  Panel.send(Button_11, F("record\nlog"));
  Panel.send(Button_14, F("view\nlog"));
  Panel.send(Button_17, F("set-\ntings"));  

  if (Calibrated) Panel.send(Led_9, F("$GREEN")); else Panel.send(Led_9, F("$OFF"));
  Panel.send(DynamicDisplay, MeasureInterval);
}

//---------------------------------------------------------------
void MonitorCalibrateValues()
{
  Panel.sendf(MonitorLog, F("4-Channel Voltmeter/Logger Startup"));
  Panel.sendf(MonitorLog, F("Build - %s %s"), __DATE__ __TIME__ );
  Panel.sendf(MonitorLog, F(""));
  Panel.sendf(MonitorLog, F("Arduino AREF: %s"), _FString(VCCMeasured,6,4));
  Panel.sendf(MonitorLog, F("BandGap Voltage: %s"), _FString(BandGapVolts,6,4));
  Panel.sendf(MonitorLog, F("V Max measure: %s"), _FString(VCCMeasured,4,2));
  Panel.sendf(MonitorLog, F("Corr. Slope: %s"), _FString(SlopeCorrection,8,6));
  Panel.sendf(MonitorLog, F("Corr. Offset: %s"), _FString(OffsetCorrection,8,6));
  Panel.sendf(MonitorLog, F(""));
}

//---------------------------------------------------------------
void VoltMeterInfo()
{
  Panel.send(InfoTitle, F("4-Channel Voltmeter/Logger"));
  Panel.send(InfoText,  F("Measures voltages of max 4 channels. (Select with CH1-CH4)."));
  Panel.send(InfoText,  F("Measure pins are A0-A3. Default range = 0-5V (usb-max)."));
  Panel.send(InfoText,  F("External Attenuation supported."));
  Panel.send(InfoText,  F("Channel names can be changed by double clicking the graph labels,"));
  Panel.send(InfoText,  F("Set alarm values are visualized in red and blue and (selectable)"));
  Panel.send(InfoText,  F("with red and blue lines in the graph panel."));
  Panel.send(InfoText,  F("Green settings Led indicates callibration done."));
  Panel.send(InfoText,  F("\nMore info:"));
  Panel.send(InfoText,  F("https://github.com/JaapDanielse/VirtualPanel/wiki/4-Channel-Voltmeter-Example"));
}

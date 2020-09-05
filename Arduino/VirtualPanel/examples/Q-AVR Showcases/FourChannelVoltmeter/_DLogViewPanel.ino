// LogView Panel
//

bool PlayBack = false;

//---------------------------------------------------------------
void LogViewCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: InitLogViewPanel(); break; 
    case Button_3: if(!PlayBack)SetupWindowRead(0); break;  
    case Button_4: if(!PlayBack)SetupWindowRead(-2); break;  
    case Button_5: if(!PlayBack)SetupWindowRead(-1); break;  
    case Button_6: PlayLog(); break;  
    case Button_7: if(!PlayBack)SetupWindowRead(1); break;  
    case Button_8: if(!PlayBack)SetupWindowRead(2); break;  
    case Button_15: InfoPanel(); break;  
    case Button_16: GraphPanel(); break;  
    case Button_17: ReturnFromLogView(); break;
    case Button_11: ReqOpenLog(); break;
    case GraphButton_1: PlaybackAlarmLine(0); break;
    case GraphButton_2: PlaybackAlarmLine(1); break;
    case GraphButton_3: PlaybackAlarmLine(2); break;
    case GraphButton_4: PlaybackAlarmLine(3); break;
    case OpenFile_1: LogOpen(); break;  
    case ReadLineFile_1: ReadDataFromFile(); break;
    case DynamicDisplay: PlayBackLog(); break;
    default: break;
  }
}

//---------------------------------------------------------------
void PlayBackLog()
{
  if (PlayBack) 
    Panel.send(ReadLineFile_1);
}

//---------------------------------------------------------------
void PlayLog()
{
  if(!PlayBack )
  {
    InitGraph(true);
    Panel.send(DynamicDisplay, MeasureInterval);
    Panel.send(Button_3, F("$GRAY"));
    Panel.send(Button_4, F("$GRAY"));
    Panel.send(Button_5, F("$GRAY"));
    Panel.send(Button_6, F("■"));
    Panel.send(Button_7, F("$GRAY"));
    Panel.send(Button_8, F("$GRAY"));
    StartPlayBack();
    PlayBack = true;
  }
  else
  {
    Panel.send(DynamicDisplay, false);
    Panel.send(Button_3, F("$BLACK"));
    Panel.send(Button_4, F("$BLACK"));
    Panel.send(Button_5, F("$BLACK"));
    Panel.send(Button_6, F("▶"));
    Panel.send(Button_7, F("$BLACK"));
    Panel.send(Button_8, F("$BLACK"));
    PlayBack = false;
  }
}

//---------------------------------------------------------------
void PlaybackAlarmLine(int ChannelNum)
{
   AlarmLine[ChannelNum] = !AlarmLine[ChannelNum];
   InitGraph(true);
 }

//---------------------------------------------------------------
void ReqOpenLog()
{
  if(UseSketchPath)
  { 
    char SketchPath[] = __FILE__; // 
    *(strrchr(SketchPath, '\\')+1)=0; // truncate to a path
    Panel.send(OpenFile_1, SketchPath);
  }
  Panel.send(FileOpenDialogTitle_1, F("Open Voltmeter Log File"));
  Panel.send(OpenFile_1, F("VoltmeterLog.vml"));
}

//---------------------------------------------------------------
void LogOpen()
{
  if(Panel.vpr_type == vp_type::vp_long)
  {
    LogDataEnd = Panel.vpr_long;
    LogFileOpen = true;
    Panel.send(Led_7, F("$GREEN"));
    InitViewLogData(); 
  }
  else
  {
    LogFileOpen = false;
    Panel.send(Led_7, F("$OFF"));
  }
}

//---------------------------------------------------------------
void ReadDataFromFile()
{ 
  char DataBuffer[60];

  if(Panel.vpr_type == vp_type::vp_string)
  {
    strcpy(DataBuffer, Panel.vpr_string);
    ReadTarget(DataBuffer);
  } 
  else
  {
    PlayLog(); 
  }
}

//---------------------------------------------------------------
void ReturnFromLogView()
{
  LogFileOpen = false; 
  PanelMode = MeterMode; 
  Panel.send(Reset);
}

//---------------------------------------------------------------
void InitLogViewPanel()
{
  CommonPanelInit();
  InitGraph(true);
  LogViewInfo();
  
  Panel.send(Display_1, F("$BLACK"));
  Panel.send(Display_2, F("$BLACK"));
  Panel.send(Display_3, F("$BLACK"));
  Panel.send(Display_4, F("$BLACK"));
  
  Panel.send(Button_1, F("$GRAY")); 
  Panel.send(Button_2, F("$GRAY"));
  Panel.send(Button_9, F("$GRAY"));
  Panel.send(Button_10, F("$GRAY"));

  Panel.send(Button_17, F("return"));
  
  Panel.send(Button_3, F("▮◁"));
  Panel.send(Button_4, F("🞇◁"));
  Panel.send(Button_5, F("◁"));
  Panel.send(Button_6, F("▶"));
  Panel.send(Button_7, F("▷"));
  Panel.send(Button_8, F("▷🞇"));
  
  Panel.send(Led_7, F("$OFF"));
  Panel.send(Button_11, F("log\nfile"));
}


//---------------------------------------------------------------
void LogViewInfo()
{
  Panel.send(InfoTitle, F("4-Channel Voltmeter/Logger"));
  Panel.send(InfoText,  F("▮◁ - Start of recording"));
  Panel.send(InfoText,  F("🞇◁ - Previous alarm point"));
  Panel.send(InfoText,  F("◁ - Previous Graph Page"));
  Panel.send(InfoText,  F("▶ - Playback (disables prev/next)"));
  Panel.send(InfoText,  F("▷ - Next Graph page"));
  Panel.send(InfoText,  F("▷🞇 - Next alarm point"));  
//  Panel.send(InfoText,  F("|< - Previous alarm point"));
//  Panel.send(InfoText,  F("o< - Previous alarm point"));
//  Panel.send(InfoText,  F("< - Previous Graph Page"));
//  Panel.send(InfoText,  F("> / [] - Playback / stop (disables prev/next)"));
//  Panel.send(InfoText,  F("> - Next Graph page"));
//  Panel.send(InfoText,  F(">o - Next alarm point"));
  Panel.send(InfoText,  F("\nMore info:"));
  Panel.send(InfoText,  F("https://github.com/JaapDanielse/VirtualPanel/wiki/4-Channel-Voltmeter-Example"));
}

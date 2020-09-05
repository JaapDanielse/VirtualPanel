// Logger Module
// Handles all log file interactions

#define SettingDataStart 1//
#define IndexDataStart 35//
#define IndexSize 50 //
#define LogDataStart 100//
#define WindowSize 60//
#define WindowBufferSize 10 //

int IndexPosition = 0;
long SettingsPosition = 0;
long LogPosition = 0;
long LogDataEnd = 0;

long WindowStart = 0;
long WindowEnd = 0;

long IndexData[IndexSize];
float WindowValueBuffer[WindowBufferSize+1][4];
int  WindowAlarmBuffer[WindowBufferSize+1][4];
int  WindowBufferWriteIdx = 0;
int  WindowBufferReadIdx = 1;

typedef void (*ReadTarget_ptr)(char *);
ReadTarget_ptr ReadTarget = &ReadLogSettings;

//---------------------------------------------------------------
void InitRecordLogData()
{
  Panel.send(ClearFile_1);
  SettingsPosition = SettingDataStart;
  LogPosition = LogDataStart;
  IndexPosition = 0;
  WriteLogSettings();
  for(int i=0; i < IndexSize; i++) { IndexData[i] = 0;}
  Panel.send(WriteLineFile_1, LogPosition);
}

//---------------------------------------------------------------
void WriteLogSettings()
{
  Panel.send(WriteLineFile_1,  (long)SettingDataStart);
  Panel.send(WriteLineFile_1,  APPID);
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(VMaxMeasurable * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), MeasureInterval);
  Panel.sendf(WriteLineFile_1, F("%d"), Digits);
  Panel.sendf(WriteLineFile_1, F("%d"), ChannelOn[0]);
  Panel.sendf(WriteLineFile_1, F("%d"), ChannelOn[1]);
  Panel.sendf(WriteLineFile_1, F("%d"), ChannelOn[2]);
  Panel.sendf(WriteLineFile_1, F("%d"), ChannelOn[3]);
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(Attenuation[0] * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(Attenuation[1] * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(Attenuation[2] * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(Attenuation[3] * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(UpperAlarm[0]  * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(UpperAlarm[1]  * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(UpperAlarm[2]  * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(UpperAlarm[3]  * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(LowerAlarm[0]  * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(LowerAlarm[1]  * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(LowerAlarm[2]  * DigitCalcValue));
  Panel.sendf(WriteLineFile_1, F("%d"), (int)(LowerAlarm[3]  * DigitCalcValue));
  Panel.send(WriteLineFile_1,  CHName[0]);
  Panel.send(WriteLineFile_1,  CHName[1]);
  Panel.send(WriteLineFile_1,  CHName[2]);
  Panel.send(WriteLineFile_1,  CHName[3]);
}


//---------------------------------------------------------------
void WriteAlarmToIndex()
{
  if(IndexPosition >= IndexSize)
    return;
  IndexData[IndexPosition++] = LogPosition-1;
}

//---------------------------------------------------------------
void WriteIndex()
{
  Panel.send(WriteLineFile_1, (long)IndexDataStart);
  for(int i=0; i<IndexSize; i++)
  {
    Panel.sendf(WriteLineFile_1, "%d", IndexData[i]);
  }
}

//---------------------------------------------------------------
void WriteLogData()
{
  char FloatBuf1[8];
  char FloatBuf2[8];
  char FloatBuf3[8];
  char FloatBuf4[8];

  Panel.sendf( WriteLineFile_1, F("%s:%d, %s:%d, %s:%d, %s:%d"),
    _FString(RealVoltage[0],0,Digits,FloatBuf1),ChannelAlarm[0],
    _FString(RealVoltage[1],0,Digits,FloatBuf2),ChannelAlarm[1],
    _FString(RealVoltage[2],0,Digits,FloatBuf3),ChannelAlarm[2],
    _FString(RealVoltage[3],0,Digits,FloatBuf4),ChannelAlarm[3]);

  LogPosition++; // keep track of next line
}

//---------------------------------------------------------------
void InitViewLogData()
{
  for(int i=0; i < WindowBufferSize; i++)
  {
    for(int j=0; j < 4; j++)
    {
      WindowValueBuffer[i][j] = 0;
      WindowAlarmBuffer[i][j] = 0;
    }
  }
  WindowStart = 0;
  WindowEnd = 0;
  SettingsPosition = SettingDataStart;
  ReadTarget = &ReadLogSettings;
  Panel.send(ReadLineFile_1, SettingsPosition);
  Panel.send(ReadLineFile_1);
}

//---------------------------------------------------------------
void ReadLogSettings(char * SettingsData)
{
  int NumData;
  const char ScanfNum[] = "%d";
  
  switch (SettingsPosition)
  {
    case SettingDataStart:
      Panel.send(Display_2, false);
      Panel.send(Display_3, false);
      Panel.send(Display_4, false);
      if(strcmp(APPID, SettingsData))
      {
        Panel.send(Display_1, F("Invalid file format"));
        return;
      }
      else
        Panel.send(Display_1, F("Log data available"));
      break;
    case SettingDataStart+1:  sscanf(SettingsData,ScanfNum, &NumData); VMaxMeasurable = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+2:  sscanf(SettingsData,ScanfNum, &NumData); MeasureInterval = NumData; break;
    case SettingDataStart+3:  sscanf(SettingsData,ScanfNum, &NumData); Digits = NumData; break;
    case SettingDataStart+4:  sscanf(SettingsData,ScanfNum, &NumData); ChannelOn[0]   = NumData; break;
    case SettingDataStart+5:  sscanf(SettingsData,ScanfNum, &NumData); ChannelOn[1]   = NumData; break;
    case SettingDataStart+6:  sscanf(SettingsData,ScanfNum, &NumData); ChannelOn[2]   = NumData; break;
    case SettingDataStart+7:  sscanf(SettingsData,ScanfNum, &NumData); ChannelOn[3]   = NumData; break;
    case SettingDataStart+8:  sscanf(SettingsData,ScanfNum, &NumData); Attenuation[0] = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+9:  sscanf(SettingsData,ScanfNum, &NumData); Attenuation[1] = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+10: sscanf(SettingsData,ScanfNum, &NumData); Attenuation[2] = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+11: sscanf(SettingsData,ScanfNum, &NumData); Attenuation[3] = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+12: sscanf(SettingsData,ScanfNum, &NumData); UpperAlarm[0]  = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+13: sscanf(SettingsData,ScanfNum, &NumData); UpperAlarm[1]  = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+14: sscanf(SettingsData,ScanfNum, &NumData); UpperAlarm[2]  = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+15: sscanf(SettingsData,ScanfNum, &NumData); UpperAlarm[3]  = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+16: sscanf(SettingsData,ScanfNum, &NumData); LowerAlarm[0]  = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+17: sscanf(SettingsData,ScanfNum, &NumData); LowerAlarm[1]  = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+18: sscanf(SettingsData,ScanfNum, &NumData); LowerAlarm[2]  = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+19: sscanf(SettingsData,ScanfNum, &NumData); LowerAlarm[3]  = (float)NumData /DigitCalcValue; break;
    case SettingDataStart+20: strcpy(CHName[0], SettingsData); break;
    case SettingDataStart+21: strcpy(CHName[1], SettingsData); break;
    case SettingDataStart+22: strcpy(CHName[2], SettingsData); break;
    case SettingDataStart+23: strcpy(CHName[3], SettingsData); break;
    case SettingDataStart+24: 
      VMax = (int)((VMaxMeasurable + 0.5)*100.0);
      if (Digits == 2) DigitCalcValue = 100.0; else DigitCalcValue = 1000.0;
      IndexPosition = 0;
      Panel.send(ReadLineFile_1, (long)IndexDataStart);
      ReadTarget = &ReadIndex;
    break;
  }
  SettingsPosition++;
  Panel.send(ReadLineFile_1);   
}

//---------------------------------------------------------------
void ReadIndex(char * IndexLine)
{
  long NumData;
    
  if( IndexPosition < IndexSize)
  {
    sscanf(IndexLine,"%ld", &NumData);
    IndexData[IndexPosition++] = NumData;
  }
  else
  {
    ChannelIndicatorInit();
    InitGraph(true);
    SetupWindowRead(0);
    return;
  }
  Panel.send(ReadLineFile_1);
}

//---------------------------------------------------------------
void SetupWindowRead(int Page)
{
  long WinStartSave;

  WinStartSave = WindowStart;
  
  if(Page == -1)
  {
    WindowStart = (LogPosition) - (WindowSize * 2);
  }

  else if(Page == 1)
  {
    WindowStart = LogPosition;
  }

  else if(Page == 2)
  {
    for (int i=0; i<IndexSize; i++)
    {
      if(IndexData[i] > (LogPosition-1) - WindowBufferSize) 
      {
        WindowStart = IndexData[i] - ((WindowSize-1) - WindowBufferSize);
        break;
      }
    }
  }

  else if(Page == -2)
  {
    for (int i=IndexSize; i>=0; i--)
    {
      if(IndexData[i]!=0 && IndexData[i] < (LogPosition-1) - WindowBufferSize) 
      {
        WindowStart = IndexData[i] - ((WindowSize-1) - WindowBufferSize);
        break;
      }
    }
  }
  
  else if(Page == 0)
  {
    WindowStart = LogDataStart;
  }

  if(WindowStart < LogDataStart)
  {
    WindowStart = LogDataStart;
  }

  WindowEnd = WindowStart + WindowSize-1;

  if(WindowEnd > LogDataEnd)
  {
    WindowStart = LogDataEnd - (WindowSize - 1);
    WindowEnd = LogDataEnd;
  }

  Panel.sendf(MonitorLog, "Window %ld - %ld", WindowStart, WindowEnd);
  
  if(WinStartSave == WindowStart) return;
  
  Panel.send(GraphValue_1, F("$STATIC"));
  Panel.send(GraphValue_2, F("$STATIC"));
  Panel.send(GraphValue_3, F("$STATIC"));
  Panel.send(GraphValue_4, F("$STATIC"));
  Panel.send(GraphValue_1, F("$CLEAR"));
  Panel.send(GraphValue_2, F("$CLEAR"));
  Panel.send(GraphValue_3, F("$CLEAR"));
  Panel.send(GraphValue_4, F("$CLEAR"));
  ReadTarget = &ReadLogWindow;
  LogPosition = WindowStart;
  Panel.send(ReadLineFile_1, WindowStart);
  Panel.send(ReadLineFile_1);
}


//---------------------------------------------------------------
void ReadLogWindow(char * LogData)
{
  ReadLogDataLine(LogData);

  if(LogPosition <= WindowEnd)
  {
    Panel.send(ReadLineFile_1);
  }
}

//---------------------------------------------------------------
void StartPlayBack()
{
  Panel.send(GraphValue_1, F("$ROLLING"));
  Panel.send(GraphValue_2, F("$ROLLING"));
  Panel.send(GraphValue_3, F("$ROLLING"));
  Panel.send(GraphValue_4, F("$ROLLING"));
  WindowStart = 0; // playback requires window reset
  ReadTarget = &ReadLogDataLine;
}


//---------------------------------------------------------------
void ReadLogDataLine(char * LogData )
{
  bool B;
  int V[4]={0};
  int D[4]={0};
  int A[4]={0};
  float F[4]={0.0};
   
  sscanf(LogData, "%d.%d:%d, %d.%d:%d, %d.%d:%d, %d.%d:%d" ,&V[0],&D[0],&A[0], &V[1],&D[1],&A[1], &V[2],&D[2],&A[2], &V[3],&D[3],&A[3]);

  for(int i=0; i<4; i++)
  {
    F[i] = (float)V[i]+((float)D[i]/DigitCalcValue);
    WindowValueBuffer[WindowBufferWriteIdx][i] = F[i];
    WindowAlarmBuffer[WindowBufferWriteIdx][i] = A[i];
  }
  
  WindowBufferWriteIdx = (WindowBufferWriteIdx+1) % (WindowBufferSize+1);
  WindowBufferReadIdx = WindowBufferWriteIdx;

  DisplayVoltage(Display_3, WindowValueBuffer[WindowBufferReadIdx][0], &WindowAlarmBuffer[WindowBufferReadIdx][0], &B, true);
  DisplayVoltage(Display_4, WindowValueBuffer[WindowBufferReadIdx][1], &WindowAlarmBuffer[WindowBufferReadIdx][1], &B, true);
  DisplayVoltage(Display_1, WindowValueBuffer[WindowBufferReadIdx][2], &WindowAlarmBuffer[WindowBufferReadIdx][2], &B, true);
  DisplayVoltage(Display_2, WindowValueBuffer[WindowBufferReadIdx][3], &WindowAlarmBuffer[WindowBufferReadIdx][3], &B, true);
  
  if(ChannelOn[0]) Panel.send( GraphValue_1, (byte)map((int)(F[0]*100.0),0,VMax,0,255));
  if(ChannelOn[1]) Panel.send( GraphValue_2, (byte)map((int)(F[1]*100.0),0,VMax,0,255));
  if(ChannelOn[2]) Panel.send( GraphValue_3, (byte)map((int)(F[2]*100.0),0,VMax,0,255));
  if(ChannelOn[3]) Panel.send( GraphValue_4, (byte)map((int)(F[3]*100.0),0,VMax,0,255));

//  Panel.send( GraphText, _Point(70,17));
  Panel.send(GraphText, _Point(5,197));
  Panel.sendf( GraphText, ("tot. rec. %s s"), _FString(float((LogDataEnd - LogDataStart + 1 - WindowBufferSize) * MeasureInterval)/1000.0, 4,2));
  Panel.send( GraphText, _Point(145,17));
  Panel.sendf( GraphText, ("%s s"), _FString(float((LogPosition - LogDataStart + 1 - WindowBufferSize) * MeasureInterval)/1000.0, 4,2));

  LogPosition++; // keep track of next line
}

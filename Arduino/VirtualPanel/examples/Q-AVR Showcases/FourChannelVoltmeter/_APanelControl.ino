// Panel Dispatcher and common routines
// Contains PanelCallback and dispatches to MeterPanel, SettingsPanel or LogViewPanel

enum ModeList 
{
  MeterMode,
  SettingsMode,
  LogViewMode,
  Endmode
};

ModeList PanelMode = MeterMode;

//---------------------------------------------------------------
void PanelCallback(vp_channel event) 
{ 
  // PanelCallback is called when a message is received from the panel 
  // only channel and type are passed as parameters. Panel data available as public library vars

   switch (PanelMode)
   {
     case MeterMode:
       MeterCallback( event); break;

     case SettingsMode: 
       SettingsCallback( event); break;

     case LogViewMode: 
       LogViewCallback( event); break;

     default: break;
   }
}

//---------------------------------------------------------------
void InfoPanel()
{
  InfoMode = !InfoMode;
  if (InfoMode) Panel.send(Info, true); else Panel.send(Info, false);
}

//---------------------------------------------------------------
void GraphPanel()
{
  GraphMode = !GraphMode;
  if (GraphMode) Panel.send(Graph, true); else Panel.send(Graph, false); 
}

//---------------------------------------------------------------
bool DisplayVoltage(vp_channel Event, float Voltage, int * Alarm, bool * BeepAlarm, bool Playback)
{
  char Sign[5] = " ";
  bool AlarmOut = false;
  
  if(*Alarm == 1)
  {
    Panel.send(Event, "$RED");
    strcpy(Sign,"▲");
    if(!(*BeepAlarm)) AlarmOut = true;
    *BeepAlarm = true;
  } 
  else if(*Alarm == -1)
  {
    Panel.send(Event, "$BLUE");
    strcpy(Sign,"▼");
    if(!(*BeepAlarm)) AlarmOut = true;
    *BeepAlarm = true;
  }
  else // Alarm == 0
  {
    if(Playback) Panel.send(Event, F("$BLACK")); else Panel.send(Event, F("$WHITE"));
    strcpy(Sign," ");
    *BeepAlarm = false;
  }
  if(!Playback) *Alarm = 0;   
  Panel.sendf( Event, F("%s%s V"), Sign, _FString(Voltage,0,Digits));
  return AlarmOut;
}  

//---------------------------------------------------------------
void InitGraph(bool LogView)
{
  Panel.send(Graph, F("$CLEAR"));

  Panel.send(GraphGrid, 10);
  Panel.send(GraphValueCount_1, 60);
  Panel.send(GraphValueCount_2, 60);
  Panel.send(GraphValueCount_3, 60);
  Panel.send(GraphValueCount_4, 60);

  Panel.send(MaxGraphInput_1, 16);
  Panel.send(MaxGraphInput_2, 16);
  Panel.send(MaxGraphInput_3, 16);
  Panel.send(MaxGraphInput_4, 16);
  
  GraphChannelInit(GraphValue_1, GraphLabel_1, GraphButton_1, 0);
  GraphChannelInit(GraphValue_2, GraphLabel_2, GraphButton_2, 1);
  GraphChannelInit(GraphValue_3, GraphLabel_3, GraphButton_3, 2);
  GraphChannelInit(GraphValue_4, GraphLabel_4, GraphButton_4, 3);

  Panel.send(GraphText, F("$WHITE"));
  Panel.send(GraphText, _Point(230,214));
  Panel.sendf(GraphText, F("%d V"), (VMax/100));
  Panel.send(GraphText, _Point(230,17));
  Panel.send(GraphText, F("0 V"));
  Panel.send(GraphText, _Point(5,214));
  Panel.sendf(GraphText, F("int. %d ms - %d ms/div. "), MeasureInterval, (MeasureInterval*60)/12 );

  if(LogView)
  {
    Panel.send( GraphDrawLine, "$WHITE");
    Panel.send( GraphDrawLine, _Line(215,15,215,205));
    Panel.send( GraphDrawLine );
    Panel.send( GraphDrawLine, _Point(215,210));
    Panel.send( GraphDrawLine, _Point(212,215));
    Panel.send( GraphDrawLine, _Point(218,215));
    Panel.send( GraphDrawLine, _Point(215,210));
    Panel.send( GraphDrawLine );
    Panel.send( GraphDrawLine, _Point(215,10));
    Panel.send( GraphDrawLine, _Point(212,5));
    Panel.send( GraphDrawLine, _Point(218,5));
    Panel.send( GraphDrawLine, _Point(215,10));
    Panel.send( GraphDrawLine );

    Panel.send( GraphDrawLine, _Point(180,19));
    Panel.send( GraphDrawLine, _Point(180,22));
    Panel.send( GraphDrawLine, _Point(211,22));
    Panel.send( GraphDrawLine );
    Panel.send( GraphDrawLine, _Point(206,25));
    Panel.send( GraphDrawLine, _Point(211,22));
    Panel.send( GraphDrawLine, _Point(206,19));

  }  
}

//---------------------------------------------------------------
void GraphChannelInit(vp_channel Value, vp_channel Label, vp_channel Button, int ChannelNum)
{
  if(ChannelOn[ChannelNum])
  {
    Panel.send(Label, ChannelColor[ChannelNum]);
    Panel.send(Label, CHName[ChannelNum]);
    Panel.send(GraphText, _Point(5,17+(15*ChannelNum)));
    Panel.send(GraphText, ChannelColor[ChannelNum]);
    Panel.send(GraphText, CHName[ChannelNum]);
    Panel.send(Value, ChannelColor[ChannelNum]);


    if(UpperAlarm[ChannelNum]>0 || LowerAlarm[ChannelNum]>0)
    {
      Panel.send(Button, F("$SMALL"));
      if (AlarmLine[ChannelNum])
      { 
        Panel.sendf(Button, F("▲▼\nCH%d"), ChannelNum+1);
        if(UpperAlarm[ChannelNum]>0)
        {
          int AlarmLevel = (byte)map((int)(UpperAlarm[ChannelNum]*100.0),0,VMax,0,255);
          Panel.send(GraphDrawLine, ChannelColor[ChannelNum]);
          Panel.send(GraphDrawLine, F("$3PX"));
          Panel.send(GraphDrawLine, _VLine(0,AlarmLevel,10,AlarmLevel));
          Panel.send(GraphDrawLine, F("$RED"));
          Panel.send(GraphDrawLine, F("$1PX"));
          Panel.send(GraphDrawLine, _VLine(15,AlarmLevel,255,AlarmLevel));
        }
        if(LowerAlarm[ChannelNum]>0)
        {
          int AlarmLevel = (byte)map((int)(LowerAlarm[ChannelNum]*100.0),0,VMax,0,255);
          Panel.send(GraphDrawLine, ChannelColor[ChannelNum]);
          Panel.send(GraphDrawLine, F("$3PX"));
          Panel.send(GraphDrawLine, _VLine(0,AlarmLevel,10,AlarmLevel));
          Panel.send(GraphDrawLine, F("$BLUE"));
          Panel.send(GraphDrawLine, F("$1PX"));
          Panel.send(GraphDrawLine, _VLine(15,AlarmLevel,255,AlarmLevel));
        }
      }
      else
      { 
        Panel.sendf(Button, F("△▽\nCH%d"), ChannelNum+1);
      }
    }
  }
  else
  {
    Panel.send(Value, F("$CLEAR"));
    Panel.send(Label, false);
    Panel.send(Button, false);
  }
}

//---------------------------------------------------------------
void ChannelIndicatorInit()
{
  if(ChannelOn[0]) Panel.send(Led_10, ChannelColor[0]); else Panel.send(Led_10, F("$OFF"));
  Panel.send(Button_1, F("CH1")); 
  if(ChannelOn[1]) Panel.send(Led_11, ChannelColor[1]); else Panel.send(Led_11, F("$OFF"));
  Panel.send(Button_2, F("CH2"));
  if(ChannelOn[2]) Panel.send(Led_12, ChannelColor[2]); else Panel.send(Led_12, F("$OFF"));
  Panel.send(Button_9, F("CH3"));
  if(ChannelOn[3]) Panel.send(Led_13, ChannelColor[3]); else Panel.send(Led_13, F("$OFF"));
  Panel.send(Button_10, F("CH4"));
}

//---------------------------------------------------------------
void CommonPanelInit()
{
  Panel.send(ApplicationName,"4-Channel Voltmeter/Logger"); // set the application name
  Panel.send(PanelColor,"$RED"); // set the application name
  
  Panel.send(Button_15, F("info"));
  Panel.send(Button_16, F("graph"));
  if (InfoMode) Panel.send(Info, true); else Panel.send(Info, false);
  if (GraphMode) Panel.send(Graph, true); else Panel.send(Graph, false);  
    
}

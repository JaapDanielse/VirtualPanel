

//---------------------------------------------------------------------------------
void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: InitPanel(); break;
    case Button_4:  Capture(); break;
    case Button_9:  SetSpeed(-1); break;
    case Button_8: Trigger = !Trigger; break;
    case Button_10: SetSpeed(+1); break;
    case Button_11: if(++TriggerBit>3) TriggerBit=0; break;
    case Button_12: SetBufSize(+1); break;
    case Button_13: SetBufSize(-1); break;
    case Button_14: TRizing = !TRizing; break;
    case Slider_5:  SetWindowPosition(Panel.vpr_int); break;
    case GraphClick: SetLeftMeasure(Panel.vpr_uint);  break;
    case GraphRightClick: SetRightMeasure(Panel.vpr_uint); break; 
    case GraphButton_1: SwitchMeasure(); break;
    case GraphButton_4: InfoPanel = !InfoPanel; break;
    case DynamicDisplay: DisplaySamplePage(false); break;
    default: break;
  }
  if( event != DynamicDisplay) StaticDisplay();
}


//---------------------------------------------------------------------------------
void SwitchMeasure()
{
  Measure = !Measure;

  if(!Measure)
  {
    DrawMeasure();
    X1Position = 0;
    X2Position = 0;  
  }
}


//---------------------------------------------------------------------------------
void SetLeftMeasure(unsigned int Position)
{
  if(Measure)
  {
    X1Position = (int)(float(WindowPosition * 2) + ((float)highByte(Position) / 4.25)+0.5);
   DrawMeasure();
  }
}


//---------------------------------------------------------------------------------
void SetRightMeasure(unsigned int Position)
{
  if(Measure)
  { 
    X2Position = (int)(float(WindowPosition * 2) + ((float)highByte(Position) / 4.25)+0.5);
    DrawMeasure();
  }
}


//---------------------------------------------------------------------------------
void SetWindowPosition(int Pos)
{
  char outstr[10];
  float TimePos; 
  
  WindowPosition = Pos;
  
  // output value to display   
  TimePos = (float)WindowPosition * 2.0 * (float)SampleSpeed;
  if(TimePos < 1000)
  { 
    dtostrf(TimePos,0,0,outstr); // convert float to string 
    Panel.sendf(Display_4, F("pos %s µs"), outstr);
  }
  else if(TimePos < 1000000) 
  {
    dtostrf(TimePos/1000.0,0,0,outstr); // convert float to string 
    Panel.sendf(Display_4, F("pos %s ms"), outstr);
  }
  else 
  {
    dtostrf(TimePos/1000000.0,0,1,outstr); // convert float to string 
    Panel.sendf(Display_4, F("pos %s s"), outstr);
  }
}


//---------------------------------------------------------------------------------
void SetBufSize(int Change)
{
  SampleBufSizeIdx += Change; 
  if( SampleBufSizeIdx > SampleBufSizeCount-1) SampleBufSizeIdx--;
  if( SampleBufSizeIdx < 0 ) SampleBufSizeIdx = 0;
  SampleBufSize = SampleBufSizeValues[SampleBufSizeIdx];  
  Panel.send(MaxSlider_5,SampleBufSize-(SampleWindow/4)); 
}


//---------------------------------------------------------------------------------
void SetSpeed(int Change)
{
  SampleSpeedIdx += Change; 
  if( SampleSpeedIdx > SampleSpeedCount-1) SampleSpeedIdx--;
  if( SampleSpeedIdx < 0 ) SampleSpeedIdx = 0;
  SampleSpeed = SampleSpeedValues[SampleSpeedIdx]; 
}

//---------------------------------------------------------------------------------
void Capture()
{
  Panel.send(DynamicDisplay, false);
  delay(100);
  while (Serial.available()){ Serial.read(); }
  Panel.send(Led_2,F("$ORANGE")); 
  Sample();
  while (Serial.available()){ Serial.read(); }
  Panel.send(DynamicDisplay, true);
  WindowPosition = 0;
  Panel.send(Slider_5,0); 
  DisplaySamplePage(true);
  SetWindowPosition(0); // reset position
  Panel.send(Led_2,F("$OFF")); 
}


//---------------------------------------------------------------------------------
void DrawDivisions()
{
  float DivisionOffset;
  char  outstr[10];

  Panel.send(GraphText,F("$DEL")); // set to delete text
  for(int i=0; i<=4; i++)
  {
    Panel.send(GraphText, _VPoint(41+(43*i)-10,ChanelHeight*4+25));
    Panel.sendf(GraphText, "", outstr );
  }

  Panel.send(GraphText,F("$WHITE"));

  for(int i=-0; i<=4; i++)
  {
    DivisionOffset = (float)((((float)(WindowPosition*2) + ((i+1)*10)) * (float)(SampleSpeed))/1000.0);
    if(DivisionOffset >= 1000)
      dtostrf(DivisionOffset,0,0,outstr); // convert float to string 
    else if(DivisionOffset >= 10)
      dtostrf(DivisionOffset,0,1,outstr); // convert float to string 
    else 
      dtostrf(DivisionOffset,0,2,outstr); // convert float to string 

    Panel.send(GraphText, _VPoint(41+(43*i)-10,ChanelHeight*4+25));
    Panel.sendf(GraphText, "%s", outstr );
  }

}


//---------------------------------------------------------------------------------
void DrawMeasure()
{

  static byte OldX1X=0;
  static byte OldX2X=0;
  static bool MeasureDrawn = false;

  if (MeasureDrawn)
  {
    Panel.send(GraphDrawLine, F("$DEL"));
    Panel.send(GraphDrawLine,_Line(OldX1X,3,OldX1X,166));
    Panel.send(GraphDrawLine, F("$DEL"));
    Panel.send(GraphDrawLine,_Line(OldX2X,3,OldX2X,166));
    MeasureDrawn = false;
  }
  
  if (Measure)
  {
    if( WindowPosition*2 < X1Position && (WindowPosition*2)+(SampleWindow/2) > X1Position)
    {
      OldX1X = (byte)((float)(X1Position - (WindowPosition*2)) * 4.25);
      Panel.send(GraphDrawLine, F("$YELLOW"));
      Panel.send(GraphDrawLine, F("$2PX"));
      Panel.send(GraphDrawLine,_Line(OldX1X,3,OldX1X,166));
      Panel.send(GraphDrawLine, F("$1PX"));
      MeasureDrawn = true;
    }

    if( WindowPosition*2 < X2Position && (WindowPosition*2)+(SampleWindow/2) > X2Position)
    {
      OldX2X = (byte)((float)(X2Position - (WindowPosition*2)) * 4.25);
      Panel.send(GraphDrawLine, F("$ORANGE"));
      Panel.send(GraphDrawLine, F("$2PX"));
      Panel.send(GraphDrawLine,_Line(OldX2X,3,OldX2X,166));
      Panel.send(GraphDrawLine, F("$1PX"));
      MeasureDrawn = true;
    }
  }
}


//---------------------------------------------------------------------------------
void DisplaySamplePage(bool ForceDisplay)
{
  static int Offset = 0;
  int TempOffset=0;

  if( Offset != WindowPosition || ForceDisplay)
  {
    Offset = WindowPosition;
    TempOffset = Offset;
  
    for( int i=TempOffset; i < TempOffset + (SampleWindow/4); i++)
    { // loop for all values in the window

      // output high (first) nibble
      for( int j=0; j<2; j++) // output every sample twice
      {
        Panel.send(GraphValue_1, (byte)((bitRead(SampleBuffer[i],4)*SignalHeight)+(ChanelHeight*3)+SignalMargin)); //D8
        Panel.send(GraphValue_2, (byte)((bitRead(SampleBuffer[i],5)*SignalHeight)+(ChanelHeight*2)+SignalMargin)); //D9
        Panel.send(GraphValue_3, (byte)((bitRead(SampleBuffer[i],6)*SignalHeight)+(ChanelHeight*1)+SignalMargin)); //D10
        Panel.send(GraphValue_4, (byte)((bitRead(SampleBuffer[i],7)*SignalHeight)+(ChanelHeight*0)+SignalMargin)); //D11
      }

      // output low (second) nibble
      for( int j=0; j<2; j++) // output every sample twice
      {
        Panel.send(GraphValue_1, (byte)((bitRead(SampleBuffer[i],0)*SignalHeight)+(ChanelHeight*3)+SignalMargin)); //D8
        Panel.send(GraphValue_2, (byte)((bitRead(SampleBuffer[i],1)*SignalHeight)+(ChanelHeight*2)+SignalMargin)); //D9
        Panel.send(GraphValue_3, (byte)((bitRead(SampleBuffer[i],2)*SignalHeight)+(ChanelHeight*1)+SignalMargin)); //D10 
        Panel.send(GraphValue_4, (byte)((bitRead(SampleBuffer[i],3)*SignalHeight)+(ChanelHeight*0)+SignalMargin)); //D11
      }
    }
    DrawDivisions(); // outpur division values
    DrawMeasure(); // output measure (if selected)
  }
}


//---------------------------------------------------------------------------------
void StaticDisplay()
{
  char  outstr[10];
  
  Panel.sendf(Display_1, F("buf. %d Sa"), SampleBufSize*2);

  if(SampleSpeed >= 1000)
    Panel.sendf(Display_3, F("%d ms/Sa"), SampleSpeed/1000);
  else
    Panel.sendf(Display_3, F("%d µs/Sa"), SampleSpeed);

  if (Trigger) 
  {
    Panel.send(Led_6, F("$ORANGE"));
    Panel.sendf(Button_11, F("trigger\nch%d"),TriggerBit); 
    if (TRizing) 
    {
      Panel.send(Button_14,F("△\ntrig")); 
      Panel.send(Led_8, F("$ORANGE")); 
    }
    else 
    {
      Panel.send(Button_14,F("trig\n▽"));
      Panel.send(Led_8, F("$YELLOW")); 
    }
    if(TriggerBit == 0) Panel.send(Led_7, F("$RED")); 
    if(TriggerBit == 1) Panel.send(Led_7, F("$PURPLE")); 
    if(TriggerBit == 2) Panel.send(Led_7, F("$BLUE")); 
    if(TriggerBit == 3) Panel.send(Led_7, F("$GREEN")); 
  }
  else
  {
    Panel.send(Led_6, F("$BLACK"));
    Panel.send(Led_7, F("$GRAY")); 
    Panel.send(Led_8, F("$GRAY")); 
  }
  
  if (Measure) Panel.send(GraphButton_1, F("$BLACK")); else   Panel.send(GraphButton_1, F("$GRAY"));

  long TimePerDivision = (long)(SampleWindow/2)*(long)SampleSpeed/6;
  if(TimePerDivision >= 1000)
  {
    TimePerDivision =TimePerDivision/1000;
    Panel.sendf(Display_2, F("%ld ms/div"), TimePerDivision);
  }
  else
    Panel.sendf(Display_2, F("%ld µs/div"), TimePerDivision);

  dtostrf(((float)X1Position*(float)SampleSpeed)/1000.0,0,2, outstr); // convert float to string 
  Panel.sendf(GraphLabel_1, F(" T-X1  %s ms"),outstr);
  dtostrf(((float)X2Position*(float)SampleSpeed)/1000.0,0,2, outstr); // convert float to string 
  Panel.sendf(GraphLabel_2, F(" T-X2  %s ms"),outstr);
  dtostrf((float)((X2Position-X1Position)*(float)SampleSpeed)/1000.0,0,2,outstr); // convert float to string 
  Panel.sendf(GraphLabel_3, F(" ΔX %s ms"), outstr);
  dtostrf(1/((float)((X2Position-X1Position)*(float)SampleSpeed)/1000000.0),0,2,outstr); // convert float to string 
  Panel.sendf(GraphLabel_4, F(" 1/ΔX f %s Hz"), outstr);

  if (InfoPanel) Panel.send(Info, true); else Panel.send(Info, false);
  
}


//---------------------------------------------------------------------------------
void InitPanel()
{
  Panel.send(ApplicationName,"Logic Analyzer"); // set the application name
  Panel.send(Button_4,F("cap-\nture")); // Button_3 visible and set text "on/off
  Panel.send(Button_8,F("trigger")); 
  Panel.send(Button_11,F("trig\nch0")); 
  Panel.send(Button_14,F("△\ntrig")); 
  Panel.send(Led_2,F("$OFF")); 
  Panel.send(Led_6,F("$OFF")); 
  Panel.send(Led_7,F("$GRAY")); 
  Panel.send(Led_8,F("$GRAY")); 

  Panel.send(Display_1, true);
  Panel.send(Display_2, F("$BLACK"));
  Panel.send(Display_3, true);
  Panel.send(Display_4, F("$BLACK"));

  Panel.send(Button_9,F("▲\nspeed")); // V/Div up button
  Panel.send(Button_10,F("speed\n▼")); // V/Div down button
  Panel.send(Button_12,F("▲\nbuffer")); // Time/Div up button
  Panel.send(Button_13,F("buffer\n▼")); // Time/Div down button
  Panel.send(MaxSlider_5, 500); // X-Position (buffer size)
  Panel.send(Slider_5,F("position")); // text
  Panel.send(Slider_5, 0); // half way
  Panel.send(MaxSlider_5,SampleBufSize-(SampleWindow/4)); 
  
  Panel.send(GraphValueCount_1, SampleWindow);
  Panel.send(GraphValue_1, F("$STATIC"));
  Panel.send(GraphValue_1, F("$RED"));
  Panel.send(GraphValueCount_2, SampleWindow);
  Panel.send(GraphValue_2, F("$STATIC"));
  Panel.send(GraphValue_2, F("$PURPLE"));
  Panel.send(GraphValueCount_3, SampleWindow);
  Panel.send(GraphValue_3, F("$STATIC"));
  Panel.send(GraphValue_3, F("$BLUE"));
  Panel.send(GraphValueCount_4, SampleWindow);
  Panel.send(GraphValue_4, F("$STATIC"));
  Panel.send(GraphValue_4 ,F("$GREEN"));

  Panel.send(GraphText, F("$GRAY"));
  Panel.send(GraphText, _Point(218,213));  // _Point(0,197)
  Panel.send(GraphText, "(ms)");

  Panel.send(GraphDrawLine, F("$GRAY"));
  for(int i=1; i<=4; i++)
  {
    Panel.send(GraphDrawLine,_VLine(0,ChanelHeight*i,255,ChanelHeight*i));
  }
  for(int i=0; i<=4; i++)
  {
    Panel.send(GraphDrawLine,_VLine(41+(43*i),ChanelHeight*4+5,41+(43*i),ChanelHeight*4-5));
    Panel.send(GraphDrawLine,_VLine(41+(43*i),ChanelHeight*2+5,41+(43*i),ChanelHeight*2-5));
  }
  
  Panel.send(GraphLabel_1, F(""));
  Panel.send(GraphLabel_1 ,F("$YELLOW"));
  Panel.send(GraphLabel_2, F(""));
  Panel.send(GraphLabel_2 ,F("$ORANGE"));
  Panel.send(GraphLabel_3, F(""));
  Panel.send(GraphLabel_3 ,F("$WHITE"));
  Panel.send(GraphLabel_4, F(""));
  Panel.send(GraphLabel_4, F("$WHITE"));

  Panel.send(GraphButton_1, F("mea\nsure"));
  Panel.send(GraphButton_1, F("$GRAY"));
  Panel.send(GraphButton_4, F("info"));
 
  Panel.send(InfoTitle,F("Logic Analyzer")); // Info title
  Panel.send(InfoText, F("Virtual Panel showcase application")); // Info text
  Panel.send(InfoText, F("Jaap Daniëlse (2IΔ) 2019")); //
  Panel.send(InfoText, F("")); //
  Panel.send(InfoText, F("Signal input on D8, D9, D10, D11 (Mega 50-53)")); //
  Panel.send(InfoText, F("Logic switch (0-1 or 1-0) on approx 2.5V")); //
  Panel.send(InfoText, F("Sample speed 2µs - 10ms/Sample")); //
  Panel.send(InfoText, F("Buffer adjustable from 100 to 2000 (def.) samples.")); //
  Panel.send(InfoText, F("For measurements click 'measure'")); //
  Panel.send(InfoText, F("and use left and right mouse click in graph panel.\n")); //
  Panel.send(InfoText, F("https://github.com/JaapDanielse/VirtualPanel/wiki/Logic-Analyzer-Example")); //

  Panel.send(Graph, true);
  Panel.send(DynamicDisplay,200);

  SetWindowPosition(0);
  SetSpeed(0);
  DrawDivisions();
  StaticDisplay();
}

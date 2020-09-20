// Panel Module

enum TriggerModeList // trigger mode enumerator
{
  Auto,
  Normal,
  Single,
  end
};

static int TriggerMode =  Auto; // will be set to Auto by PanelInit
static bool InfoPanel = false;

//-----------------------------------------------------------------------------------------------
void PanelCallback(vp_channel event) 
{ 
   switch (event) 
  {
    case PanelConnected: InitPanel(); break;

    case Button_4:  AFButtonToggle(); break; // 1X / 10X
    case Button_8:  RunState = !RunState; break; // run / pause
    case Button_9:  SetVDiv(+1); break; // VDiv +
    case Button_10: SetVDiv(-1); break; // VDiv -
    case Button_11: SwitchTriggerMode(); break; // trigger mode: auto trig / normal tig / single event
    case Button_12: SetmsDiv(+1); break; // tDiv +
    case Button_13: SetmsDiv(-1); break; // tDiv -
    case Button_14: TriggerEdgeRizing = !TriggerEdgeRizing; break; // trigger edge rizing/falling
    case Slider_1: SetVertPos(Panel.vpr_int, true); break; // vertical position
    case Slider_4: SetTrigger(Panel.vpr_int); break; // triggel level
    case Slider_5: SetXPos(Panel.vpr_int); break; //horizontal position
    case GraphButton_1: VMeasure = !VMeasure; break; // toggle Volts measurement
    case GraphButton_2: TMeasure = !TMeasure; break; // toggle Time measurement 
    case GraphButton_4: InfoPanel = !InfoPanel; Panel.send(Info,InfoPanel); break; // toggle Time measurement 
    case GraphClick: LeftClickPos = Panel.vpr_uint; break; // catch left click for measurement
    case GraphRightClick: RightClickPos = Panel.vpr_uint; break; // catch right click for measurement
    default: break;
  }
  DisplayStatic();
}


// Control drawing manual measurements
//-----------------------------------------------------------------------------------------------
void DrawMeasure()
{
   if(LeftClickPos != 0 && RightClickPos !=0) // if pos. available.
   {
     DrawVMeasure(true); // Delete previous Voltage measure
     if (VMeasure) DrawVMeasure(false); // draw new Voltage measure
   }

   if(LeftClickPos != 0 && RightClickPos !=0) // if position available
   {
     DrawTMeasure(true); // Delete previous time measure
     if (TMeasure) DrawTMeasure(false); // write new time measure
   }
   
   if(!VMeasure && !TMeasure) // no measure requested?
   {
     LeftClickPos = 0; // clear position
     RightClickPos =0; // clear position
   }
}

// Draw Voltage measurement 
//-----------------------------------------------------------------------------------------------
void DrawVMeasure(bool erase)
{
   static byte LeftX = 0;
   static byte LeftY = 0;
   static byte RightY = 0;
   static float MVolts = 0.0;
   char  outstr1[10];
   
   if (erase)
   { 
     Panel.send(GraphDrawLine,F("$DEL")); // set to delete line 
     Panel.send(GraphText, "$DEL"); // set to delete text
     MVolts = (float)VDiv/(255.0/5.0)*abs(LeftY-RightY); // calc. pre. text
     dtostrf(MVolts,0,2,outstr1); // convert float to string 
   }
   else
   {
     Panel.send(GraphDrawLine,F("$BLUE")); // set to draw in blue
     Panel.send(GraphText, F("$BLUE")); // set to write in blue
     LeftX  = highByte(LeftClickPos); // save positions
     LeftY  = lowByte(LeftClickPos);
     RightY = lowByte(RightClickPos);
     MVolts = (float)VDiv/(220.0/5.0)*abs(LeftY-RightY); // calculate Volts
     dtostrf(MVolts,0,2,outstr1); // convert float to string 
   }
   Panel.send(GraphDrawLine,_Line(LeftX,LeftY,LeftX,RightY)); // draw line from top left- to botom rightclick
   Panel.send(GraphDrawLine,_Line(LeftX-3,LeftY,LeftX+3,LeftY)); // end line top
   Panel.send(GraphDrawLine,_Line(LeftX-3,RightY,LeftX+3,RightY)); // end line botom
   Panel.send(GraphText,_Point(LeftX+5,(LeftY+RightY)/2)); // set text pos.
   Panel.sendf(GraphText, "%s V", outstr1); // output measurement text
}

// Draw Time Measurement
//-----------------------------------------------------------------------------------------------
void DrawTMeasure(bool erase)
{
   static byte LeftX  = 0; // left click x
   static byte RightX = 0; // right click x
   static byte RightY = 0; // right click y
   static float MTime = 0.0;
   static float MFreq = 0.0;
   char  outstr1[10];
   char  outstr2[10];
   
   if (erase)
   { 
     Panel.send(GraphDrawLine,F("$DEL")); // set delete lines
     Panel.send(GraphText, F("$DEL")); // set delete text
     MTime = (float)msDiv/(263.0/6.0)*(RightX-LeftX); // calc prev. time
     MFreq = (1.0/MTime)*1000.0; // calc prev. freq.
     dtostrf(MTime,0,1,outstr1); // convert float to string 
     dtostrf(MFreq,0,1,outstr2); // convert float to string 
   }
   else
   {
     Panel.send(GraphDrawLine,F("$BLUE")); // write in blue
     Panel.send(GraphText, F("$BLUE")); // draw in blue
     LeftX  = highByte(LeftClickPos); // save position 
     RightX = highByte(RightClickPos);
     RightY = lowByte(RightClickPos);
     MTime = (float)msDiv/(263.0/6.0)*(RightX-LeftX); // calculate time
     MFreq = (1.0/MTime)*1000.0; // calculate frequency
     dtostrf(MTime,0,2,outstr1); // convert Time float to string 
     dtostrf(MFreq,0,1,outstr2); // convert Frequency float to string 
   }
   Panel.send(GraphDrawLine,_Line(LeftX,RightY,RightX,RightY)); // draw line from left to right on right click level
   Panel.send(GraphDrawLine,_Line(LeftX,RightY-3,LeftX,RightY+3)); // end line left
   Panel.send(GraphDrawLine,_Line(RightX,RightY-3,RightX,RightY+3)); // end line right
   Panel.send(GraphText,_Point(LeftX+10,RightY-5)); // set text position
   Panel.sendf(GraphText, "T=%s ms f=%s Hz", outstr1, outstr2); // output measurement text
}

// Atenuator toggle button (1x or 10x)
//-----------------------------------------------------------------------------------------------
void AFButtonToggle()
{ 
  static byte  AFButtonState = 0; //Attenuator and AC filter button state

  AFButtonState++;
  if ( AFButtonState  > ((AttenuatorMultiplier!=1)*2) + (ACFilter*2)) AFButtonState = 0; // reset when past last choice (0-4)
  if ( AFButtonState == 0 && (AttenuatorMultiplier != 1 or ACFilter)) AFButtonState = 1; // if any hardware reset status = 1 
  if ( AFButtonState == 2 && AttenuatorMultiplier == 1) AFButtonState = 3; // if only AC filter

  switch (AFButtonState) 
  {
    case 0: // no extra hardware 
      AttenuatorValue = 1.0; // set multiplier to 1x
      VDecimalCount = 2; // set to display 2 decimals
      ACSelect = false;
      Panel.send(Button_4, false); // remove button
      Panel.send(Led_2, false); // no led
      break; 

    case 1: // DC X1
      AttenuatorValue = 1.0; // set multiplier to 1x
      VDecimalCount = 2; // set to display 2 decimals
      ACSelect = false; // set DC selected
      Panel.sendf(Button_4, "DC\n1X", AttenuatorMultiplier); // set buttont text to show choice
      Panel.send(Led_2, "$ORANGE"); // indicate on led
      break; 

    case 2: // DC Xs  
      AttenuatorValue = (float)AttenuatorMultiplier; // set multiplier to 10x
      if (AttenuatorMultiplier < 10)
        VDecimalCount = 2; // set to display 2 decimals 
      else
        VDecimalCount = 1; // set to display 1 decimal 
      ACSelect = false; // set DC selected
      Panel.sendf(Button_4, "DC\n%dX", AttenuatorMultiplier); // set buttont text to show choice
      Panel.send(Led_2, "$ORANGE"); // indicate on led
      break; 

    case 3:   
      AttenuatorValue = 1.0; // set multiplier to 1x
      VDecimalCount = 2; // set to display 2 decimals 
      ACSelect = true; // set AC selected
      Panel.sendf(Button_4, "AC\n1X", AttenuatorMultiplier); // set buttont text to show choice
      Panel.send(Led_2, "$YELLOW"); // indicate on led
      break; // AC X1

    case 4:   
      AttenuatorValue = (float)AttenuatorMultiplier; // set multiplier to 10x
      if (AttenuatorMultiplier < 10)
        VDecimalCount = 2; // set to display 2 decimals 
      else
        VDecimalCount = 1; // set to display 1 decimal 
      ACSelect = true; // set AC selected
      Panel.sendf(Button_4, "AC\n%dX", AttenuatorMultiplier); // set buttont text to show choice
      Panel.send(Led_2, "$YELLOW"); // indicate on led
      break; // AC Xs
  }
}


// Time per Division change (up and down)
//-----------------------------------------------------------------------------------------------
void SetmsDiv(int msDivChange)
{
  msDivSelIdx += msDivChange; // handle input (+1 or -1)
  if(msDivSelIdx > msDivSelCount-1) msDivSelIdx = msDivSelCount-1; // top limit
  if(msDivSelIdx < 0 ) msDivSelIdx = 0; //botom limit
  msDiv = msDivSelect[msDivSelIdx]; //set selected msDiv value

  MaxSampleValues = SampleValuesSize - (msDivSelIdx * 35); // max buf (idx=0) 500  min buf (idx=10) 150 (const 35)
  Panel.send(MaxSlider_5, MaxSampleValues); // X-Position (buffer size)
  Panel.send(Slider_5, "x-pos"); // text
  Panel.send(Slider_5, MaxSampleValues/2); // half way
  triggershift = 0; // reset triggershift
  SetXPos(triggershift + (MaxSampleValues/2)); // display change in x-position value
}


// Volts per Division change (up and down)
//-----------------------------------------------------------------------------------------------
void SetVDiv(int VDivChange)
{
  VDivSelIdx += VDivChange; // handle input (+1 or -1)
  if(VDivSelIdx > VDivSelCount-1) VDivSelIdx = VDivSelCount-1; // top limit
  if(VDivSelIdx < 0 ) VDivSelIdx = 0; // bottom limit
  VDiv = VDivSelect[VDivSelIdx]; // set the selected VDiv value
  DrawTrigger();
  Panel.send(Slider_4, TriggerLine); // set the trigger Slider to the corresponding position
  // trigger line is drawn by StaticDisplay
}


// Triggelevel change (Slider)
//-----------------------------------------------------------------------------------------------
void SetTrigger(int NewTriggerLevel)
{
  TriggerLevel = ((float)(NewTriggerLevel - (vpos + (ACSelect*128))) * ((VDiv * (float)GridSize) / 255.0)) + (ACSelect * 2.5); // calculate new level
  // trigger line is drawn by StaticDisplay
}


// Display triggerline from SetTrigger, Set vert an 
//-----------------------------------------------------------------------------------------------
void DrawTrigger()
{
  Panel.send(GraphDrawLine,"$DEL"); 
  Panel.send(GraphDrawLine,_VLine(0,TriggerLine,255,TriggerLine));  
  TriggerLine = ((TriggerLevel-(ACSelect*2.5)) * (255.0 / (VDiv * (float)GridSize))) + vpos+(ACSelect*128);
  TriggerLine = constrain(TriggerLine, 0 ,255);
  Panel.send(GraphDrawLine,"$RED");
  Panel.send(GraphDrawLine,_VLine(0,TriggerLine,255,TriggerLine));
}


// Y-Position change (Slider)
//-----------------------------------------------------------------------------------------------
void SetVertPos(int NewVertPos, bool Set)
{
  static int OldYPos = 0; // remember so we can remove the previous line
  static unsigned long PosLineDeleteTimer = 0; // timer to delay removal

  if( Set || (!Set && PosLineDeleteTimer <= millis())) // when set or timeout, remove
  {
    Panel.send(GraphDrawLine,"$DEL"); // set to delete
    Panel.send(GraphDrawLine,_VLine(0,OldYPos,255,OldYPos)); // delete line
    PosLineDeleteTimer = 4294967295; // max value
    DrawTrigger();
  }
  
  if(Set) // is set write line
  {
    vpos = NewVertPos-255; // calculate position
    OldYPos = constrain(vpos + (ACSelect*128), 0, 255); // store for removal
    Panel.send(GraphDrawLine,"$ORANGE"); // same color as the wave 
    Panel.send(GraphDrawLine,_VLine(0,OldYPos,255,OldYPos)); // draw line
    Panel.send(Slider_4, TriggerLine); // and the trigger Slider 
    PosLineDeleteTimer = millis() + 500; // half a second from now
    // trigger line is drawn by StaticDisplay
  }
}


// Trigger rizing edge / falling edge toggle
//-----------------------------------------------------------------------------------------------
void SwitchTriggerMode()
{
  TriggerMode = (TriggerModeList)(TriggerMode+1); // Next mode
  if (TriggerMode == end) TriggerMode = Auto; 

  if (TriggerMode == Auto) { Panel.send(Button_11, "auto\ntrig"); Panel.send(Led_7, "$BLUE");}
  if (TriggerMode == Normal) { Panel.send(Button_11, "normal\ntrig"); Panel.send(Led_7, "$ORANGE");}
  if (TriggerMode == Single) { Panel.send(Button_11, "single\nevent"); Panel.send(Led_7, "$YELLOW");}
}


//-----------------------------------------------------------------------------------------------
void SetXPos(int newXpos)
{
  char outstr1[10];  
  char outstr2[10];
  char Sign[3]="+";
  char Unit[4]="";

  triggershift = newXpos-(MaxSampleValues/2);
  
  float mSXPos = (float)triggershift * 50.0 * msDiv;
  
  if (mSXPos > 999999.0 || mSXPos < -999999.0)
  { mSXPos  = mSXPos / 1000000.0; strcpy(Unit,"s");}
  else if (mSXPos > 999.0 || mSXPos < -999.0)
  { mSXPos  = mSXPos / 1000.0; strcpy(Unit,"ms"); }
  else
  { strcpy(Unit,"µs"); }

  if (mSXPos < 0.001) strcpy(Sign,"");
  dtostrf(mSXPos,0,1,outstr1);
  Panel.sendf(Display_4,"%s%s %s", Sign, outstr1, Unit);

  // calculate trigger value to float
  dtostrf((TriggerLevel-(ACSelect*VCCValue/2.0))* AttenuatorValue,0,1,outstr2); 
  Panel.sendf(GraphLabel_5,"Trig %s V Pos %s%s %s", outstr2, Sign, outstr1, Unit);
}


// handle static display changes
//-----------------------------------------------------------------------------------------------
void DisplayStatic()
{
  char outstr[10];
 
  // handle run state ( can be change from two sources)   
  if (RunState)
  { // when running
    Panel.send(Button_8, "run"); 
    Panel.send(Led_6, "$GREEN");
  }
  else
  { //when pauzing
    Panel.send(Button_8, "pause"); 
    Panel.send(Led_6, "$OFF");
  }
  
  // calculate trigger value to float
  dtostrf((TriggerLevel-(ACSelect*VCCValue/2.0))* AttenuatorValue,0,VDecimalCount-1,outstr); 
 
  if (TriggerEdgeRizing)
  { // when rizing
    Panel.send(Button_14, "△\ntrig"); 
    Panel.sendf(Display_2,"trig △ %sV", outstr); 
    Panel.send(Led_8, "$BLUE"); 
  }
  else
  { // when falling
    Panel.send(Button_14, "trig\n▽");
    Panel.sendf(Display_2,"trig ▽ %sV", outstr); 
    Panel.send(Led_8, "$ORANGE"); 
  }
  
  // Output to displays an caption
  if(msDiv>=1000)
    Panel.sendf(Display_1,"%d s/div", msDiv/1000); // output Time / div
  else
    Panel.sendf(Display_1,"%d ms/div", msDiv); // output Time / div

  dtostrf(VDiv * AttenuatorValue,0,VDecimalCount-1,outstr);  // calculate VDiv to float
  Panel.sendf(Display_3,"%s V/div", outstr); // output VDiv

  Panel.send(GraphText,F("$WHITE"));
  Panel.sendf(GraphCaption_2,"%d ms/div - %s V/div", (int)(msDiv), outstr); // to Caption too.
  SetXPos(triggershift + (MaxSampleValues/2)); // recalculate horizontal pos and display 
  DrawTrigger(); // draw trigger line

  if (VMeasure) 
    Panel.send(GraphButton_1,"$BLACK"); 
  else 
    Panel.send(GraphButton_1,"$GRAY");

  if (TMeasure) 
    Panel.send(GraphButton_2,"$BLACK"); 
  else 
    Panel.send(GraphButton_2,"$GRAY");
  
  DrawMeasure();
}

// Initialize panel
//-----------------------------------------------------------------------------------------------
void InitPanel()
{
    Panel.send(ApplicationName,"Oscilloscope"); // set the application name
    //Panel.send(PanelColor, "$BLUE"); // set panel bar blue
    
    Panel.send(Display_1,"$WHITE"); // time division in white
    Panel.send(Display_2,"$BLACK"); // Trigger in black
    Panel.send(Display_3,"$WHITE"); // volts div. in white
    Panel.send(Display_4,"$BLACK"); // x-pos in balck
    
    Panel.send(GraphGrid,GridSize); // set gridsize
    Panel.send(GraphValueCount_1, GraphValues); // set value count
    Panel.send(GraphValue_1,"$STATIC"); // define static graph
    Panel.send(GraphValue_1,"$ORANGE"); // orange line
    
    Panel.send(GraphLabel_1,"$ORANGE"); // measured value in orange (Vmin - Vmax)
    Panel.send(GraphLabel_2,"$ORANGE"); // Measured Value in orange (Vpp)
    Panel.send(GraphLabel_3,"$YELLOW"); // calculated value in yellow (Period)
    Panel.send(GraphLabel_4,"$YELLOW"); // calculated value in yellow (Frequency)
    Panel.send(GraphLabel_5,"$RED");
    
    Panel.send(GraphButton_1,"meas.\nvolts"); // button text Voltage measurement
    Panel.send(GraphButton_1,"$GRAY"); // use color to show inactive
    Panel.send(GraphButton_2,"meas.\ntime"); // button text Time Measurement
    Panel.send(GraphButton_2,"$GRAY"); // use color to show inactive
 
    Panel.send(GraphButton_4,"info"); // use color to show inactive

    Panel.send(Graph,true); // open graph window 
    AFButtonToggle(); // init Attenuator AC Filter button (4)
    Panel.send(Button_9, "▲\nV/div"); // V/Div up button
    Panel.send(Button_10, "V/div\n▼"); // V/Div down button
    Panel.send(Button_12, "▲\nt/div"); // Time/Div up button
    Panel.send(Button_13, "t/div\n▼"); // Time/Div down button
   
    Panel.send(MaxSlider_1, 512); // Y-Pos Slider (max 512)
    Panel.send(Slider_1, "y-pos"); // text
    Panel.send(Slider_1, vpos+255); // initial value
    
    Panel.send(MaxSlider_4, 255); // Trigger level
    Panel.send(Slider_4, "trig lev"); //text
    Panel.send(Slider_4, TriggerLine); // initial value

    SetmsDiv(0);
    
    if( --TriggerMode < 0) TriggerMode = end-1; // prevent togle on reset
    SwitchTriggerMode();
 
    Panel.send(InfoTitle,F("Oscilloscope")); // Info title
    Panel.send(InfoText, F("Virtual Panel showcase application - Jan & Jaap Daniëlse (2IΔ) 2019\n")); // Info text
    Panel.send(InfoText, F("Signal input on A0")); //
    Panel.send(InfoText, F("Maximum direct input level 5V")); //
    Panel.send(InfoText, F("Sample speed 20.000 Samples/S")); //
    Panel.send(InfoText, F("Maximum frequency (appox.) 8KHz")); //
    Panel.send(InfoText, F("For measurements use left and right mouse click in graph panel.\n")); //
    Panel.send(InfoText, F("Documentation:")); //
    Panel.send(InfoText, F("https://github.com/JaapDanielse/VirtualPanel/wiki/Oscilloscope-Example")); //

}

// end module

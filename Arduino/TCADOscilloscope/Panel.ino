// Panel Module

//-----------------------------------------------------------------------------------------------
void PanelCallback(int event, int type) 
{ 
   switch (event) 
  {
    case PanelConnected: { PanelInit(); break; }
    case Button_4: { if (--triggershift <= -TriggerStart) triggershift++; break; }
    case Button_5: { if (++triggershift >= TriggerStart) triggershift--; break; }
    case ScrollBar_1:
    {
      Panel.Send(GraphPen,"$DEL");
      Panel.Send(GraphDrawLine,_Line(0,trig,255,trig));
      trig = Panel.vpr_int;
      Panel.Send(GraphPen,"$RED");
      Panel.Send(GraphDrawLine,_Line(0,trig,255,trig));
      DisplayStatic();
      break;
    }
    case ScrollBar_2: { usDivSelIdx = Panel.vpr_int; SetTimeBase(usDivSelIdx+1); DisplayStatic(); break; }
    case ScrollBar_3: { vdiv = (float)(Panel.vpr_int+1)/10.0; DisplayStatic(); break; }
    case ScrollBar_4: { vpos = Panel.vpr_int-255; DisplayStatic(); break; }
    case StaticDisplay: { DisplayStatic(); break; }
  }
}

//-----------------------------------------------------------------------------------------------
void DisplayStatic()
{
  char outstr[10];

  dtostrf(vdiv,0,1,outstr);
  Panel.Sendf(Display_1,"%s V/div", outstr);

  if (usDivSelect[usDivSelIdx]>=1000000)
  {
    Panel.Sendf(GraphCaption_2,"%d s/div - %s V/div", (int)(usDivSelect[usDivSelIdx]/(long)1000000), outstr);
    Panel.Sendf(Display_2,"%d s/div", (int)(usDivSelect[usDivSelIdx]/(long)1000000));
  }
  else if (usDivSelect[usDivSelIdx]>=1000)
  {
    Panel.Sendf(GraphCaption_2,"%d ms/div - %s V/div", (int)(usDivSelect[usDivSelIdx]/(long)1000), outstr);
    Panel.Sendf(Display_2,"%d ms/div", (int)(usDivSelect[usDivSelIdx]/(long)1000));
  }
  else
  {
    Panel.Sendf(GraphCaption_2,"%d us/div - %s V/div", (int)(usDivSelect[usDivSelIdx]), outstr);
    Panel.Sendf(Display_2,"%d us/div", (int)(usDivSelect[usDivSelIdx]));
  }
  float TriggerVolt = (float)(map(trig,0,220,0,255)-vpos)/51.0;
  dtostrf(TriggerVolt,0,1,outstr);
  Panel.Sendf(Display_3,"trig %s V", outstr);
  Panel.Sendf(Display_4,"sh %d ms", triggershift);
  Panel.Sendf(GraphLabel_5,"Trigger: %s V  Shift: %d ms", outstr, triggershift);
}

//-----------------------------------------------------------------------------------------------
void PanelInit()
{
    Panel.Send(ApplicationName,"Oscilloscope"); // set the application name

    Panel.Send(InfoLabel, F("Oscilloscope"));
    Panel.Send(InfoText, F("Jan en Jaap Danielse"));
    Panel.Send(InfoText, F("A0 is input signal"));

    Panel.Send(Display_3,"$BLACK");
    Panel.Send(Display_4,"$BLACK");
    
    Panel.Send(GraphGrid,5);
    Panel.Send(GraphValueCount_1, MaxGraphValues);
    Panel.Send(GraphValue_1,"$STATIC");
    Panel.Send(GraphValue_1,"$ORANGE");
    Panel.Send(GraphLabel_1,"$YELLOW");
    Panel.Send(GraphLabel_2,"$ORANGE");
    Panel.Send(GraphLabel_3,"$ORANGE");
    Panel.Send(GraphLabel_4,"$ORANGE");
    Panel.Send(GraphLabel_5,"$RED");
    Panel.Send(GraphPen,"$RED");
    Panel.Send(GraphDrawLine,_Line(0,trig,255,trig));
    Panel.Send(Graph,true); 

    Panel.Send(Button_4, "$LEFT");
    Panel.Send(Button_5, "$RIGHT");
 
    Panel.Send(MaxScrollBar_1, 220);
    Panel.Send(ScrollBar_1, "trig");
    Panel.Send(ScrollBar_1, trig);
    
    Panel.Send(MaxScrollBar_2,15);
    Panel.Send(ScrollBar_2,"time");
    Panel.Send(ScrollBar_2,usDivSelIdx);

    Panel.Send(MaxScrollBar_3,99);
    Panel.Send(ScrollBar_3,"v/div");
    Panel.Send(ScrollBar_3,(int)vdiv*10);
    
    Panel.Send(MaxScrollBar_4,512);
    Panel.Send(ScrollBar_4,"vpos");
    Panel.Send(ScrollBar_4,vpos+255);
    
    Panel.Send(StaticDisplay,true); 
    DisplayStatic();     
}

// end module

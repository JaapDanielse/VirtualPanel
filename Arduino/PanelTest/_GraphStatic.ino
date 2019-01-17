
int vpos = 128;
float vdiv = 30.0;
float sincount =  6.0;
int SampleCount = 90;
int trig = 110;
bool freq = false;
float tsincount;

void StaticCallback(int event, int type)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
     // initialize panel layout
      Panel.Send(ApplicationName,"PanelTest - StaticGraph"); // set the application name
      Panel.Send(DynamicDisplay,500);     // enable dynamic display request
      Panel.Send(Button_4, F("next"));
      Panel.Send(Button_5, F("graph"));
      Panel.Send(Button_6, F("mon"));
      Panel.Send(Button_7, F("frq\ndrft"));
      Panel.Send(GraphGrid, 6);
      Panel.Send(GraphButton_1, F("GrBttn 1"));
      Panel.Send(GraphButton_2, F("GrBttn 2"));
      Panel.Send(GraphButton_3, F("GrBttn 3"));
      Panel.Send(GraphButton_4, F("GrBttn 4"));
      Panel.Send(GraphCaption_1, F("Simulated Oscilloscope"));
      Panel.Send(GraphLabel_1, F("$ORANGE"));
      Panel.Send(GraphLabel_1, "GraphLabel_1");
      Panel.Send(GraphValueCount_1,SampleCount);
      Panel.Send(GraphValue_1,F("$STATIC"));
      Panel.Send(GraphValue_1,F("$ORANGE"));
      Panel.Send(ScrollBar_1, "trig");
      Panel.Send(ScrollBar_1, trig);
      Panel.Send(MaxScrollBar_1, 220);
      Panel.Send(ScrollBar_2, F("v-pos"));
      Panel.Send(ScrollBar_2, vpos);
      Panel.Send(MaxScrollBar_2, 255);
      Panel.Send(ScrollBar_3, F("v/div"));
      Panel.Send(ScrollBar_3, (int)vdiv);
      Panel.Send(MaxScrollBar_3, 150);
      Panel.Send(ScrollBar_4, F("s/div"));
      Panel.Send(ScrollBar_4, (int)tsincount*10);
      Panel.Send(MaxScrollBar_4, 150);
      Panel.Send(GraphPen,F("$RED"));
      Panel.Send(GraphDrawLine,_Line(0,trig,255,trig));
      Panel.Send(Graph,true); 

      break; 
    }

    case Button_4:
    {
      PanelMode = Click;
      Panel.Send(Reset);
      break;
    }

    case Button_5:
    {
      Graphmode = !Graphmode;
      Panel.Send(Graph,Graphmode);
      break;
    }

    case Button_6:
    {
      Monmode = !Monmode;
      Panel.Send(Monitor,Monmode);
      break;
    }

    case Button_7:
    {
      freq = !freq;
      Panel.Send(Led_5,freq);
      sincount = 6.0;
      break;
    }

    case ScrollBar_1:
    {
      Panel.Send(GraphPen,F("$DEL"));
      Panel.Send(GraphDrawLine,_Line(0,trig,255,trig));
      trig = Panel.vpr_int;
      Panel.Send(GraphPen,F("$RED"));
      Panel.Send(GraphDrawLine,_Line(0,trig,255,trig));

      break;
    }

    case ScrollBar_2:
    {
      vpos = Panel.vpr_int;
      break;
    }

    case ScrollBar_3:
    {
      vdiv = Panel.vpr_int;
      break;
    }

    case ScrollBar_4:
    {
      sincount = (float)Panel.vpr_int/10.0;
      break;
    }


    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      Panel.Sendf(Display_1,F("%d V/div"),(int)vdiv);  
      Panel.Sendf(Display_2,F("%6d mS/div"),sincount);  
      Panel.Sendf(Display_3,F("vp: %d"),vpos);  
      Panel.Sendf(GraphLabel_1,F("%d Hz"),(int)(tsincount*10.0));  
      Sinus();
      break;
    }
    
    default:
      break;
  }
}


void Sinus()
{
   float angle = 0.0;
   byte graphvalue = 0;

   if(!freq)
   {
     tsincount = sincount +((float)random(0,5)/10.0);
   }
   else
     tsincount = sincount++;
    
   for(int j=0; j<SampleCount; j++)
   {
     angle += 360.0/((float)SampleCount/tsincount);
     float RadAngle = (float)(PI/180.0) * angle;
     graphvalue = (byte) constrain((vdiv * sin(RadAngle) + vpos),0,255);
     Panel.Send(GraphValue_1,graphvalue);  
   }

}



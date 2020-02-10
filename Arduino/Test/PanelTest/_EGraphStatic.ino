
int vpos = 128;
float vdiv = 50.0;
float sincount =  6.0;
int SampleCount = 90;
int trig = 110;
bool freq = false;
float tsincount;

void StaticCallback(vp_channel event)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
     // initialize panel layout
      Panel.send(ApplicationName,"PanelTest - StaticGraph"); // set the application name
      Panel.send(DynamicDisplay,500);     // enable dynamic display request

      Panel.send(Button_4,  F("next\npanel"));
      Panel.send(Button_5,  F("info"));
      Panel.send(Button_6,  F("moni\ntor"));
      Panel.send(Button_7,  F("graph"));
      Panel.send(Button_4,  F("next\npanel"));
      Panel.send(Button_5,  F("info"));
      Panel.send(Button_6,  F("moni\ntor"));
      Panel.send(Button_7,  F("graph"));
      Panel.send(GraphValueCount_1,SampleCount);
      Panel.send(GraphValue_1,F("$STATIC"));
      Panel.send(GraphValue_1,F("$BLUE"));
      Panel.send(GraphValueCount_2,SampleCount);
      Panel.send(GraphValue_2,F("$STATIC"));
      Panel.send(GraphValue_2,F("$PURPLE"));
      Panel.send(Slider_3, F("ampl."));
      Panel.send(MaxSlider_3, 150);
      Panel.send(Slider_3, (int)vdiv);
      Panel.send(MaxSlider_4, 150);
      Panel.send(Slider_4, F("freq."));
      Panel.send(Slider_4, (int)sincount*10);
      WriteInfo();
      Graphmode = true;
      Panel.send(Graph,Graphmode); 
      break; 
    }

    case Button_4:
      if( ++PanelMode == Endmode ) PanelMode = 0;
      Panel.send(Reset);
      break;

    case Button_5:
      Infomode = !Infomode;
      Panel.send(Info,Infomode);
      break;

    case Button_6:
      Monmode = !Monmode;
      Panel.send(Monitor,Monmode);
      break;

    case Button_7:
    {
      Graphmode = !Graphmode;
      Panel.send(Graph,Graphmode);
      break;
    }


    case Button_8:
    {
      freq = !freq;
      Panel.send(Led_5,freq);
      sincount = 6.0;
      break;
    }

    case Slider_1:
    {
      Panel.send(GraphDrawLine,F("$DEL"));
      Panel.send(GraphDrawLine,_Line(0,trig,255,trig));
      trig = Panel.vpr_int;
      Panel.send(GraphDrawLine,F("$RED"));
      Panel.send(GraphDrawLine,_Line(0,trig,255,trig));

      break;
    }

    case Slider_2:
    {
      vpos = Panel.vpr_int;
      break;
    }

    case Slider_3:
    {
      vdiv = Panel.vpr_int;
      break;
    }

    case Slider_4:
    {
      sincount = (float)Panel.vpr_int/10.0;
      break;
    }


    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      Panel.sendf(Display_1,F("amp. %d"),(int)vdiv);  
      Panel.sendf(Display_2,F("freq. %d"),(int)sincount);  
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

   for(int j=0; j<SampleCount; j++)
   {
     angle += 360.0/((float)SampleCount/sincount);
     float RadAngle = (float)(PI/180.0) * angle;
     graphvalue = (byte) constrain((vdiv * sin(RadAngle) + vpos),0,255);
     Panel.send(GraphValue_1,graphvalue);  
   }
}

void Cosinus()
{
   float angle = 0.0;
   byte graphvalue = 0;

   for(int j=0; j<SampleCount; j++)
   {
     angle += 360.0/((float)SampleCount/sincount);
     float RadAngle = (float)(PI/180.0) * angle;
     graphvalue = (byte) constrain((vdiv * cos(RadAngle) + vpos),0,255);
     Panel.send(GraphValue_2,graphvalue);  
   }
}

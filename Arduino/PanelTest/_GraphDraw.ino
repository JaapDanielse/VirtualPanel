
boolean Direction = true;
int Angle = 0;
int Distance = 120;

void DrawCallback(int event, int type) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
      Panel.Send(ApplicationName,"PanelTest - Draw"); // set the application name

      Panel.Send(Button_4,  "next");
      Panel.Send(Button_5,  "graph");
      Panel.Send(Button_6,  "mon");

      Panel.Send(GraphText, Point(5,210));
      Panel.Send(GraphText, "Simulated distance sensor sweep");
      Panel.Send(DynamicDisplay,100); 
      Panel.Send(Graph,true); 
      
      DrawCircles();    
      break;
    }

    case Button_4:
    {
      PanelMode = Roling;
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
    

    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      if (Direction) Angle+=2; else Angle-=2;
      if (Angle <= 0 || Angle >= 180) Direction = !Direction; 
      Angle = constrain( Angle, 0, 180);
      Swipe(Angle, Distance);
      break;
    }

  }

}

void DrawCircles()
{

   int Dist = 110;

   Panel.Send(GraphPen,"$ORANGE");
   Panel.Send(GraphPen,"$1PX");
   Panel.Send(GraphDrawLine); // new line
   for(int Angle=0 ; Angle <= 180 ; Angle+=2)
   {
     float RadAngle = (float)(PI/180.0) * Angle;
     byte x = 5 + (Dist * cos(RadAngle) + 127);
     byte y = (Dist * sin(RadAngle) + 30) ;
     Panel.Send(GraphDrawLine,Point(x,y));
   }

   Dist = 55;
   
   Panel.Send(GraphPen,"$1PX");
   Panel.Send(GraphDrawLine); // new line
   for(int Angle=0 ; Angle <= 180 ; Angle+=2)
   {
     float RadAngle = (float)(PI/180.0) * Angle;
     byte x = 5 + (Dist * cos(RadAngle) + 127);
     byte y = (Dist * sin(RadAngle) + 30) ;
     Panel.Send(GraphDrawLine,Point(x,y));
   }

   Panel.Send(GraphPen,"$1PX");
   Panel.Send(GraphCaption_2,"0 deg                                          180 deg");
   Panel.Send(GraphDrawPixel,Point(200,200));

}


void Swipe(int Angle, int Distance)
{
   #define MinDist 10//
   #define OldSize 50//

   static int OldAngle=0;
   static int OldIdx=0;
   static byte xsOld[OldSize];
   static byte ysOld[OldSize];
   static byte xeOld[OldSize];
   static byte yeOld[OldSize];

   OldIdx++; 
   if (OldIdx == OldSize) OldIdx = 0;

   int TmpIdx = OldIdx-1;
   if (TmpIdx < 0) TmpIdx = OldSize + TmpIdx;

   int TmpIdx2 = OldIdx-4;
   if (TmpIdx2 < 0) TmpIdx2 = OldSize + TmpIdx2;
   
   Panel.Send(GraphPen,"$DEL");
   Panel.Send(GraphDrawLine,Line(xsOld[OldIdx],ysOld[OldIdx],xeOld[OldIdx],yeOld[OldIdx]));
   
   Panel.Send(GraphPen,"$BLUE");
   Panel.Send(GraphDrawLine,Line(xsOld[TmpIdx2],ysOld[TmpIdx2],xeOld[TmpIdx2],yeOld[TmpIdx2]));

   Panel.Send(GraphPen,"$GREEN");
   Panel.Send(GraphDrawLine,Line(xsOld[TmpIdx],ysOld[TmpIdx],xeOld[TmpIdx],yeOld[TmpIdx]));

   float RadAngle = (float)(PI/180.0) * Angle;

   byte xs = 5 + (MinDist * cos(RadAngle) + 127);
   byte ys = (MinDist * sin(RadAngle) + 30);
   byte xe = 5 + (Distance * cos(RadAngle) + 127);
   byte ye = (Distance * sin(RadAngle) + 30) ;

   OldAngle = Angle;
   
   Panel.Send(GraphPen,"$YELLOW");
   Panel.Send(GraphDrawLine,Line(xs,ys,xe,ye));
   xsOld[OldIdx] = xs;
   ysOld[OldIdx] = ys;
   xeOld[OldIdx] = xe;
   yeOld[OldIdx] = ye;

   Panel.Sendf(GraphLabel_1, "Angle %d", 180-Angle);
   
}

unsigned long Line( byte xs, byte ys, byte xe, byte ye)
{
  unsigned long linepoints;

  linepoints = ye;
  linepoints += (unsigned long)xe << 8 ;
  linepoints += (unsigned long)ys << 16 ;
  linepoints += (unsigned long)xs << 24 ;
  
  return(linepoints);
}

unsigned int Point( byte x, byte y)
{
  unsigned int point;

  point = y;
  point += (unsigned long)x << 8 ;
  
  return(point);
}


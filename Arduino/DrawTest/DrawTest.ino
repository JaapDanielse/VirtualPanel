
#include "PanelOne.h"

boolean Direction = true;
int Angle = 0;
int Distance = 120;

void setup() 
{
  Panel.Init(); // init port and protocol
}

void loop() 
{
  Panel.Receive(); // handle panel data coming in
  delay(50);
}



void PanelCallback(int event, int type) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
      Panel.Send(ApplicationName,"Panel Test"); // set the application name
      Panel.Send(GraphText, Point(10,10));
      Panel.Send(GraphText, "Time of flight sensor sweep");
      Panel.Send(DynamicDisplay,100);     
      break;
    }

    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      if (Direction) Angle+=5; else Angle-=5;
      if (Angle <= 0 || Angle >= 180) Direction = !Direction; 
      Angle = constrain( Angle, 0, 180);
      Swipe(Angle, Distance);
      break;
    }

  }

}


void Swipe(int Angle, int Distance)
{
   #define MinDist 10//
   #define OldSize 10//

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
   
   Panel.Send(GraphDraw,"$BLUE");
   Panel.Send(GraphDraw,Line(xsOld[TmpIdx2],ysOld[TmpIdx2],xeOld[TmpIdx2],yeOld[TmpIdx2]));

   Panel.Send(GraphDraw,"$GREEN");
   Panel.Send(GraphDraw,Line(xsOld[TmpIdx],ysOld[TmpIdx],xeOld[TmpIdx],yeOld[TmpIdx]));

   Panel.Send(GraphDraw,"$BLACK");
   Panel.Send(GraphDraw,Line(xsOld[OldIdx],ysOld[OldIdx],xeOld[OldIdx],yeOld[OldIdx]));

   float RadAngle = (float)(PI/180.0) * Angle;

   byte xs = 5 + (MinDist * cos(RadAngle) + 120);
   byte ys = 210-(MinDist * sin(RadAngle) + 20);
   byte xe = 5 + (Distance * cos(RadAngle) + 120);
   byte ye = 210-(Distance * sin(RadAngle) + 20) ;

   OldAngle = Angle;
   
   Panel.Send(GraphDraw,"$YELLOW");
   Panel.Send(GraphDraw,Line(xs,ys,xe,ye));
   xsOld[OldIdx] = xs;
   ysOld[OldIdx] = ys;
   xeOld[OldIdx] = xe;
   yeOld[OldIdx] = ye;

   Panel.Sendf(GraphLabel_1, "Angle %d", Angle);
   
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


// VirtualPanel J-Draw example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"


bool Direction = true;
int16_t Angle = 0;
int16_t Distance = 120;

void setup() 
{
  Panel.begin(); // init port and protocol
}

void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
}

void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
      Panel.send(ApplicationName,"Draw"); // set the application name
      Panel.send(GraphText, _Point(5,210));
      Panel.send(GraphText, "Simulated distance sensor sweep");
      Panel.send(DynamicDisplay, (int16_t)100); 
      Panel.send(Graph, (bool)true); 
      
      DrawCircles();    
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

   int16_t Dist = 110;

   Panel.send(GraphDrawLine, "$ORANGE");
   Panel.send(GraphDrawLine, "$2PX");
   Panel.send(GraphDrawLine); // new line
   for(int Angle=0 ; Angle <= 180 ; Angle+=2)
   {
     float RadAngle = (float)(PI/180.0) * Angle;
     byte x = 5 + (Dist * cos(RadAngle) + 127);
     byte y = (Dist * sin(RadAngle) + 30) ;
     Panel.send(GraphDrawLine,_Point(x,y));
   }

   Dist = 55;
   
   Panel.send(GraphDrawLine, "$1PX");
   Panel.send(GraphDrawLine); // new line
   for(int Angle=0 ; Angle <= 180 ; Angle+=2)
   {
     float RadAngle = (float)(PI/180.0) * Angle;
     byte x = 5 + (Dist * cos(RadAngle) + 127);
     byte y = (Dist * sin(RadAngle) + 30) ;
     Panel.send(GraphDrawLine,_Point(x,y));
   }

   Panel.send(GraphDrawLine,"$1PX");
   Panel.send(GraphCaption_2,"0 deg                                          180 deg");
   Panel.send(GraphDrawPixel,_Point(200,200));

}


void Swipe(int Angle, int Distance)
{
   #define MinDist 10//
   #define OldSize 50//

   static int16_t OldAngle=0;
   static int16_t OldIdx=0;
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
   
   Panel.send(GraphDrawLine, "$DEL");
   Panel.send(GraphDrawLine,_Line(xsOld[OldIdx],ysOld[OldIdx],xeOld[OldIdx],yeOld[OldIdx]));
   
   Panel.send(GraphDrawLine, "$BLUE");
   Panel.send(GraphDrawLine,_Line(xsOld[TmpIdx2],ysOld[TmpIdx2],xeOld[TmpIdx2],yeOld[TmpIdx2]));

   Panel.send(GraphDrawLine, "$GREEN");
   Panel.send(GraphDrawLine,_Line(xsOld[TmpIdx],ysOld[TmpIdx],xeOld[TmpIdx],yeOld[TmpIdx]));

   float RadAngle = (float)(PI/180.0) * Angle;

   byte xs = 5 + (MinDist * cos(RadAngle) + 127);
   byte ys = (MinDist * sin(RadAngle) + 30);
   byte xe = 5 + (Distance * cos(RadAngle) + 127);
   byte ye = (Distance * sin(RadAngle) + 30) ;

   OldAngle = Angle;
   
   Panel.send(GraphDrawLine, "$YELLOW");
   Panel.send(GraphDrawLine,_Line(xs,ys,xe,ye));
   xsOld[OldIdx] = xs;
   ysOld[OldIdx] = ys;
   xeOld[OldIdx] = xe;
   yeOld[OldIdx] = ye;

   Panel.sendf(GraphLabel_1, "Angle %d", 180-Angle);
  
}

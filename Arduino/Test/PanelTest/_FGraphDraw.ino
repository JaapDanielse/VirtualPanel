
boolean Direction = true;
int Angle = 0;
int Distance = 120;
static int i = 0;

#define NON 0 //
#define SQR 1 //
#define RAD 2 //
#define MAZ 3 //


static byte DrawStat = SQR;

void DrawCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
      Panel.send(ApplicationName,"PanelTest - Draw"); // set the application name

      Panel.send(Button_4,  F("next\npanel"));
      Panel.send(Button_5,  F("info"));
      Panel.send(Button_6,  F("moni\ntor"));
      Panel.send(Button_7,  F("graph"));
      Panel.send(Button_11, F("square"));
      Panel.send(Button_14, F("maze"));
      Panel.send(Button_17, F("radar"));
      Panel.send(DynamicDisplay,(int16_t)100); 
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

    case Button_11:
    {
      DrawStat = SQR;
      Panel.send(Graph, "$CLEAR");
      break;
    }

    case Button_14:
    {
      DrawStat = MAZ;
      Panel.send(Graph, F("$CLEAR"));
      i=0;
      break;
    }

    case Button_17:
    {
      DrawStat = RAD;
      Panel.send(Graph, F("$CLEAR"));
      DrawCircles();
      break;
    }


    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      if ( DrawStat == SQR )
      {
        Panel.send(Led_7, F("$ORANGE"));
        Panel.send(Led_8, F("$OFF"));
        Panel.send(Led_9, F("$OFF"));
        i+=5;
        DrawSquares(i);
        if(i>=105)
        {
          Panel.send(Graph, F("$CLEAR"));
          if (++ColNum > MaxColNum) ColNum=0;
          Panel.send(GraphDrawLine,  Color[ColNum]);
          i=0;
        }
      }
      
      if ( DrawStat == RAD )
      {
        Panel.send(Led_7, F("$OFF"));
        Panel.send(Led_8, F("$OFF"));
        Panel.send(Led_9, F("$ORANGE"));
        if (Direction) Angle+=2; else Angle-=2;
        if (Angle <= 0 || Angle >= 180) Direction = !Direction; 
        Angle = constrain( Angle, 0, 180);
        Swipe(Angle, Distance);
      }
      
      if ( DrawStat == MAZ )
      {
        Panel.send(Led_7, F("$OFF"));
        Panel.send(Led_8, F("$ORANGE"));
        Panel.send(Led_9, F("$OFF"));
        if(i<=0)
        {
          Panel.send(Graph, F("$CLEAR"));
          if (++ColNum > MaxColNum) ColNum=0;
          Panel.send(GraphDrawLine,  Color[ColNum]);
          for(int j=0; j<110; j++) { DisplayMaze(j);}
          i=25;
        }
        i--;
      }
      break;
    }
  }
}


void DrawSquares(int SquareSize)
{
     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(127-SquareSize,110-SquareSize));
     Panel.send(GraphDrawLine,_Point(127+SquareSize,110-SquareSize));
     Panel.send(GraphDrawLine,_Point(127+SquareSize,110+SquareSize));
     Panel.send(GraphDrawLine,_Point(127-SquareSize,110+SquareSize));
     Panel.send(GraphDrawLine,_Point(127-SquareSize,110-SquareSize));
}


void DrawCircles()
{
   Panel.send(GraphDrawCircle, "$ORANGE");
   Panel.send(GraphDrawCircle, "$2PX");
   Panel.send(GraphDrawCircle, _Circle(132,30,110,270,180));
   
   Panel.send(GraphDrawCircle, "$1PX");
   Panel.send(GraphDrawCircle, _Circle(132,30,55,270,180));
   
   Panel.send(GraphDrawLine,F("$1PX"));
   Panel.send(GraphCaption_2,"0 deg                                          180 deg");
}


void Swipe(int Angle, int Distance)
{
   #define MinDist 10//
   #define OldSize 50//

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
   
   Panel.send(GraphDrawLine,F("$DEL"));
   Panel.send(GraphDrawLine,_Line(xsOld[OldIdx],ysOld[OldIdx],xeOld[OldIdx],yeOld[OldIdx]));
   
   Panel.send(GraphDrawLine,F("$BLUE"));
   Panel.send(GraphDrawLine,_Line(xsOld[TmpIdx2],ysOld[TmpIdx2],xeOld[TmpIdx2],yeOld[TmpIdx2]));

   Panel.send(GraphDrawLine,F("$GREEN"));
   Panel.send(GraphDrawLine,_Line(xsOld[TmpIdx],ysOld[TmpIdx],xeOld[TmpIdx],yeOld[TmpIdx]));

   float RadAngle = (float)(PI/180.0) * Angle;

   byte xs = 5 + (MinDist * cos(RadAngle) + 127);
   byte ys = (MinDist * sin(RadAngle) + 30);
   byte xe = 5 + (Distance * cos(RadAngle) + 127);
   byte ye = (Distance * sin(RadAngle) + 30) ;

 //  OldAngle = Angle;
   
   Panel.send(GraphDrawLine,F("$YELLOW"));
   Panel.send(GraphDrawLine,_Line(xs,ys,xe,ye));
   xsOld[OldIdx] = xs;
   ysOld[OldIdx] = ys;
   xeOld[OldIdx] = xe;
   yeOld[OldIdx] = ye;

   Panel.send(GraphText, _Point(100,180));
   Panel.sendf(GraphText, F("Angle %d"), 180-Angle);
}


void DisplayMaze(int square)
{
  int xp, yp;

  xp = ((square/10)*20)+17;
  yp = ((square%10)*20)+10;
     
  int i = random(0,4);
  
  switch (i)
  {
    case 0: DrawSquareCross(xp,yp); break;
    case 1: DrawSquareRight(xp,yp); break;
    case 2: DrawSquareLeft(xp,yp); break;
    case 3: DrawSquareVert(xp,yp); break;
    default: break;
  }
}


void DrawSquareCross(int x, int y)
{
     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+6,y));
     Panel.send(GraphDrawLine,_Point(x+6, y+6));
     Panel.send(GraphDrawLine,_Point(x,y+6));

     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+13,y));
     Panel.send(GraphDrawLine,_Point(x+13, y+6));
     Panel.send(GraphDrawLine,_Point(x+20,y+6));

     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x,y+13));
     Panel.send(GraphDrawLine,_Point(x+6, y+13));
     Panel.send(GraphDrawLine,_Point(x+6,y+20));

     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+13,y+20));
     Panel.send(GraphDrawLine,_Point(x+13,y+13));
     Panel.send(GraphDrawLine,_Point(x+20,y+13));

}


void DrawSquareVert(int x, int y)
{
     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+6,y));
     Panel.send(GraphDrawLine,_Point(x+6, y+20));

     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+13,y));
     Panel.send(GraphDrawLine,_Point(x+13,y+20));

     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x,y+6));
     Panel.send(GraphDrawLine,_Point(x,y+13));

     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+20,y+6));
     Panel.send(GraphDrawLine,_Point(x+20,y+13));
}


void DrawSquareLeft(int x, int y)
{
     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x,y+6));
     Panel.send(GraphDrawLine,_Point(x+6, y));
     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+13, y));
     Panel.send(GraphDrawLine,_Point(x, y+13));

     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+6,y+20));
     Panel.send(GraphDrawLine,_Point(x+20, y+6));
     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+13, y+20));
     Panel.send(GraphDrawLine,_Point(x+20, y+13));
}


void DrawSquareRight(int x, int y)
{
     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x,y+6));
     Panel.send(GraphDrawLine,_Point(x+13,y+19));
     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x,y+14));
     Panel.send(GraphDrawLine,_Point(x+6, y+20));

     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+6,y));
     Panel.send(GraphDrawLine,_Point(x+19, y+13));
     Panel.send(GraphDrawLine); // new line
     Panel.send(GraphDrawLine,_Point(x+14, y));
     Panel.send(GraphDrawLine,_Point(x+20, y+6));
}

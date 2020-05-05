// VirtualPanel K-PointClick example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

char * Color[] = {"$WHITE","$YELLOW","$ORANGE","$RED","$GREEN","$BLUE","$GRAY"};
int ColorNum = 0;
const int MaxColorNum = 6;

char * PenSize[] = {"$1PX","$2PX","$3PX","$4PX"};
int PenSizeNum = 0;
const int MaxPenSizeNum = 3;

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
      Panel.send(ApplicationName,"Point-Click"); // set the application name
      Panel.send(GraphButton_1, "■");
      Panel.send(GraphButton_1, Color[ColorNum]);
      Panel.send(GraphButton_2, PenSize[PenSizeNum]);
      Panel.send(GraphButton_3, "clear");
      Panel.send(Graph, (bool)true);
      break; 

    case GraphButton_1:
      if (++ColorNum > MaxColorNum) ColorNum=0;
      Panel.send(GraphButton_1,  Color[ColorNum]);
      Panel.send(GraphDrawPixel, Color[ColorNum]);
      Panel.send(GraphDrawLine,  Color[ColorNum]);
      break;
    
    case GraphButton_2:
      if (++PenSizeNum > MaxPenSizeNum) PenSizeNum=0;
      Panel.send(GraphButton_2, PenSize[PenSizeNum]);
      Panel.send(GraphDrawLine, PenSize[PenSizeNum]);
      break;

    case GraphButton_3:
      Panel.send(Graph,"$CLEAR"); //
      break;

    case GraphClick:
      Panel.send(GraphDrawPixel, Panel.vpr_uint); // 
      Panel.send(GraphDrawLine, Panel.vpr_uint); // 
      break;

    case GraphDoubleClick:
      Panel.send(Display_2, "Double");
      Panel.send(Graph,"$CLEAR"); //
      break;

    case GraphRightClick:
      Panel.send(Display_2, "Right");
      Panel.send(GraphDrawLine); // Start a new line
      break;

  }
}

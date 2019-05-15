// VirtualPanel Minimal example 

#include "VirtualPanel.h"

char * Color[] = {"$WHITE","$YELLOW","$ORANGE","$RED","$GREEN","$BLUE","$GRAY"};
int ColorNum = 0;
const int MaxColorNum = 6;

char * PenSize[] = {"$1PX","$2PX","$3PX","$4PX"};
int PenSizeNum = 0;
const int MaxPenSizeNum = 3;

void setup() 
{
  Panel.Init(); // init port and protocol
}

void loop() 
{
  Panel.Receive(); // handle panel events form the panel (must be in the loop)
}


void PanelCallback(int event, int type) 
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      Panel.Send(ApplicationName,"Point-Click"); // set the application name
      Panel.Send(GraphButton_1, "■");
      Panel.Send(GraphButton_1, Color[ColorNum]);
      Panel.Send(GraphButton_2, PenSize[PenSizeNum]);
      Panel.Send(GraphButton_3, "clear");
      Panel.Send(Graph, true);
      break; 

    case GraphButton_1:
      if (++ColorNum > MaxColorNum) ColorNum=0;
      Panel.Send(GraphButton_1,  Color[ColorNum]);
      Panel.Send(GraphDrawPixel, Color[ColorNum]);
      Panel.Send(GraphDrawLine,  Color[ColorNum]);
    break;
    case GraphButton_2:
      if (++PenSizeNum > MaxPenSizeNum) PenSizeNum=0;
      Panel.Send(GraphButton_2, PenSize[PenSizeNum]);
      Panel.Send(GraphDrawLine, PenSize[PenSizeNum]);
    break;

    case GraphButton_3:
      Panel.Send(Graph,"$CLEAR"); //
    break;

    case GraphClick:
      Panel.Send(GraphDrawPixel, Panel.vpr_uint); // 
      Panel.Send(GraphDrawLine, Panel.vpr_uint); // 
    break;

    case GraphDoubleClick:
      Panel.Send(Display_2, "Double");
      Panel.Send(Graph,"$CLEAR"); //
    break;

    case GraphRightClick:
      Panel.Send(Display_2, "Right");
      Panel.Send(GraphDrawLine); // Start a new line
    break;

  }
}



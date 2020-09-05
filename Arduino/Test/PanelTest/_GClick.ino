

const char * PenSize[] = {"$1PX","$2PX","$3PX","$4PX"};
int PenSizeNum = 0;
const int MaxPenSizeNum = 3;

void ClickCallback(vp_channel event)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      ColNum = 0;
      Panel.send(ApplicationName,F("PanelTest - Click")); // set the application name
      Panel.send(Button_4,  F("next\npanel"));
      Panel.send(Button_5,  F("info"));
      Panel.send(Button_6,  F("moni\ntor"));
      Panel.send(Button_7,  F("graph"));
      Panel.send(GraphButton_1, "■");
      Panel.send(GraphButton_1, Color[ColNum]);
      Panel.send(GraphButton_2, PenSize[PenSizeNum]);
      Panel.send(GraphButton_3, "clear");
      Panel.send(GraphDrawPixel, Color[ColNum]);
      Panel.send(GraphDrawLine,  Color[ColNum]);
      Panel.send(GraphDrawLine, PenSize[0]);
      WriteInfo();
      Graphmode = true;
      Panel.send(Graph,Graphmode); 
      break; 

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
      Graphmode = !Graphmode;
      Panel.send(Graph,Graphmode);
      break;

    case GraphButton_1:
      if (++ColNum > MaxColNum) ColNum=0;
      Panel.send(GraphButton_1,  Color[ColNum]);
      Panel.send(GraphDrawPixel, Color[ColNum]);
      Panel.send(GraphDrawLine,  Color[ColNum]);
    break;
    
    case GraphButton_2:
      if (++PenSizeNum > MaxPenSizeNum) PenSizeNum=0;
      Panel.send(GraphButton_2, PenSize[PenSizeNum]);
      Panel.send(GraphDrawLine, PenSize[PenSizeNum]);
    break;

    case GraphButton_3:
      Panel.send(Graph,F("$CLEAR")); //
    break;
    
    case GraphClick:
      Panel.send(Display_2, F("Left Click"));
      Panel.send(GraphDrawPixel, Panel.vpr_uint); // send text to Display_2
      Panel.send(GraphDrawLine, Panel.vpr_uint); // send text to Display_2
      break;

    case GraphDoubleClick:
      Panel.send(Display_2, F("Double Click"));
      Panel.send(Graph,F("$CLEAR")); //
      break;

    case GraphRightClick:
      Panel.send(Display_2, F("Right Click"));
      Panel.send(GraphDrawLine); // Start a new line
    break;
  }
}

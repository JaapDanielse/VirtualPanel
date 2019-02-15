#define MaxColNum 5 //

char * Color[] = {"$WHITE","$YELLOW","$ORANGE","$RED","$GREEN","$BLUE"};
int ColNum = 0;



void ClickCallback(int event, int type)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      Panel.Send(Graph, true);
      Panel.Send(Button_1, F("⚫⚪")); //off on
      Panel.Send(Button_2, F("▲"));
      Panel.Send(Button_3, F("▼"));
      Panel.Send(Button_4, F("◀"));
      Panel.Send(Button_5, F("▶"));
      Panel.Send(Button_6, F("$BIG"));
      Panel.Send(Button_6, F("$GRAY"));
      Panel.Send(Button_6, F("Test"));
      Panel.Send(Button_7, F("Test\n⚫")); 
      Panel.Send(Button_8, F("⭯"));
      Panel.Send(Button_9, F("⭮"));
      Panel.Send(Button_10, F(""));
      Panel.Send(Button_11, F(""));
      Panel.Send(Button_12, F("$RTURN"));
      Panel.Send(Button_13, F("$LTURN"));
      Panel.Send(Button_14, F("$ONOFF"));
      Panel.Send(Button_15, F("$UP"));
      Panel.Send(Button_16, F("$DOT"));
      Panel.Send(Button_17, F("$DOWN"));
      Panel.Send(GraphButton_1, F("■"));
      Panel.Send(GraphButton_1, F("$WHITE"));
      Panel.Send(GraphButton_2, F("1PX"));
      Panel.Send(GraphButton_3, F("clear"));
      break; 

    case Button_4:
      PanelMode = Clock;
      Panel.Send(Reset);
      break;

    case Button_5:
      Panel.Send(Display_1, "◀ ▶ ▲ ▼ 🔨");
      break;

    case GraphButton_1:
      if (++ColNum > MaxColNum) ColNum=0;
      Panel.Send(GraphButton_1,  Color[ColNum]);
      Panel.Send(GraphPen, Color[ColNum]);
      break;

    case GraphButton_2:
      if (++ColNum > MaxColNum) ColNum=0;
      Panel.Send(GraphButton_1,  Color[ColNum]);
      Panel.Send(GraphPen, Color[ColNum]);
      break;

    case GraphClick:
      Panel.Send(GraphDrawPixel, Panel.vpr_uint); // send text to Display_2
      Panel.Send(GraphDrawLine, Panel.vpr_uint); // send text to Display_2
      break;

    case GraphDoubleClick:
      Panel.Send(Display_2, "Double");
      Panel.Send(GraphDrawLine); // send text to Display_2
      break;

    case GraphRightClick:
      Panel.Send(Display_2, "Right");
      Panel.Send(Graph,"$CLEAR"); //
      break;

  }
}



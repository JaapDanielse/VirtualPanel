#define MaxColNum 5 //

char * Color[] = {"$WHITE","$YELLOW","$ORANGE","$RED","$GREEN","$BLUE"};
int ColNum = 0;



void ClickCallback(int event, int type)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      Panel.Send(Graph, true);
      Panel.Send(Button_4, F("Next"));
      Panel.Send(Button_5, F("Extended"));
      Panel.Send(GraphButton_1, F("$DOT"));
      Panel.Send(GraphButton_1, F("$WHITE"));
      Panel.Send(GraphButton_2, F("1PX"));
      Panel.Send(GraphButton_3, F("clear"));
      break; 

    case Button_4:
      PanelMode = Clock;
      Panel.Send(Reset);
      break;

    case Button_5:
      Panel.Send(Display_1, "µ");
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



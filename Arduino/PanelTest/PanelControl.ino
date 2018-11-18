//

#define NextButton Button_4 //
boolean Graphmode = false;
boolean Monmode = false;

void PanelCallback(int event, int type) 
{ 
  // PanelCallback is called when a message is received from the panel 
  // only channel and type are passed as parameters. Panel data available as public library vars
  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
      // initialize panel layout
      Panel.Send(ApplicationName,"Panel Test"); // set the application name
      Panel.Send(Display_1, "$BIG");       // set display 1 (time) to big font
      Panel.Send(Display_1, "$BOLD");      // set display 1 (time) to bold 
      Panel.Send(Display_2, "$BLACK");     // set display 2 (date) to black
      Panel.Send(DynamicDisplay,100);     // enable dynamic display request
      Panel.Send(Button_4,  "next");
      Panel.Send(UnixTime, true);          // request time
      Panel.Send(GraphGrid, 15);
      Panel.Send(GraphCaption_1, "100");
      Panel.Send(GraphCaption_2, "0");
      Panel.Send(GraphButton_1, "GrBttn 1");
      Panel.Send(GraphButton_2, "GrBttn 2");
      Panel.Send(GraphButton_3, "GrBttn 3");
      Panel.Send(GraphButton_4, "GrBttn 4");
      
      Panel.Send(GraphLabel_1, "$YELLOW");
      Panel.Send(GraphLabel_1, "GraphLabel_1");
      Panel.Send(GraphLabel_2, "$ORANGE");
      Panel.Send(GraphLabel_2, "GraphLabel_2");
      Panel.Send(GraphLabel_3, "$RED");
      Panel.Send(GraphLabel_3, "GraphLabel_3");
      Panel.Send(GraphLabel_4, "$BLUE");
      Panel.Send(GraphLabel_4, "GraphLabel_4");
      Panel.Send(GraphLabel_5, "$GREEN");
      Panel.Send(GraphLabel_5, "GraphLabel_5");
      //Panel.Send(GraphDraw,Line(50,50,50,200)); // Output date to display 2
      //Panel.Send(GraphDraw,Line(50,200,200,200)); // Output date to display 2
      //Panel.Send(GraphDraw,Line(200,200,200,50)); // Output date to display 2
      //Panel.Send(GraphDraw,Line(200,50,50,50)); // Output date to display 2

      break; 
    }

    case UnixTime: // receive (local) time in unix timestamp 
    {
      setTime(Panel.vpr_ulong); // set time using received unsigend long from panel
      break;
    }

    case NextButton:
    {
      SwitchPanel();
      Panel.Send(Pling);
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

    

    case GraphButton_1: yellow = !yellow; break;
    case GraphButton_2: orange = !orange; break;
    case GraphButton_3: red = !red; break;
    case GraphButton_4: blue = !blue; break;

    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      Panel.Sendf(Display_1,"%02d:%02d:%02d",hour(), minute(), second()); // Output time to display 1
      Panel.Sendf(Display_2,"%02d-%02d-%04d",day(), month(), year()); // Output date to display 2
      if(blue)  Panel.Send(GraphValue_5,(byte)random(0,51));   //green
      if(blue)  Panel.Send(GraphValue_4,(byte)random(51,102));
      if(red)   Panel.Send(GraphValue_3,(byte)random(102,153));
      if(orange)Panel.Send(GraphValue_2,(byte)random(153,204));
      if(yellow)Panel.Send(GraphValue_1,(byte)random(204,255)); 

      //Panel.Send(GraphValue_1, (byte)255);
      
      break;
    }

    default:
    {
       if (event >= 8 && event <= 24) 
         Panel.Sendf(MonitorScrollBox,"ChannelId %d Button_%d Pressed", event, event-7 );
       if (event >= 25 && event <= 28)
         Panel.Sendf(MonitorScrollBox,"ChannelId %d ScrollBar_%d Value %d", event, event-24, Panel.vpr_int );
    }
  }
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

void SwitchPanel()
{
  static int panelnum = 0;
  const int  panelcount = 3;
    
  ClearPanel();

  switch ( panelnum )
  {
    case 0:
    {
      AllButtonPanel();
      break;
    }

    case 1:
    {
      ScrollbarPanel();
      break;
    }

    case 2:
    {
      ControlPanel();
      break;
    }
  
  }

  panelnum++;
  if (panelnum == panelcount) panelnum = 0;  
}


void AllButtonPanel()
{
  Panel.Send(MonitorScrollBox, "AllButtonPanel");
  Panel.Send(MonitorField_1, false);
  Panel.Send(MonitorField_2, (byte)254 );
  Panel.Send(MonitorField_3, (int)-32768 );
  Panel.Send(MonitorField_4, (unsigned int)65535 );
  Panel.Send(MonitorField_5, (long)-2147483648 );
  Panel.Send(MonitorField_6, (unsigned long)4294967295 );
  
  Panel.Send(Display_1, "display 1");
  Panel.Send(Display_2, "display 2");
  Panel.Send(Display_3, "display 3");
  Panel.Send(Display_4, "display 4");




  
  Panel.Send(Button_1,  "button 1");
  Panel.Send(Button_2,  "button 2");
  Panel.Send(Button_3,  "button 3");
  Panel.Send(Button_4,  "button 4");
  Panel.Send(Button_5,  "button 5");
  Panel.Send(Button_6,  "button 6");
  Panel.Send(Button_7,  "button 7");
  Panel.Send(Button_8,  "button 8");
  Panel.Send(Button_9,  "button 9");
  Panel.Send(Button_10, "button 10");
  Panel.Send(Button_11, "button 11");
  Panel.Send(Button_12, "button 12");
  Panel.Send(Button_13, "button 13");
  Panel.Send(Button_14, "button 14");
  Panel.Send(Button_15, "button 15");
  Panel.Send(Button_16, "button 16");
  Panel.Send(Button_17, "button 17");


  Panel.Send(Led_1,  "$OFF");
  Panel.Send(Led_2,  "$WHITE");
  Panel.Send(Led_3,  "$YELLOW");
  Panel.Send(Led_4,  "$ORANGE");
  Panel.Send(Led_5,  "$RED");
  Panel.Send(Led_6,  "$BLUE");
  Panel.Send(Led_7,  "$GREEN");
  Panel.Send(Led_8,  "$YELLOW");
  Panel.Send(Led_9,  "$ORANGE");
  Panel.Send(Led_10,  "$BLUE");
  Panel.Send(Led_11,  "$GREEN");
  Panel.Send(Led_12,  "$YELLOW");
  Panel.Send(Led_13,  "$ORANGE");

}


void ScrollbarPanel()
{
  Panel.Send(MonitorScrollBox, "MonitorScrollBox");
  Panel.Send(MonitorField_1, "MonitorField_1");
  Panel.Send(MonitorField_2, "MonitorField_2");
  Panel.Send(MonitorField_3, "MonitorField_3");
  Panel.Send(MonitorField_4, "MonitorField_4");
  Panel.Send(MonitorField_5, "MonitorField_5");
  Panel.Send(MonitorField_6, "MonitorField_6");

  Panel.Send(Display_1, "display 1");
  Panel.Send(Display_2, "display 2");
  Panel.Send(Display_3, "display 3");
  Panel.Send(Display_4, "display 4");

  Panel.Send(ScrollBar_1, true);
//  Panel.Send(MaxScrollBar_1, 50);
  Panel.Send(ScrollBar_2, true);
  Panel.Send(ScrollBar_3, true);
  Panel.Send(ScrollBar_4, true);

  Panel.Send(ScrollBar_1, "scrlab1");
  Panel.Send(ScrollBar_2, "scrlab2");
  Panel.Send(ScrollBar_3, "scrlab3");
  Panel.Send(ScrollBar_4, "scrlab4");

  Panel.Send(Button_4,  "button 4");
  Panel.Send(Button_5,  "button 5");
  Panel.Send(Button_6,  "button 6");
  Panel.Send(Button_7,  "button 7");
  Panel.Send(Button_8,  "button 8");
 
  Panel.Send(Led_2,  "$WHITE");
  Panel.Send(Led_3,  "$YELLOW");
  Panel.Send(Led_4,  "$ORANGE");
  Panel.Send(Led_5,  "$RED");
  Panel.Send(Led_6,  "$BLUE");

  Panel.Send(Led_10,  "$BLUE");
  Panel.Send(Led_11,  "$GREEN");
  Panel.Send(Led_12,  "$YELLOW");
  Panel.Send(Led_13,  "$ORANGE");

}


void ControlPanel()
{
  Panel.Send(MonitorScrollBox, "ControlPanel");
  Panel.Send(MonitorField_1, false);
  Panel.Send(MonitorField_2, (byte)254 );
  Panel.Send(MonitorField_3, (int)-32768 );
  Panel.Send(MonitorField_4, (unsigned int)65535 );
  Panel.Send(MonitorField_5, (long)-2147483648 );
  Panel.Send(MonitorField_6, (unsigned long)4294967295 );

  Panel.Send(Display_1, "display 1");
  Panel.Send(Display_2, "display 2");
  Panel.Send(Display_3, "display 3");
  Panel.Send(Display_4, "display 4");
  
  Panel.Send(Button_1,  "$YELLOW");
  Panel.Send(Button_1,  "$UP");
  Panel.Send(Button_2,  "$ORANGE");
  Panel.Send(Button_2,  "$DOWN");
  Panel.Send(Button_3,  "$ONOFF");

  Panel.Send(Button_4,  "next");
  
  Panel.Send(Button_5,  "$RUN");
  Panel.Send(Button_6,  "$PAUSE");
  Panel.Send(Button_7,  "$STOP");
  Panel.Send(Button_8,  "$SET");

  Panel.Send(Button_9,  "$LTURN");
  Panel.Send(Button_10, "$LEFT");

  Panel.Send(Button_11, "$GREEN");
  Panel.Send(Button_11, "$DOT" );

  Panel.Send(Button_12, "$UP" );
  Panel.Send(Button_13, "$DOT");
  Panel.Send(Button_14, "$DOWN");
  Panel.Send(Button_15, "$RTURN");
  Panel.Send(Button_16, "$RIGHT");
  
  Panel.Send(Button_17, "$RED");
  Panel.Send(Button_17, "$DOT");


}


void ClearPanel()
{
  //
  Panel.Send(Display_1, "$NORMAL");
  Panel.Send(Display_1, "$WHITE");
  Panel.Send(Display_1, "");
  Panel.Send(Display_1, false);
  //
  Panel.Send(Display_2, "$NORMAL");
  Panel.Send(Display_2, "$WHITE");
  Panel.Send(Display_2, "");
  Panel.Send(Display_2, false);
  //
  Panel.Send(Display_3, "$NORMAL");
  Panel.Send(Display_3, "$WHITE");
  Panel.Send(Display_3, "");
  Panel.Send(Display_3, false);
  //
  Panel.Send(Display_4, "$NORMAL");
  Panel.Send(Display_4, "$WHITE");
  Panel.Send(Display_4, "");
  Panel.Send(Display_4, false);
  //
  Panel.Send(Button_1, false);
  Panel.Send(Button_2, false);
  Panel.Send(Button_3, false);
  Panel.Send(Button_4, false);
  Panel.Send(Button_5, false);
  Panel.Send(Button_6, false);
  Panel.Send(Button_7, false);
  Panel.Send(Button_8, false);
  Panel.Send(Button_9, false);
  Panel.Send(Button_10, false);
  Panel.Send(Button_11, false);
  Panel.Send(Button_12, false);
  Panel.Send(Button_13, false);
  Panel.Send(Button_14, false);
  Panel.Send(Button_15, false);
  Panel.Send(Button_16, false);
  Panel.Send(Button_17, false);
  //
  Panel.Send(Button_1, "$BLACK");
  Panel.Send(Button_2, "$BLACK");
  Panel.Send(Button_3, "$BLACK");
  Panel.Send(Button_4, "$BLACK");
  Panel.Send(Button_5, "$BLACK");
  Panel.Send(Button_6, "$BLACK");
  Panel.Send(Button_7, "$BLACK");
  Panel.Send(Button_8, "$BLACK");
  Panel.Send(Button_9, "$BLACK");
  Panel.Send(Button_10, "$BLACK");
  Panel.Send(Button_11, "$BLACK");
  Panel.Send(Button_12, "$BLACK");
  Panel.Send(Button_13, "$BLACK");
  Panel.Send(Button_14, "$BLACK");
  Panel.Send(Button_15, "$BLACK");
  Panel.Send(Button_16, "$BLACK");
  Panel.Send(Button_17, "$BLACK");
  //
  Panel.Send(ScrollBar_1, false);
  Panel.Send(ScrollBar_2, false);
  Panel.Send(ScrollBar_3, false);
  Panel.Send(ScrollBar_4, false);
  //
  Panel.Send(Led_1, false);
  Panel.Send(Led_2, false);
  Panel.Send(Led_3, false);
  Panel.Send(Led_4, false);
  Panel.Send(Led_5, false);
  Panel.Send(Led_6, false);
  Panel.Send(Led_7, false);
  Panel.Send(Led_8, false);
  Panel.Send(Led_9, false);
  Panel.Send(Led_10, false);
  Panel.Send(Led_11, false);
  Panel.Send(Led_12, false);
  Panel.Send(Led_13, false);
 //
  Panel.Send(DynamicDisplay,false);  
}


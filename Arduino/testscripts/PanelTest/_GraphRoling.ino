boolean yellow = true;
boolean orange = true;
boolean red = true;
boolean blue = true;   

 void RolingCallback(int event, int type)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
     // initialize panel layout
      Panel.Send(ApplicationName,F("PanelTest - RolingGraph")); // set the application name
      Panel.Send(DynamicDisplay,100);     // enable dynamic display request
      Panel.Send(Button_4,  F("next"));
      Panel.Send(Button_5,  F("graph"));
      Panel.Send(Button_6,  F("mon"));
      Panel.Send(GraphGrid, 15);
      Panel.Send(GraphCaption_1, F("100"));
      Panel.Send(GraphCaption_2, F("0"));
      Panel.Send(GraphButton_1, F("GrBttn 1"));
      Panel.Send(GraphButton_2, F("GrBttn 2"));
      Panel.Send(GraphButton_3, F("GrBttn 3"));
      Panel.Send(GraphButton_4, F("GrBttn 4"));
      Panel.Send(GraphLabel_1, F("$YELLOW"));
      Panel.Send(GraphLabel_1, F("GraphLabel_1"));
      Panel.Send(GraphLabel_2, F("$ORANGE"));
      Panel.Send(GraphLabel_2, F("GraphLabel_2"));
      Panel.Send(GraphLabel_3, F("$RED"));
      Panel.Send(GraphLabel_3, F("GraphLabel_3"));
      Panel.Send(GraphLabel_4, F("$BLUE"));
      Panel.Send(GraphLabel_4, F("GraphLabel_4"));
      Panel.Send(GraphLabel_5, F("$GREEN"));
      Panel.Send(GraphLabel_5, F("GraphLabel_5"));
      Panel.Send(Graph,true); 

      break; 
    }

    case Button_4:
    {
      PanelMode = Static;
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

    case GraphButton_1:
      yellow = !yellow; break;
    case GraphButton_2: 
      orange = !orange; break;
    case GraphButton_3: 
      red = !red; break;
    case GraphButton_4: 
      blue = !blue; break;


    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      Panel.Sendf(Display_1,"%02d:%02d:%02d",hour(), minute(), second()); // Output time to display 1
      Panel.Sendf(Display_2,"%02d-%02d-%04d",day(), month(), year()); // Output date to display 2
      if(blue)  Panel.Send(GraphValue_5,(byte)random(0,51));   //green
      if(blue)  Panel.Send(GraphValue_4,(byte)random(51,102));
      if(red)   Panel.Send(GraphValue_3,(byte)random(102,153));
      if(orange)Panel.Send(GraphValue_2,(byte)random(153,204));
      if(yellow)Panel.Send(GraphValue_1,(byte)random(204,255)); 
      break;
    }
    
    default:
      break;
  }
}
 


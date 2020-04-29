byte yellow = 0;
byte orange = 0;
byte red = 0;
byte blue = 0;   
byte green = 0;   

 void RolingCallback(vp_channel event)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
    { 
     // initialize panel layout
      Panel.send(ApplicationName,F("PanelTest - RolingGraph")); // set the application name
      Panel.send(PanelColor,"$PINK"); // set the application name
      Panel.send(DynamicDisplay,100);     // enable dynamic display request
      Panel.send(Button_4,  F("next\npanel"));
      Panel.send(Button_5,  F("info"));
      Panel.send(Button_6,  F("moni\ntor"));
      Panel.send(Button_7,  F("graph"));
      Panel.send(GraphGrid, 15);
      Panel.send(GraphCaption_1, F("Caption_1"));
      Panel.send(GraphCaption_2, F("Caption_2"));
      Panel.send(GraphButton_1, F("GrBttn 1"));
      Panel.send(GraphButton_2, F("GrBttn 2"));
      Panel.send(GraphButton_3, F("GrBttn 3"));
      Panel.send(GraphButton_4, F("GrBttn 4"));
      Panel.send(GraphLabel_1, F("$YELLOW"));
      Panel.send(GraphLabel_1, F("GraphLabel_1"));
      Panel.send(GraphLabel_2, F("$ORANGE"));
      Panel.send(GraphLabel_2, F("GraphLabel_2"));
      Panel.send(GraphLabel_3, F("$RED"));
      Panel.send(GraphLabel_3, F("GraphLabel_3"));
      Panel.send(GraphLabel_4, F("$BLUE"));
      Panel.send(GraphLabel_4, F("GraphLabel_4"));
      Panel.send(GraphLabel_5, F("$GREEN"));
      Panel.send(GraphLabel_5, F("GraphLabel_5"));
      Panel.send(GraphValue_2,"$2PX");
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
      Graphmode = !Graphmode;
      Panel.send(Graph,Graphmode);
      break;

    case DynamicDisplay: // dynamic display request (requested every 500ms)
    {
      yellow = random(0,255); // generate yellow "sensor" value
      orange = random(0,255); // generate orange "sensor" value
      red    = random(0,255); // generate red "sensor" value
      blue   = random(0,255); // generate blue "sensor" value  
      green  = random(0,255); // generate green "sensor" value   

      Panel.sendf(Display_1,"y:%03d  o:%03d  r:%03d  b:%03d  g:%03d", yellow, orange, red, blue, green); 
      Panel.send(GraphValue_1,(byte)map(yellow,0,255, 204,255)); // map yellow to grid sections 9 and 10
      Panel.send(GraphValue_2,(byte)map(orange,0,255, 153,204)); // map orange to grid sections 7 and 8
      Panel.send(GraphValue_3,(byte)map(red,   0,255, 102,153)); // map red to grid sections 5 and 6
      Panel.send(GraphValue_4,(byte)map(blue,  0,255,  51,102)); // map blue to grid sections 3 and 4
      Panel.send(GraphValue_5,(byte)map(green, 0,255,   0, 51)); // map green to grid sections 1 and 2
      break;
    }
    
    default:
      break;
  }
}
 

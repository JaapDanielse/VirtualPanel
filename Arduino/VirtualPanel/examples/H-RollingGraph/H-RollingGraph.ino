// VirtualPanel H-RollingGraph example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool    InfoVisible = false; // Power status

byte yellow = 0;
byte orange = 0;
byte red = 0;
byte blue = 0;   
byte green = 0;   

void setup() 
{
  Panel.Init(); // init port and protocol
}

void loop() 
{
  Panel.Receive(); // handle panel events form the panel (must be in the loop)
  yellow = random(0,255); // generate yellow "sensor" value
  orange = random(0,255); // generate orange "sensor" value
  red    = random(0,255); // generate red "sensor" value
  blue   = random(0,255); // generate blue "sensor" value  
  green  = random(0,255); // generate green "sensor" value   
}

void PanelCallback(int event, int type) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.Send(ApplicationName,"RollingGraph"); // set the application name
      Panel.Send(Button_8,"info"); // Button_3 visible and set text "on/off"
      Panel.Send(GraphLabel_1, F("$YELLOW")); // set label bar color
      Panel.Send(GraphLabel_1, F("Yellow \"sensor\"")); // set label text
      Panel.Send(GraphLabel_2, F("$ORANGE")); // set label bar color
      Panel.Send(GraphLabel_2, F("Orange \"sensor\""));
      Panel.Send(GraphLabel_3, F("$RED")); // set label bar color
      Panel.Send(GraphLabel_3, F("Red \"sensor\""));
      Panel.Send(GraphLabel_4, F("$BLUE")); // set label bar color
      Panel.Send(GraphLabel_4, F("Blue \"sensor\""));
      Panel.Send(GraphLabel_5, F("$GREEN")); // set label bar color
      Panel.Send(GraphLabel_5, F("Green \"sensor\""));
      Panel.Send(GraphCaption_1, F("five \"sensor\" graphs")); 
      Panel.Send(GraphCaption_2, F("yellow, orange, red, blue, green"));
      Panel.Send(GraphGrid, 15); // set graph grid to 15 vertical sections
      Panel.Send(Graph,true); 

      Panel.Send(InfoTitle, F("Roling Graph")); // Info Title the F() macro can be used to force strings in program memory
      Panel.Send(InfoText, F("The graph panel is set visible"));
      Panel.Send(InfoText, F("By simply pushing value (between 0 and 255) to the different"));
      Panel.Send(InfoText, F("GraphValue_x events you \"feed\" the graphs"));
      Panel.Send(InfoText, F("In this case values are mapped to a specific section."));
      Panel.Send(InfoText, F("In this rolling graph values scroll from right to left"));
      Panel.Send(InfoText, F("The number of values can be set. Default (used here) is 50."));

      Panel.Send(DynamicDisplay,100);     // enable dynamic display request
    break;

    case Button_8: // Catch button pressed
      InfoVisible = !InfoVisible;
    break;
    
    case DynamicDisplay: // dynamic display request (requested every 500ms)
      Panel.Sendf(Display_1,"y:%03d  o:%03d  r:%03d  b:%03d  g:%03d", yellow, orange, red, blue, green); 
      Panel.Send(GraphValue_1,(byte)map(yellow,0,255, 204,255)); // map yellow to grid sections 9 and 10
      Panel.Send(GraphValue_2,(byte)map(orange,0,255, 153,204)); // map orange to grid sections 7 and 8
      Panel.Send(GraphValue_3,(byte)map(red,   0,255, 102,153)); // map red to grid sections 5 and 6
      Panel.Send(GraphValue_4,(byte)map(blue,  0,255,  51,102)); // map blue to grid sections 3 and 4
      Panel.Send(GraphValue_5,(byte)map(green, 0,255,   0, 51)); // map green to grid sections 1 and 2
    break;
  }

  StaticChange();
}

void StaticChange()
{
  if (InfoVisible)
    Panel.Send(Info, true); // set info panel visible
  else
    Panel.Send(Info, false); // set info panel invisible
}



// VirtualPanel F-Input example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

bool    Power = false; // Power status
bool    MonitorVisible = false; // Power status
bool    InfoVisible = false; // Power status
char    Value[60]="channel 1";

void setup() 
{
  Panel.begin(); // init port and protocol
}

void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
  delay(250); // delay 
}

void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
    
      Panel.send(PanelColor,"$GREEN"); // set the application name
      Panel.send(ApplicationName,"Graph Values"); // set the application name
      Panel.send(Graph,true);
      Panel.send(GraphLabel_1, Value);
      Panel.send(GraphLabel_1, "$RED");
      Panel.send(GraphLabel_2, Value);
      Panel.send(GraphLabel_2, "$GREEN");
      Panel.send(GraphLabel_3, Value);
      Panel.send(GraphLabel_3, "$BLUE");
      Panel.send(GraphLabel_4, Value);
      Panel.send(GraphLabel_4, "$PURPLE");
      Panel.send(GraphLabel_5, Value);
      Panel.send(GraphLabel_5, "$YELLOW");
    break;

    case GraphLabel_1: // display has been double clicked 
      Panel.send(MinGraphInput_1, 0); // 
      Panel.send(MaxGraphInput_1, 100); // 
      Panel.send(GraphInputLabel_1, "descr."); // 
      Panel.send(GraphInput_1, Value); // 
    break;

    case GraphInput_1:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        strcpy(Value,Panel.vpr_string); // ok, store
    break;
    
    case GraphLabel_2: // display has been double clicked 
      Panel.send(MinGraphInput_2, 0); // 
      Panel.send(MaxGraphInput_2, 100); // 
      //Panel.send(GraphInputLabel_2, "descr."); // 
      Panel.send(GraphInput_2, Value); // 
    break;

    case GraphInput_2:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        strcpy(Value,Panel.vpr_string); // ok, store
    break;
    
    case GraphLabel_3: // display has been double clicked 
      Panel.send(MinGraphInput_3, 0); // 
      Panel.send(MaxGraphInput_3, 100); // 
      Panel.send(GraphInputLabel_3, "descr."); // 
      Panel.send(GraphInput_3, Value); // 
    break;

    case GraphInput_3:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        strcpy(Value,Panel.vpr_string); // ok, store
    break;
    
    case GraphLabel_4: // display has been double clicked 
      Panel.send(MinGraphInput_4, 0); // 
      Panel.send(MaxGraphInput_4, 100); // 
      Panel.send(GraphInputLabel_4, "descr."); // 
      Panel.send(GraphInput_4, Value); // 
    break;

    case GraphInput_4:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        strcpy(Value,Panel.vpr_string); // ok, store
    break;
    
    case GraphLabel_5: // display has been double clicked 
      Panel.send(MinGraphInput_5, 0); // 
      Panel.send(MaxGraphInput_5, 100); // 
      Panel.send(GraphInputLabel_5, "descr."); // 
      Panel.send(GraphInput_5, Value); // 
    break;

    case GraphInput_5:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        strcpy(Value,Panel.vpr_string); // ok, store
    break;

  }

  StaticChange();
}


void StaticChange()
{
  Panel.send(Display_1, Value); // write display_1
  Panel.send(GraphLabel_1, Value); // write display_1
}


char    Value[60]="channel 1";

void GraphInputCallback(vp_channel event)
{  
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
    
      Panel.send(PanelColor,"$GREEN"); // set the application name
      Panel.send(ApplicationName,"PanelTest - Graph Inputs"); // set the application name
      Panel.send(Button_4,  F("next\npanel"));
      Panel.send(Graph,true);
      Panel.send(GraphLabel_1, "Channel 1");
      Panel.send(GraphLabel_1, "$RED");
      Panel.send(GraphLabel_2, "Channel 2");
      Panel.send(GraphLabel_2, "$GREEN");
      Panel.send(GraphLabel_3, "Channel 3");
      Panel.send(GraphLabel_3, "$BLUE");
      Panel.send(GraphLabel_4, "Channel 4");
      Panel.send(GraphLabel_4, "$PURPLE");
      Panel.send(GraphLabel_5, "Channel 5");
      Panel.send(GraphLabel_5, "$YELLOW");
      Panel.send(GraphDrawCircle, _Circle(128,110,100));
      Panel.send(MinGraphInput_1, 0); // 
      Panel.send(MaxGraphInput_1, 100); // 
      Panel.send(GraphInputLabel_1, "descr."); // 
      Panel.send(GraphInput_1, Value); // 
      Panel.send(GraphInput_1, true); // 
    break;


    case Button_4:
      if( ++PanelMode == Endmode ) PanelMode = 0;
      Panel.send(Reset);
      break;

    case GraphLabel_1: // display has been double clicked 
    break;

    case GraphInput_1:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        strcpy(Value,Panel.vpr_string); // ok, store
      Panel.send(GraphLabel_1, Value); // write display_1
    break;
    
    case GraphLabel_2: // display has been double clicked 
      Panel.send(MinGraphInput_2, 0); // 
      Panel.send(MaxGraphInput_2, 100); // 
      Panel.send(GraphInputLabel_2, "descr."); // 
      Panel.send(GraphInput_2, Value); // 
    break;

    case GraphInput_2:
      if (Panel.vpr_type != vp_type::vp_void) // check if not discarded
        strcpy(Value,Panel.vpr_string); // ok, store
      Panel.send(GraphLabel_2, Value); // write display_1
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
      Panel.send(GraphLabel_3, Value); // write display_1
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
      Panel.send(GraphLabel_4, Value); // write display_1
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
      Panel.send(GraphLabel_5, Value); // write display_1
    break;
  }
  Panel.send(Display_1, Value); // write display_1
}
 

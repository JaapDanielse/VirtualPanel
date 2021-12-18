
//---------------------------------------------------------------------------
void PanelOneCallback(vp_channel event) // Mode One callback
{ 
  switch (event) 
  {
    case PanelConnected: // panel init specific for mode one
      Panel.send(Display_1, "Panel - One");
      Panel.send(Button_3, "Next\nPanel");
      Panel.send(Button_5, "One");
      break; 
      
    case Button_3: 
      ChangePanelMode(); // switch to next mode see tab _APanelControl
      break;
    
    case Button_5: 
      Panel.send(Display_2, "One it is"); 
      break;
 
    default: break;
  }
}

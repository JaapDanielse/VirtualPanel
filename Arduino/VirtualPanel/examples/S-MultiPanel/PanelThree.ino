
//---------------------------------------------------------------------------
void PanelThreeCallback(vp_channel event) // Mode three callback
{ 
  switch (event) 
  {
    case PanelConnected: // panel init specific for mode three
      Panel.send(Display_1, "Panel - Three");
      Panel.send(Button_3, "Next\nPanel");
      Panel.send(Button_7, "3");
      break; 
      
    case Button_3: 
      ChangePanelMode(); // switch to next mode see tab _APanelControl 
      break;
    
    case Button_7: 
      Panel.send(Display_2, "3 it is"); 
      break;
 
     default: break;
  }
}

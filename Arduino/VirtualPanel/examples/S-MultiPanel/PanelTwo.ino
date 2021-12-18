
//---------------------------------------------------------------------------
void PanelTwoCallback(vp_channel event) // Mode two callback 
{ 
  switch (event) 
  {
    case PanelConnected: // panel init specific for mode two
      Panel.send(Display_1, "Panel - Two");
      Panel.send(Button_3, "Next\nPanel");
      Panel.send(Button_6, "TWO");
      break; 
      
    case Button_3: 
      ChangePanelMode(); // switch to next mode see tab _APanelControl 
      break;
    
    case Button_6: 
      Panel.send(Display_2, "TWO it is"); 
      break;
 
     default: break;
  }
}

// Panel Dispatcher

enum ModeList {ONE, TWO, THREE, MODEEND}; // mode enum
int16_t PanelMode = ONE; // int used because it can increment

//---------------------------------------------------------------
// this is the actual callback, but it simply forwards to specific callback for each mode
void PanelCallback(vp_channel event) 
{ 
  switch (PanelMode)
  {
    case ONE:
      PanelOneCallback( event); break;

    case TWO: 
      PanelTwoCallback( event); break;

    case THREE: 
      PanelThreeCallback( event); break;

    default: break;
  }
}

//---------------------------------------------------------------
void ChangePanelMode() //called from each panel to switch to the next mode
{
  if(++PanelMode == MODEEND) PanelMode = ONE; // update the mode
  Panel.send(Reset); // reset the panel
}

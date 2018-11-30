//-----------------------------------------------------------------------------------------------
// Callback

void PanelCallback(int chanel, int type)
{
  // Called by Panel.Receive after receiving a panel event
  
  switch (chanel) 
  {
    case PanelConnected: // Pannel connected: Init Controls
    { 
      MyPanelInit(); 
      break; 
    }

    case DynamicDisplay: // DynamicDisplay requested: Send Dynamic Data
    { 
      MyPanelDynamicDisplay(); 
      break; 
    }

    case ScrollBar_2: // Frequency Scrollbar moved
    { 
      KiloHertz = MyPanel.vpr_int; // vpr_int contains the value received. there is also vpr_byte, vpr_uint etc.  
      MyPanel.Sendf(Display_1,"%03d %03d Hz", KiloHertz, Hertz  ); // Return Static value for scrollbar only
      break; 
    }

    case ScrollBar_3: // 
    { 
      Hertz = MyPanel.vpr_int ; 
      MyPanel.Sendf(Display_1,"%03d %03d Hz", KiloHertz, Hertz  ); // Return Static value for scrollbar only
      break; 
    }
    case ScrollBar_4: // Duty Scrollbar moved
    { 
      BlinkDuty = MyPanel.vpr_int ; 
      MyPanel.Sendf(Display_2,"%03d %%", BlinkDuty ); // Return Static value for scrollbar only
      break; 
    }
    
    case Button_3:// (on/off) pressed
    { 
      Power=!Power; 
      MyPanel.Sendf(StatMonitor,"Power %d after %d ms", Power, millis() ); 
      MyPanelStaticDisplay(); 
      break; 
    }
    
    break;
  }
  CommandReceived = true;

}

void MyPanelInit()
{ // initialize panel layout
  MyPanel.Send(ApplicationName, "Arduino Led Blink" ); 
  MyPanel.Send(Button_3,"$ONOFF" );
  MyPanel.Send(Display_1,"$BOLD");
  MyPanel.Send(Display_2,"$BOLD");
  MyPanel.Send(Display_4,"$NORMAL");
  MyPanel.Send(Led_1,"$OFF");
  MyPanel.Send(ScrollBar_2, "KHz" );
  MyPanel.Send(MaxScrollBar_2, 999);
  MyPanel.Send(ScrollBar_2, KiloHertz);
  MyPanel.Send(ScrollBar_3, "Hz" ); 
  MyPanel.Send(MaxScrollBar_3, 999);
  MyPanel.Send(ScrollBar_3, Hertz);
  MyPanel.Send(ScrollBar_4, "duty%"  );
  MyPanel.Send(MaxScrollBar_4, 100);
  MyPanel.Send(ScrollBar_4, BlinkDuty );
  //MyPanel.Send(DynamicDisplay, true);
  
  MyPanel.Send(PanelConnected);
  MyPanelStaticDisplay();
}

void MyPanelDynamicDisplay()
{
  // Send Dynamic Values; requested by panel every 500 ms.
  //MyPanel.Sendf(Display_3,"+%6ld us   ", TimeLedOn);
  //MyPanel.Sendf(Display_4,"- %6ld us   ", TimeLedOff);
  
}

void MyPanelStaticDisplay()
{
  // Send Static Values; direct result of actions on the panel, requested by panel after button pressed.
  MyPanel.Sendf(Display_1,"%03d %03d Hz", KiloHertz, Hertz  ); // Return Static value for scrollbar only
  MyPanel.Sendf(Display_2,"%03d %% ", BlinkDuty );
  if(Power) MyPanel.Send(Led_1,"$RED"); else MyPanel.Send(Led_1,"$OFF");
}    
     





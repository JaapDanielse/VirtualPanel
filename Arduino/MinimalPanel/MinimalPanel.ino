
#include "VirtualPanel.h"

int Freq = 1000;

void setup() 
{
  Panel.Init(); // init port and protocol
}

void loop() 
{
  static int i=0;
  
  Panel.Receive(); // handle panel data coming in
  //Panel.Send(Display_1,random(0,101));
  //if(Panel.delay(2000)) Panel.Send(Display_3, i++);
  delay(250);
}

void PanelCallback(int event, int type) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      Panel.Send(ApplicationName,"MinimalPanel"); // set the application name
//      Panel.Send(ScrollBar_5,"Five"); // Set button_3 visible showing "One"
      Panel.Send(MaxScrollBar_5,10000); // Set button_3 visible showing "One"
      Panel.Send(ScrollBar_5,100); // Set button_3 visible showing "One"

      
      
      Panel.Send(Button_4,"Two"); // Set Button_4 visible showing "Two"
      Panel.Send(ScrollBar_5, "Three");
      Panel.Send(Button_8,"Four"); // Set Button_4 visible showing "Two"
      Panel.Send(ScrollBar_2,"Five"); // Set Button_4 visible showing "Two"
      Panel.Send(ScrollBar_3,"Six"); // Set Button_4 visible showing "Two"
      Panel.Send(ScrollBar_5,"Seven"); // Set Button_4 visible showing "Two"
      Panel.Send(MonitorInputLabel_1,"Een:"); // send text to Display_2
      Panel.Send(MonitorInputLabel_2,"Twee:"); // send text to Display_2
      Panel.Send(MonitorInputLabel_3,"Drie:"); // send text to Display_2
      Panel.Send(MonitorInputLabel_4,"Vier:"); // send text to Display_2
      Panel.Send(MonitorInputLabel_5,"Vijf:"); // send text to Display_2
      Panel.Send(MonitorInputLabel_6,"Zes:"); // send text to Display_2
      Panel.Send(MonitorInput_1,true); // 
      Panel.Send(MinMonitorInput_1,0); // 
      Panel.Send(MaxMonitorInput_1,10); // 
      Panel.Send(MonitorInput_1,1); // 
      Panel.Send(InfoLabel, "Test");
      Panel.Send(InfoText, "Test Test Test");
      
           
      Panel.Sendf(Display_1,"Freq. %d Hz", Freq); // 
      //Panel.Send(Display_1,"$BIG"); // 
      Panel.Send(Display_2,"Get int 2"); // 
      //Panel.Send(Display_3,"Get int 3"); // 
      Panel.Send(Display_4,"Get int 4"); // 
      
      Panel.Send(GraphDrawLine,_Line(0,0,255,255));

      break;

    case Button_3: // Catch button pressed
      Panel.Send(Display_2,"Button One pressed!"); // send text to displaty_2
      Panel.Send(Beep,_Sound(300,1000));
      break;

    case Button_4: // Catch button pressed  
      Panel.Send(Display_2,"µ ɸ ʩ ֍ א ◀"); // send text to Display_2
      Panel.Send(Beep, 700); // send text to Display_2
      
      break;

    case Button_5: // Catch button pressed  
      Panel.Send(Display_2,"Button Two pressed! µ"); // send text to Display_2
      Panel.Send(Beep); // send text to Display_2
      
      break;

    case Display_1:
      Panel.Send(MinPanelInput_1,0); // 
      Panel.Send(MaxPanelInput_1,10000); // 
      Panel.Send(PanelInputLabel_1,"Frequency (Hz)"); // 
      Panel.Send(PanelInput_1,Freq); // 
      break;

    case Display_2:
      Panel.Send(PanelInputLabel_2,"Get Int 2"); // 
      Panel.Send(PanelInput_2,2); // 
      break;
   
    case Display_3:
      Panel.Send(PanelInputLabel_1,"Get Int 3"); // 
      Panel.Send(PanelInput_1,3); // 
      break;
   
    case Display_4:
      Panel.Send(PanelInputLabel_2,"Get Int 4"); // 
      Panel.Send(PanelInput_2,4); // 
      break;

    case ScrollBar_5:
      Panel.Send(Display_3,Panel.vpr_int); // 
      break;
   
    case PanelInput_1:
      Freq = Panel.vpr_int;
      Panel.Sendf(Display_1,"Freq. %d Hz", Freq); // 
      break;
    
    case MonitorInput_1:
      if(type==vp_void) Panel.Send(MonitorInput_1,1); // 
      if(type==vp_int)  Panel.Sendf(Display_2,"Input %d", Panel.vpr_int); // send text to Display_2
      break;

    case MonitorField_2: Panel.Send(MonitorInput_2,2); break;
    case MonitorInput_2:
      if(type==vp_int)  Panel.Sendf(Display_2,"Input %d", Panel.vpr_int); // send text to Display_2
      break;

    case MonitorField_3: Panel.Send(MonitorInput_3,3); break;
    case MonitorInput_3:
      if(type==vp_int)  Panel.Sendf(Display_2,"Input %d", Panel.vpr_int); // send text to Display_2
      break;

    case MonitorField_4: Panel.Send(MonitorInput_4,4); break;
    case MonitorInput_4:
      if(type==vp_int)  Panel.Sendf(Display_2,"Input %d", Panel.vpr_int); // send text to Display_2
      break;

    case MonitorField_5: if(type==vp_void) Panel.Send(MonitorInput_5,5); break;
    case MonitorInput_5:
      if(type==vp_int)  Panel.Sendf(Display_2,"Input %d", Panel.vpr_int); // send text to Display_2
      break;

    case MonitorField_6: Panel.Send(MonitorInput_6,6); break;
    case MonitorInput_6:
      if(type==vp_int)  Panel.Sendf(Display_2,"Input %d", Panel.vpr_int); // send text to Display_2
      break;

    case GraphClick:
      Panel.Send(Display_2, "Single");
      Panel.Send(GraphDrawPixel, Panel.vpr_uint); // send text to Display_2
      Panel.Send(GraphDrawLine, Panel.vpr_uint); // send text to Display_2
      break;

    case GraphRightClick:
      Panel.Send(Display_2, "Right");
      Panel.Send(Graph,"$CLEAR"); //
      break;

    case GraphDoubleClick:
      Panel.Send(Display_2, "Double");
      Panel.Send(GraphDrawLine); // send text to Display_2
      break;

  }
}


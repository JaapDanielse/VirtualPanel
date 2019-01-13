
#include "VirtualPanel.h"

void setup() 
{
  Panel.Init(); // init port and protocol
}

void loop() 
{
  Panel.Receive(); // handle panel data coming in
  Panel.Send(Display_1,random(0,101));
  delay(250);
}

void PanelCallback(int event, int type) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected message
      Panel.Send(ApplicationName,"MinimalPanel"); // set the application name
      Panel.Send(Button_3,"One"); // Set button_3 visible showing "One"
      Panel.Send(Button_4,"Two"); // Set Button_4 visible showing "Two"
      break;

    case Button_3: // Catch button pressed
      Panel.Send(Display_2,"Button One pressed!"); // send text to displaty_2
      break;

    case Button_4: // Catch button pressed  
      Panel.Send(Display_2,"Button Two pressed!"); // send text to Display_2
      break;
  }
}


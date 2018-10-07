#include "PanelOne.h"

boolean Power = false;
int Value = 0;
int MyScrollValue = 1;

void setup()
{
	Panel.Init(); // init pannel protocol and serial port
}

void loop()
{
	Panel.Receive(); // handle pannel data coming in
  if(Power) Value = random(1,1000) * MyScrollValue; else Value=0;
}

void PanelCallback(int channel, int type) 
{ // callback is called when a message is received from the panel 
  // only channel and type are available as parameters. Pannel data in public vars defined by the library 
  
  switch (channel) 
  {
    case PanelConnected: 
    { // initialize panel layout
      Panel.Send(ApplicationName,"MinimalPanel"); // set the application name
     // Panel.Send(StaticDisplay,true); // enable static display requests
      Panel.Send(DynamicDisplay,true); // enable dynamic display requests
      Panel.Send(Button_3,"$ONOFF"); // make button_3 (low left corner) a power button (power symbol)
      Panel.Send(ScrollBar_2,"mply"); // activate scrollbar 2 and name mply (multiply) 
//      Panel.Send(MaxScrollBar_2, 50); // set scrollbar maximum value 
      Panel.Send(ScrollBar_2, MyScrollValue + 25); // set scrollbar (scaled) actual value
      Panel.Send(Led_1,"$OFF");// activate led_1 (above the power button an set it to off
      break; 
    }

    case Button_3: // (on/off) pressed
    { 
      Power = !Power; // toggle power
      break; 
    }

    case ScrollBar_2: // ScrollBar change
    {
      MyScrollValue = Panel.vpr_int - 25; //copy value and move scale 
      Panel.Sendf(Display_2,"%d", MyScrollValue); // Output value to display directly
      break;
    }

    case DynamicDisplay: // dynamic display request
    {
      Panel.Sendf(Display_1,"%d", Value); // Output value to display
      break;
    }

    case StaticDisplay:
    {
      if (Power)
        Panel.Send(Led_1,"$RED"); // led on (red)
      else  
        Panel.Send(Led_1,"$OFF"); // led off
  //    Panel.Send(ScrollBar_2, MyScrollValue + 25); // set scrollbar (scaled) actual value
      Panel.Sendf(Display_2,"%d", MyScrollValue); // Output value to display directly
      break;   
    }
  }
}



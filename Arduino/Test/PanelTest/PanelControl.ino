//
enum ModeList 
{
  Buttons,
  Sliders,
  Inputs,
  Roling,
  Static,
  Draw,
  Click,
  Clock,
  Endmode
};

int PanelMode = Buttons;


void PanelCallback(vp_channel event) 
{ 
  // PanelCallback is called when a message is received from the panel 
  // only channel and type are passed as parameters. Panel data available as public library vars

   switch (PanelMode)
   {
     case Buttons:
       ButtonsCallback( event); break;

     case Sliders: 
       SlidersCallback( event); break;

     case Inputs:
       InputsCallback( event); break;

     case Draw: 
       DrawCallback( event); break;

     case Roling: 
       RolingCallback( event); break;
       
     case Static: 
       StaticCallback( event); break;
       
     case Click: 
       ClickCallback( event); break;

     case Clock: 
       ClockCallback( event); break;
     
       
     default: 
       break;
   }
}

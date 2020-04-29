//
enum ModeList 
{
  Buttons,
  Sliders,
  Inputs,
  Graphinput,
  Roling,
  Static,
  Draw,
  Click,
  Beeps,
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

     case Beeps: 
       BeepCallback( event); break;
     
     case Clock: 
       ClockCallback( event); break;

     case Graphinput: 
       GraphInputCallback( event); break;
       
     default: 
       break;
   }
}

void WriteInfo()
{

  
  Panel.send(InfoTitle, F("PannelTest"));
  Panel.send(InfoText,  F("Application specific help text"));
  Panel.send(InfoText,  F("Can be changed run-time"));
  Panel.send(InfoText,  F("Hyperlink to documenation pages\n"));
  Panel.send(InfoText,  F("https://github.com/JaapDanielse/VirtualPanel"));

  Infomode = false;
  Monmode = false;
  Graphmode = false;
}

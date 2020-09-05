// VirtualPanel I-StaticGraph example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

int16_t vpos = 128;
float vdiv = 60.0;
float sincount =  6.0;
int16_t SampleCount = 90;
bool freq = false;
float tsincount;


void setup() 
{
  Panel.begin(); // init port and protocol
}

void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
}

void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
     // initialize panel layout
      Panel.send(ApplicationName,"StaticGraph"); // set the application name
      Panel.send(DynamicDisplay, (int16_t)500);     // enable dynamic display request
      Panel.send(GraphGrid, (int16_t)6);
      Panel.send(GraphCaption_1, "Simulated Oscilloscope");
      Panel.send(GraphLabel_1, "$ORANGE");
      Panel.send(GraphLabel_1, "GraphLabel_1");
      Panel.send(GraphValueCount_1,SampleCount);
      Panel.send(GraphValue_1, "$STATIC");
      Panel.send(GraphValue_1, "$ORANGE");
      Panel.send(Graph, (bool)true); 
      break; 

    case DynamicDisplay: // dynamic display request (requested every 500ms)
      Sinus();
      break;

    default: break;
  }
}

void Sinus()
{
   float angle = 0.0;
   byte graphvalue = 0;

   tsincount = sincount +((float)random(0,5)/10.0); // simulate small frequency shifts
    
   for(int j=0; j<SampleCount; j++)
   {
     angle += 360.0/((float)SampleCount/tsincount);
     float RadAngle = (float)(PI/180.0) * angle;
     graphvalue = (byte) constrain((vdiv * sin(RadAngle) + vpos),0,255);
     Panel.send(GraphValue_1,graphvalue);  
   }

}

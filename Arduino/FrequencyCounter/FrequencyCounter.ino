
#include "PanelOneV01.h"

#define FRQPIN 5 // Frequency Measure Pin

void PanelCallback(int chanel, int type); // you need to define the callback function first

VirtualPanel MyPanel(PanelID, PanelCallback, Serial, 115200);

boolean Power = false;
float frequency = 0.0;

//------------------------------------------------------------------------
void setup()
{
  pinMode(FRQPIN, INPUT);  // This is the frequency input
  MyPanel.Init();
  InitFreqCount();
 }

//------------------------------------------------------------------------
void loop() 
{
  MyPanel.Receive();
    
  if (Power)
  { 
    frequency = FrequencyCount(); 
  }
}


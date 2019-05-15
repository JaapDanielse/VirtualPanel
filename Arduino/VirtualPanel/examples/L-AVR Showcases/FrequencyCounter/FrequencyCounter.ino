
#include "VirtualPanel.h"

#define FRQPIN 5 // Frequency Measure Pin

boolean Power = false;
float frequency = 0.0;

//------------------------------------------------------------------------
void setup()
{
  pinMode(FRQPIN, INPUT);  // This is the frequency input
  Panel.Init();
  InitFreqCount();
 }

//------------------------------------------------------------------------
void loop() 
{
  Panel.Receive();
    
  if (Power)
  { 
    frequency = FrequencyCount(); 
  }
}


// VirtualPanel Frequency Counter example/showcase
// Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Frequency-Counter-Example
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

// Does not work on Mega2560 (T1 not connected)

#include "VirtualPanel.h"

#define FRQPIN 5 // Frequency Measure Pin

boolean Power = false;
boolean InfoPanel = false;
float frequency = 0.0;

//------------------------------------------------------------------------
void setup()
{
  pinMode(FRQPIN, INPUT);  // This is the frequency input
  Panel.begin();
  InitFreqCount();
 }

//------------------------------------------------------------------------
void loop() 
{
  Panel.receive();
    
  if (Power)
  { 
    frequency = FrequencyCount(); 
  }
}

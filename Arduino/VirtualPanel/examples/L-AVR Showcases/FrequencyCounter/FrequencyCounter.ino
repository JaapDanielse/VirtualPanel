// VirtualPanel Frequency Counter example/showcase
// Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Frequency-Counter-Example
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel



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


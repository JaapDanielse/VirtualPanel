// VirtualPanel SignalGenerator example/showcase
// Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Logic-Analyzer-Example
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

// application variables
 bool Power = false;
 bool InfoPanel = false;

 unsigned long ClockFrequency = 16000000;
 int Prescaler = 0;
 float ClockTime = 1.0/(float)ClockFrequency;
 float TimeUnit = 0.0;
 unsigned int Top = 0;

 unsigned long Frequency = 0;
 const int KiloHertzRange = 50;
 int KiloHertzSteps = KiloHertzRange;
 int KiloHertz = 0;

 int Hertz = 0;
 unsigned long  HertzStepOffset = 0;
 int HertzStepCount = 999;
 int HertzStep = 0;
 int NextHertzStep = 0;

 int Duty = 50;
 int DutyValue = 0;

//-----------------------------------------------------------------------------------------------
// Initialisation

void setup()
{
  InitSignalGenerator();
	Panel.begin();
}

//-----------------------------------------------------------------------------------------------
// Main Loop

void loop()
{
	Panel.receive();
}

/* end module */

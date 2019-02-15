/*
 VirtualPanel.ino
 Application for the PC VirtualPanel application
 Using the Arduino VirtualPanel library

 V0.1    16-06-2018 JpD
 Original version

*/

#include "VirtualPanel.h"

// application variables
 boolean Power = false;

 int KiloHertz = 0;
 int Hertz = 0;

 unsigned long ClockFrequency = 16000000;
 int Prescaler = 0;
 float TimeUnit = 1.0/(float)ClockFrequency;
 float TopTime = 0.0;
 unsigned int Top = 0;
 int Duty=50;

 unsigned long Frequency = 0;

//-----------------------------------------------------------------------------------------------
// Initialisation

void setup()
{
	Panel.Init();
}

//-----------------------------------------------------------------------------------------------
// Main Loop

void loop()
{
	Panel.Receive();
}

/* end module */

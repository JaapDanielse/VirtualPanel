/*
 VirtualPanel.ino
 Application for the PC VirtualPanel application
 Using the Arduino VirtualPanel library

 V0.1    16-06-2018 JpD
 Original version

*/

#include "VirtualPanel.h"

#define LedPin 13 //
#define SignalOutputPIN 9 //


// application variables

 boolean CommandReceived = true;
 boolean Power = false;

 int KiloHertz = 0;
 int Hertz = 0;

 unsigned long BlinkFrequency = 0;
 int BlinkDuty = 50;
 
 unsigned long TimeLedOn = 0;
 unsigned long TimeLedOff = 0;
 

//-----------------------------------------------------------------------------------------------
// Initialisation

void setup()
{
	Panel.Init();
  pinMode( LedPin, OUTPUT );
  pinMode(SignalOutputPIN, OUTPUT);       // Pin 9 - Voltage-PWM  to integrator (TC-1 - OCR1A)
  //InitSignalGenerator();
}

//-----------------------------------------------------------------------------------------------
// Main Loop

void loop()
{

	Panel.Receive();


  if(Power && BlinkFrequency > 0 )
  { // Power is on: Blink the led
    BlinkLed();
  }

}


void BlinkLed()
{
  unsigned long LedTimer = 0;

  while(1)
  {
     LedTimer = micros() + (TimeLedOff);
     PORTB = (0<<PB5);   
     if(Serial.available()) return;
     while(LedTimer >= micros());
     PORTB = (1<<PB5);   
     LedTimer = micros() + ( TimeLedOn);
     while(LedTimer >= micros());
  }
}

/* end module */

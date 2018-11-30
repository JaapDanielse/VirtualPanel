/*
 VirtualPanel.ino
 Application for the PC VirtualPanel application
 Using the Arduino VirtualPanel library

 V0.1    16-06-2018 JpD
 Original version

*/

#include "PanelOneV01.h"

#define LedPin 13 //
#define SignalOutputPIN 9 //


void PanelCallback(int chanel, int type); // you need to define the callback function first

VirtualPanel MyPanel(PanelID, PanelCallback, Serial, 115200);

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
	MyPanel.Init();
  pinMode( LedPin, OUTPUT );
  pinMode(SignalOutputPIN, OUTPUT);       // Pin 9 - Voltage-PWM  to integrator (TC-1 - OCR1A)
  InitSignalGenerator();
}

//-----------------------------------------------------------------------------------------------
// Main Loop

void loop()
{

	MyPanel.Receive();

  if (CommandReceived)
  { 
    // A panel event came in: recalulate
    BlinkFrequency = (KiloHertz*1000) + Hertz;
    TimeLedOn  = ((1000000.0/(float)BlinkFrequency)/100.0)*BlinkDuty;
    TimeLedOff = ((1000000.0/(float)BlinkFrequency)/100.0)*(100-BlinkDuty);     
    CommandReceived = false;
  }
  
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

/*  
  static int Blinkmode = 0;
  switch (Blinkmode)
  {
    case 0: // setup timer and switch led on
    { 
      LedTimer=millis()+TimeLedOn;
      Blinkmode = 1;
      break;      
    }
    case 1: // wait for timer, set timer and switch led off
    {
      if(LedTimer < millis()) 
      {
        LedTimer=millis()+TimeLedOff;
        digitalWrite(LedPin,LOW);
        Blinkmode = 2;
      }
      break;      
    }
    case 2: // wait for timer
    {
      if(LedTimer < millis()) 
      {
        Blinkmode = 0;
      }
      break;
    }
  }
  */
  
/* end module */

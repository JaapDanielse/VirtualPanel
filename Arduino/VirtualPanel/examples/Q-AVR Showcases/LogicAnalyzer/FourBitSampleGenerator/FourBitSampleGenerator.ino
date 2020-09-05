// VirtualPanel PatternGenerator example - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

enum Patterns
{
  Count,
  ZigZag,
  Chequered,
  Noise 
}; 

const int DelayTimeCount = 13;
const int DelayTimeValues[] = { 1,2,5,10,20,50,100,200,500,1000,2000,5000,10000 };
      int DelayTimeIdx = 9;
      int DelayTime = DelayTimeValues[DelayTimeIdx];

Patterns PatternSelect = Count;

bool Power = false;
bool ShowInfo = false;

void setup() 
{
  Panel.begin(); // init port and protocol
  DDRB = B00001111; // Set data direction for D8,D9,D10,D11 to write.
}

void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)

  if(Power)
  {
    switch( PatternSelect)
    {
      case Count:     GenCount();     break;
      case ZigZag:    GenZigZag();    break;
      case Chequered: GenChequered(); break;
      case Noise:     GenNoise();     break;
    }
  }
}


void GenCount()
{
  while(!Serial.available())
  {
    for (byte i=0; i<15; i++)
    {
       PORTB = i;
       delayMicroseconds(DelayTime);
    }
    for (byte i=15; i>0; i--)
    {
       PORTB = i;
       delayMicroseconds(DelayTime);
    }
  }
}


void GenZigZag()
{
  while(!Serial.available())
  {
    PORTB = B00000001;
    delayMicroseconds(DelayTime);
    PORTB = B00000010;
    delayMicroseconds(DelayTime);
    PORTB = B00000100;
    delayMicroseconds(DelayTime);
    PORTB = B00001000;
    delayMicroseconds(DelayTime);
    PORTB = B00000100;
    delayMicroseconds(DelayTime);
    PORTB = B00000010;
    delayMicroseconds(DelayTime);
  }
}


void GenChequered()
{
  while(!Serial.available())
  {
    PORTB = B00000101;
    delayMicroseconds(DelayTime);
    PORTB = B00001010;
    delayMicroseconds(DelayTime);
  }
}


void GenNoise()
{
  while(!Serial.available())
  {
    PORTB = random(0,15);
    delayMicroseconds(DelayTime);
  }
}


void PanelCallback(vp_channel event) 
{ 
  switch (event) 
  {
    case PanelConnected: InitPanel(); break;
    case Button_4: Power = !Power; break;
    case Button_5: PatternSelect = Count; break;
    case Button_6: PatternSelect = ZigZag; break;
    case Button_7: PatternSelect = Chequered; break;
    case Button_8: PatternSelect = Noise; break;
    case Button_9:  if(++DelayTimeIdx >= DelayTimeCount) DelayTimeIdx--;  break;
    case Button_10: if(--DelayTimeIdx < 0 ) DelayTimeIdx=0;  break;
    case Button_14: ShowInfo = !ShowInfo;  break;
    default: break;
  }
  StaticDisplay();
}


void StaticDisplay()
{
  Panel.send(Led_2,"$OFF"); 
  Panel.send(Led_3,"$OFF");
  Panel.send(Led_4,"$OFF");
  Panel.send(Led_5,"$OFF");
  Panel.send(Led_6,"$OFF");

  if (Power) Panel.send(Led_2,"$RED");
  if (PatternSelect == Count)  Panel.send(Led_3,"$GREEN");
  if (PatternSelect == ZigZag) Panel.send(Led_4,"$GREEN");
  if (PatternSelect == Chequered) Panel.send(Led_5,"$GREEN");
  if (PatternSelect == Noise)  Panel.send(Led_6,"$GREEN");

  DelayTime = DelayTimeValues[DelayTimeIdx];

  if (ShowInfo) 
    Panel.send(Info,true); 
  else 
    Panel.send(Info,false);

  Panel.sendf( Display_1, "Step delay %d µS",  DelayTime);
}


void InitPanel()
{

  Panel.send(ApplicationName,"FourBit-SampleGenerator"); // set the application name
  Panel.send(Button_4,"output");
  Panel.send(Button_5,"count");
  Panel.send(Button_6,"zig-zag");
  Panel.send(Button_7,"chequered");
  Panel.send(Button_8,"noise");
  Panel.send(Button_9, "▲\ndelay"); 
  Panel.send(Button_10,"delay\n▼"); // Button_3 visible and set text "on/off"
  Panel.send(Button_14,"info");

  Panel.send(InfoTitle, F("FourBit-SampleGenerator"));
  Panel.send(InfoText,  F("Geneterates a 4-bit sample pattern "));
  Panel.send(InfoText,  F("Output on D8, D9, D10, D11 (Mega 50-53)\n"));
  Panel.send(InfoText,  F("Different patterns can be selected\n"));
  Panel.send(InfoText,  F("Documentation:"));
  Panel.send(InfoText,  F("https://github.com/JaapDanielse/VirtualPanel/wiki/Logic-Analyzer-Example"));
}

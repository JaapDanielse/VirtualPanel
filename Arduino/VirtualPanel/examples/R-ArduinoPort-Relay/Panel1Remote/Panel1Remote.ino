
// VirtualPanel/ArduinoPort PanelRelay Example
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel
// Implements one panel displaying data from multiple (slave) Arduino's


#include <SoftwareSerial.h>
#include <ArduinoPort.h>
#include <VirtualPanel.h>

enum Soft_Channel // event/channel list for slave Arduino communication
{
  DataRequest,
  SetValue_1,
  SetValue_2,
  CalcValue,
  EndData
};


SoftwareSerial mySerial(10, 11); // RX, TX
void SoftPortCallback(int event);
ArduinoPort SoftPort =  ArduinoPort("[Soft1]", SoftPortCallback, mySerial);

int RemoteValue1 = 0;
int RemoteValue2 = 0;
bool SoftPortPrio = false;
unsigned long SerialTimeout = 0;

void setup() 
{
  Panel.begin(); // Open VirtualPanel communications
  mySerial.begin(9600); // set the data rate for the SoftwareSerial port (you cannot use SoftPort.begin())
}

// -- main loop
void loop() 
{  // do not delay!
  Panel.receive();
  mySerial.listen();
  SerialTimeout = millis()+50;
  while(SoftPortPrio){ 
    SoftPort.receive(); 
    if(millis()>SerialTimeout){ 
      SoftPortPrio=false; 
      break;
    }
  }
  SoftPort.receive();
}


// -- Catch SoftPort events
void SoftPortCallback(int event)
{ 
  switch (event) 
  {
    case SetValue_1:
      RemoteValue1 = SoftPort.vpr_int;
      Panel.sendf(Display_3, "Value 1: %d", RemoteValue1);
      break;

    case SetValue_2:
      RemoteValue2 = SoftPort.vpr_int;
      Panel.sendf(Display_1, "Value 2: %d", RemoteValue2);
      break;

    case CalcValue:
      Panel.sendf(Display_2, "Calc %04d", SoftPort.vpr_int);
      break;

    case EndData:
      SoftPortPrio = false;
      break;

  }  
}

// -- VirtualPanel Events
void PanelCallback(vp_channel event)
{
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.send(ApplicationName,"PanelRelay"); // set the application name
      Panel.send(Button_9, "△\nV1"); 
      Panel.send(Button_10,"V1\n▽"); 
      Panel.send(Button_12,"△\nV2");
      Panel.send(Button_13,"V2\n▽");
      Panel.send(DynamicDisplay, 250);
      break;

    case Button_9: // Catch button pressed
      SoftPort.send(SetValue_1, ++RemoteValue1);
      break;

    case Button_10: // Catch button pressed
      SoftPort.send(SetValue_1, --RemoteValue1);
      break;

    case Button_12: // Catch button pressed
      SoftPort.send(SetValue_2, ++RemoteValue2);
      break;

    case Button_13: // Catch button pressed
      SoftPort.send(SetValue_2, --RemoteValue2);
      break;

    case DynamicDisplay:
      SoftPort.send(DataRequest);
      SoftPortPrio = true;
      break;
    
    default: break;
  }
}

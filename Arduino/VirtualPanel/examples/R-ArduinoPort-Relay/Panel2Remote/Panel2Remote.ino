
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

#define RemoteCount 2 //

int RemoteSelect = 1;
int RemoteValue1 = 0;
int RemoteValue2 = 0;
unsigned long SerialTimeout = 0;

SoftwareSerial SoftSerial_1 ( 8,  9); // RX, TX
void SoftPortCallback_1 (int event);
ArduinoPort SoftPort_1 =  ArduinoPort("[Soft1]", SoftPortCallback_1, SoftSerial_1);
int Remote_1_Value1 = 0;
int Remote_1_Value2 = 0;
int Remote_1_Calc   = 0;
bool SoftPortPrio_1 = false;

SoftwareSerial SoftSerial_2(10, 11); // RX, TX
void SoftPortCallback_2 (int event);
ArduinoPort SoftPort_2 =  ArduinoPort("[Soft2]", SoftPortCallback_2, SoftSerial_2);
int Remote_2_Value1 = 0;
int Remote_2_Value2 = 0;
int Remote_2_Calc   = 0;
bool SoftPortPrio_2 = false;

void setup() 
{
  Panel.begin(); // Open VirtualPanel communications 

  // set the data rate for the SoftwareSerial ports
  SoftSerial_1.begin(9600); // you cannot use SoftPort_1.begin()
  SoftSerial_2.begin(9600); // you cannot use SoftPort_2.begin()
}

// -- main loop
void loop() 
{  // do not delay!
  Panel.receive();
  
  SoftSerial_1.listen();
  SerialTimeout = millis()+50;
  while(SoftPortPrio_1){ SoftPort_1.receive(); if(millis()>SerialTimeout){SoftPortPrio_1=false; break;}}
  SoftPort_1.receive();

  SoftSerial_2.listen();
  SerialTimeout = millis()+50;
  while(SoftPortPrio_2){ SoftPort_2.receive(); if(millis()>SerialTimeout){SoftPortPrio_2=false; break;}}
  SoftPort_2.receive();

}


// -- Catch SoftPort events
void SoftPortCallback_1(int event)
{ 
  switch (event) 
  {
    case SetValue_1:
      Remote_1_Value1 = SoftPort_1.vpr_int;
      break;

    case SetValue_2:
      Remote_1_Value2 = SoftPort_1.vpr_int;
      break;

    case CalcValue:
      Remote_1_Calc = SoftPort_1.vpr_int;
      break;

    case EndData:
      SoftPortPrio_1 = false;
      break;

  }  
}


// -- Catch SoftPort events
void SoftPortCallback_2(int event)
{ 
  switch (event) 
  {
    case SetValue_1:
      Remote_2_Value1 = SoftPort_2.vpr_int;
      break;

    case SetValue_2:
      Remote_2_Value2 = SoftPort_2.vpr_int;
      break;

    case CalcValue:
      Remote_2_Calc = SoftPort_2.vpr_int;
      break;

    case EndData:
      SoftPortPrio_2 = false;
      break;

  }  
}
// -- VirtualPanel Events
void PanelCallback(vp_channel event)
{
  static int RemoteData = 1;
  
  switch (event) 
  {
    case PanelConnected: // receive panel connected event
      Panel.send(ApplicationName,"PanelRelay"); // set the application name
      Panel.send(Display_1,"$SMALL"); 
      Panel.send(Display_2,"$SMALL"); 
      Panel.send(Button_3, "rem.\nsel.");
      Panel.sendf(Led_10, "$GREEN");
      Panel.sendf(Led_11, "$OFF"); 
      Panel.send(Button_9, "△\nV1"); 
      Panel.send(Button_10,"V1\n▽"); 
      Panel.send(Button_12,"△\nV2");
      Panel.send(Button_13,"V2\n▽");
      Panel.send(DynamicDisplay, 125);
      break;

    case Button_3: // Catch button pressed
      SwitchRemote();
      break;

    case Button_9: // Catch button pressed
      sendRemote(SetValue_1, ++RemoteValue1);
      break;

    case Button_10: // Catch button pressed
      sendRemote(SetValue_1, --RemoteValue1);
      break;

    case Button_12: // Catch button pressed
      sendRemote(SetValue_2, ++RemoteValue2);
      break;

    case Button_13: // Catch button pressed
      sendRemote(SetValue_2, --RemoteValue2);
      break;

    case DynamicDisplay: // Times the remote port communication

      Panel.sendf(Display_1, "R1 - V1:%02d V2:%02d C:%03d", Remote_1_Value1,  Remote_1_Value2, Remote_1_Calc);
      Panel.sendf(Display_2, "R2 - V1:%02d V2:%02d C:%03d", Remote_2_Value1,  Remote_2_Value2, Remote_2_Calc);
   
      if(RemoteData == 1)
      {  
        SoftPortPrio_1 = true;
        SoftPort_1.send(DataRequest);
      }
      else if (RemoteData == 2)
      {
        SoftPortPrio_2 = true;
        SoftPort_2.send(DataRequest);
      }
      if(++RemoteData > RemoteCount) RemoteData = 1;
      break;
      
    default: break;
  }
}


void SwitchRemote()
{
  if(++RemoteSelect > RemoteCount) RemoteSelect = 1;
  if( RemoteSelect == 1)
  {
    RemoteValue1 = Remote_1_Value1;
    RemoteValue2 = Remote_1_Value2;
    Panel.sendf(Led_10, "$GREEN");
    Panel.sendf(Led_11, "$OFF");
  }
  if( RemoteSelect == 2)
  {
    RemoteValue1 = Remote_2_Value1;
    RemoteValue2 = Remote_2_Value2;
    Panel.sendf(Led_10, "$OFF");
    Panel.sendf(Led_11, "$GREEN");
  }
  
}


void sendRemote(int Channel, int Value)
{
  if(RemoteSelect == 1)
  {
    SoftPort_1.send(Channel, Value);
  }
  else if (RemoteSelect == 2)
  {
    SoftPort_2.send(Channel, Value);
  }
  
}

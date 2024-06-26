//  
//

#include <SoftwareSerial.h>
#include <VirtualPanel.h>

enum Soft_channel : uint8_t // event/channel list 
{
  DataRequest,
  SetValue_1,
  SetValue_2,
  CalcValue,
  EndData
};

SoftwareSerial mySerial(10, 11); // RX, TX

void SoftPortCallback(uint8_t event);

ArduinoPort SoftPort =  ArduinoPort("[Soft1]", SoftPortCallback, mySerial);

int Value1 = 0;
int Value2 = 0;
int RandValue = 0;

void setup() 
{
  Serial.begin(115200); // SerialBaudrate
  mySerial.begin(9600); // SoftPort baudrate (you cannot use SoftPort.begin())
}

void loop() 
{ // do not delay!
  SoftPort.receive(); 
  RandValue = random(1,100);

}

void SoftPortCallback(uint8_t event)
{
  switch (event) 
  {
    case DataRequest:
      SoftPort.send(SetValue_1, Value1);
      SoftPort.send(SetValue_2, Value2);
      SoftPort.send(CalcValue, (Value1+Value2) * RandValue); 
      SoftPort.send(EndData); 
      break;

    case SetValue_1:
      Value1 = SoftPort.vpr_int;
      break;

    case SetValue_2:
      Value2 = SoftPort.vpr_int;
      break;
  }  
}

void PanelCallback(vp_channel){}

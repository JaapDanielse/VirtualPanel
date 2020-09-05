// VirtualPanel Logic Analizer example/showcase
// Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Logic-Analyzer-Example
// MIT Licence - Copyright (c) 2019 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

#define SampleBufferSize 1000 //
#define SampleWindow 120 //

#define SignalHeight 20 //
#define ChanelHeight 51 //
#define SignalMargin 15 //


byte SampleBuffer[SampleBufferSize + 1];
int  SampleBufferIdx = 0;

const int SampleBufSizeCount = 5; // number of VDiv values
const int SampleBufSizeValues[] =
{
  SampleBufferSize / 20, //   50 /  100
  SampleBufferSize / 10, //  100 /  200
  SampleBufferSize / 4, //  250 /  500
  SampleBufferSize / 2, //  500 / 1000
  SampleBufferSize     // 1000 / 2000
};
int SampleBufSizeIdx = 4; // current index
int SampleBufSize = SampleBufSizeValues[SampleBufSizeIdx];

const int SampleSpeedCount = 12; // number of VDiv values
const int SampleSpeedValues[] = { 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };
int SampleSpeedIdx = 5; // current index
int SampleSpeed = SampleSpeedValues[SampleSpeedIdx];

int WindowPosition = 0;
int X1Position = 0;
int X2Position = 0;
bool Measure = false;

bool Trigger = false;
bool TRizing = true;
byte TriggerBit  = 0;

bool InfoPanel = false;

//---------------------------------------------------------------------------------
void setup()
{
  Panel.begin(); // init port and protocol
  SampleInit();
}


//---------------------------------------------------------------------------------
void loop()
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
}

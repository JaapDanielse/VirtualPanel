#include "VirtualPanel.h"

#define MaxSampleValues 500 //
#define MaxGraphValues 120 //
#define TriggerStart 50 //
#define DefaultVdiv 1.0 //

byte SampleValues[MaxSampleValues+10]; // Sample buffer
int  SampleIndex = 0; // Sample buffer index
bool Sampling = false; // True if sample run underway
bool SampleReady = false; // True if sample run ready
unsigned long SampleCount = 0; // number of samples during sample run
unsigned long ScanCount = 0; // sample run count
int  vpos = 0; // vertical position (-255 to 255)
float vdiv = DefaultVdiv; // voltage per divistion
int  trig = 110;
int  triggershift = 0;


const long usDivSelect[] = {100,200,400,1000,2000,4000,10000,20000,40000,100000,200000,400000,1000000,2000000,4000000,10000000};
      int usDivSelIdx = 9;
const int VDivSelect[]  = {20000, 10000, 5000, 2000, 1000, 500, 200, 100};
      int VDivSelIdx = 0;
      
//-----------------------------------------------------------------------------------------------
void setup()
{
	Panel.Init(); // init pannel protocol and serial port
  SamplerInit(); //
}

//-----------------------------------------------------------------------------------------------
void loop()
{
	Panel.Receive(); // handle pannel data coming in
  Sampler();
}



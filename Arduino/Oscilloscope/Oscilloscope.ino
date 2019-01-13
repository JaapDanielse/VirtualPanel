#include "VirtualPanel.h"

#define MaxSampleValues 500 //
#define MaxGraphValues 120 //
#define TriggerStart 50 //
#define DefaultVdiv 1.0 //

byte SampleValues[MaxSampleValues+1]; // Sample buffer
int  SampleIndex = 0; // Sample buffer index
bool Sampling = false; // True if sample run underway
bool SampleReady = false; // True if sample run ready
unsigned long SampleCount = 0; // number of samples during sample run
unsigned long ScanCount = 0; // sample run count
int  StepSize = 8; 
int  vpos = 0; // vertical position (-255 to 255)
float vdiv = DefaultVdiv; // voltage per divistion
int  trig = 110;
int  triggershift = 0;
const int msDivSelect[] = {1000,500,200,100,50,20,10,5,2,1};
      int msDivSelIdx = 0;
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



#include "VirtualPanel.h"

#define MaxSampleValues 800 //
#define MaxGraphValues 120 //
#define TriggerStart 50 //
#define DefaultVdiv 1.0 //

byte SampleValues[MaxSampleValues+1]; // Sample buffer
int  SampleIndex = 0; // Sample buffer index
bool Sampling = false; // True if sample run underway
bool SampleReady = false; // True if sample run ready
unsigned long SampleCount = 0; // number of samples during sample run
unsigned long ScanCount = 0; // sample run count
int  StepSize = 10; 
int  vpos = 0; // vertical position (-255 to 255)
float vdiv = DefaultVdiv; // voltage per divistion
int  trig = 110;
int  triggershift = 0;
const int msDivSelect[] = { 1,2,5,10,20,50,100,200,500,1000,2000,5000};
      int msDivSelIdx = 4;

const int VDivSelect[]  = {20, 10, 5, 2, 1}; 
      int VDivSelIdx = 1;
      
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



// VirtualPanel Oscilloscope example/showcase
// Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Oscilloscope-Example
// MIT Licence - Copyright (c) 2020 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel

#include "VirtualPanel.h"

#define SampleValuesSize 500 // Sample Buffer Size
#define MaxGraphValues  120 // Maximum number of display values
#define GridSize 5 // Vertical grid section (horizontal 6)

const int  AttenuatorMultiplier = 1; // hardware multiplier (1 = none) 
const int  ACFilter = 0; // hardware AC filter (0=none)

float VCCValue = 5.0;

byte SampleValues[SampleValuesSize+1]; // Sample buffer
int  MaxSampleValues = SampleValuesSize; // Buffersize used
int  SampleIndex = 0; // Sample buffer index
int  GraphValues = MaxGraphValues; // Nuber of values in display window

bool Sampling = false; // True if sample run underway
bool SampleReady = false; // True if sample run ready

unsigned long SampleCount = 0; // number of samples during sample run
unsigned long ScanCount = 0; // sample run count

int vpos = 0; // vertical position (-255 to 255)
int triggershift = 0; // horizontal (X) position relative to trigger point

int TriggerLine =127; // vertical position of the trigger line
float TriggerLevel = 2.5; // trigerlevel in volts
int   TriggerValue = TriggerLevel * (255.0 / (float)GridSize); // AD trigger level
bool SingleEventTrig = false;

const int msDivSelCount = 11; // number of msDiv values
const int msDivSelect[] = {1,2,5,10,20,50,100,200,500,1000,2000}; // msDiv value list
      int msDivSelIdx = 3; // current index (defalut=3, 10 mS/Div
      int msDiv = msDivSelect[msDivSelIdx];  // the current value used for display and sample skip

const int   VDivSelCount = 5; // number of VDiv values
const float VDivSelect[]  = {0.1, 0.2, 0.5, 1, 2};  // VDiv value list
      int   VDivSelIdx = 3; // current index (default=3, 1 V/Div)
      float VDiv = VDivSelect[VDivSelIdx]; // current value 

bool RunState = true; // running status
bool TriggerEdgeRizing = true; // trigger rizing /falling edge

bool VMeasure = false; // measure Volts
bool TMeasure = false; // measure Time
unsigned int LeftClickPos = 0; // measurement position 1
unsigned int RightClickPos = 0; // measurement position 2

float AttenuatorValue = 1.0; // multiplier value (default 1x)
int   VDecimalCount = 2; // number of decimals to display depending on attenuator setting
bool  ACSelect = false;

//-----------------------------------------------------------------------------------------------
void setup()
{
	Panel.begin();  // init pannel protocol and serial port
  SamplerInit(); // Setup AD conversion
}

//-----------------------------------------------------------------------------------------------
void loop()
{
	Panel.receive(); // handle pannel data coming in
  Sampler(); // do sampling
}

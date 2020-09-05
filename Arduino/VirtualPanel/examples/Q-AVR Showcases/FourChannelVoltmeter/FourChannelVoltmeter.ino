// VirtualPanel FourChanelVoltmeter/Logger example/showcase
// Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/4-Channel-Voltmeter-Example
// MIT Licence - Copyright (c) 2020 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel


// 
#include "VirtualPanel.h"

#define CH1 A0 //
#define CH2 A1 //
#define CH3 A2 //
#define CH4 A3 //

bool MonitorMode = false;
bool GraphMode = true;
bool InfoMode = false;
bool LoggerMode = false;
bool Recording = false;
bool LogFileOpen = false;
bool UseSketchPath = false; // set to "true" to use sketch directory as default path
bool Calibrated = false;

const float SlopeCorrection  = 0.998336;  // linear correction function a (y=ax+b) where x = v-measured and y=vdisplayed
const float OffsetCorrection = 0.012479;  // linear correction function b

//const float SlopeCorrection  = 1.0;  // use thes lines when recalibrating slope
//const float OffsetCorrection = 0.0;  // 

float BandGapVolts = 1.1;

int GraphRange = 0;
int MeasureInterval = 250;

float DigitCalcValue = 100.0;
int   Digits = 2;

const char * ChannelColor[] = {"$YELLOW", "$GREEN", "$ORANGE", "$PURPLE"}; 
bool ChannelOn[4] = {true, true, true, true};
int  ChannelAlarm[4] = {0,0,0,0};
bool AlarmLine[4] = {false, false, false, false};
bool BeepAlarm[4]={false, false, false, false};
bool Sound = false;

float VCCMeasured  = 0.0; 
float VMaxMeasurable = 0.0;
int   VMax = 0;

float Scalefactor = 0.0;
float RealVoltage[4] = {0.0, 0.0, 0.0, 0.0};
float Attenuation[4] = {1.0, 1.0, 1.0, 1.0};
float UpperAlarm[4]  = {0.0, 0.0, 0.0, 0.0};
float LowerAlarm[4]  = {0.0, 0.0, 0.0, 0.0};

const char APPID[] = "4CHVML-V1";

char CHName[4][17] = {"CH1","CH2","CH3","CH4"};

//---------------------------------------------------------------
void setup() 
{
  ReadSettings();
  VCCMeasured = VCCVoltage(BandGapVolts);
  CalculateScalefactors();
  InitSampler();
  Panel.begin(); // init port and protocol
}

//---------------------------------------------------------------
void loop() 
{
  Panel.receive(); // handle panel events form the panel (must be in the loop)
  Sampler();
}

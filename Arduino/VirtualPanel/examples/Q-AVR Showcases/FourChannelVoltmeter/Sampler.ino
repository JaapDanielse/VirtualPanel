// Sampler 
// Reads the Analog ports 

#define SAMPLECOUNT 32 //

float ScaledVoltage[4] = {0, 0, 0, 0};
bool  NewValues = false;
  
//---------------------------------------------------------------
void InitSampler()
{
  pinMode(CH1, INPUT); 
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  InitADConverter();
}

//---------------------------------------------------------------
void InitADConverter()
{ 
  ADMUX  = (1 << REFS0) | (0 << REFS1) | (0 << MUX1)| (0 << MUX0); // MUX 011 = Voltage A3 (REFS0 = 1 REFS1 = 0) VCC=ref 
  ADCSRB = 0; //clear ADCSRB register
  ADCSRA = (1 << ADPS0) | (1 << ADPS2) | (1 << ADIE) | (1 << ADEN) | (1 << ADSC); 
}

//---------------------------------------------------------------
ISR(ADC_vect) //runs when new ADC value is available
{
  static unsigned long TotaScaledVoltage[4] = {0, 0, 0, 0};
  static int ChannelSelect = 0;
  static int TotalVoltageCount = 0;

  switch (ChannelSelect)
  {
    case 0: // A0 (MUX 000)
      TotaScaledVoltage[0] += (ADC << 2); //save measurement as 4096 sample
      bitSet  (ADMUX,MUX0); // set for A1 (MUX 001)
      bitClear(ADMUX,MUX1);
      ChannelSelect = 1; // flag next measurement Voltage
      break;

    case 1: // A1 (MUX 001)
      TotaScaledVoltage[1] += (ADC << 2); //save measurement as 4096 sample
      bitClear(ADMUX,MUX0); // set for A2 (MUX 010)
      bitSet  (ADMUX,MUX1);
      ChannelSelect = 2; // flag next measurement Voltage
      break;

    case 2: // A2 (MUX 010)
      TotaScaledVoltage[2] += (ADC << 2); //save measurement as 4096 sample
      bitSet  (ADMUX,MUX0); // set for A3 (MUX 011)
      bitSet  (ADMUX,MUX1);
      ChannelSelect = 3; // flag next measurement Voltage
      break;
    
    case 3: //A3 (MUX 011)
      TotaScaledVoltage[3] += (ADC << 2); //save measurement as 4096 sample
      bitClear(ADMUX,MUX0); // set for A0 (MUX 000)
      bitClear(ADMUX,MUX1);
      ChannelSelect = 0; // flag next measurement Voltage
      TotalVoltageCount++;
      break;
  }
  
  if (TotalVoltageCount == SAMPLECOUNT)
  {
    for(int i=0; i<4; i++)
    {
      ScaledVoltage[i] = (float)TotaScaledVoltage[i] / (float)TotalVoltageCount;
      TotaScaledVoltage[i] = 0;
    }
    TotalVoltageCount = 0;
    NewValues = true;
  }

  bitSet( ADCSRA,ADSC);  // start next ADC measurement  
}


//---------------------------------------------------------------
void Sampler()
{
  float AnalogValue[4];

  if(NewValues)
  {
    for( int i=0; i<4; i++)
    {
      if(ChannelOn[i])
      {
        AnalogValue[i] = (((ScaledVoltage[i] * Scalefactor) *  SlopeCorrection) + OffsetCorrection) * Attenuation[i];
        AnalogValue[i] =  (float)round(AnalogValue[i] * DigitCalcValue) / DigitCalcValue;
      }
      else
      {  AnalogValue[i] = 0.0; }
      RealVoltage[i] = SetAlarm(i, AnalogValue[i]);
    }
    NewValues = false;
  }
}

//---------------------------------------------------------------
float SetAlarm(int ChannelId, float AnalogValue)
{
   if (UpperAlarm[ChannelId]>0 && AnalogValue > UpperAlarm[ChannelId])
   {
      ChannelAlarm[ChannelId] = 1;
      if (RealVoltage[ChannelId] > AnalogValue && ChannelAlarm[ChannelId] == 0) return RealVoltage[ChannelId];
   }
   else if (LowerAlarm[ChannelId]>0 && AnalogValue < LowerAlarm[ChannelId])
   {
      ChannelAlarm[ChannelId] = -1;
      if (RealVoltage[ChannelId] < AnalogValue && ChannelAlarm[ChannelId] == 0) return RealVoltage[ChannelId];
   }
   else
   {
     ChannelAlarm[ChannelId] = 0;
   }
   return AnalogValue;
}


//---------------------------------------------------------------
void CalculateScalefactors()
{
  float MaxAttenuation = 0.0;
  
  Scalefactor = VCCMeasured / 4095.0;
  Panel.sendf(MonitorLog, F("Scalefactor %s"), _FString(Scalefactor,6,4));
  
  for(int i=0; i<4; i++)
  {
    if( Attenuation[i] > MaxAttenuation)
    {
      MaxAttenuation =  Attenuation[i];
    }
    Panel.sendf(MonitorLog, F("Max Voltage CH%d %s"), i+1, _FString((Attenuation[i] * VCCMeasured),6,4));
  }
  VMaxMeasurable = VCCMeasured * MaxAttenuation;
  VMax = (int)((VMaxMeasurable + 0.5)*100.0);
}

// Sampler Module

#define port_AD_Scope  16 // Pin - AD input current


//-----------------------------------------------------------------------------------------------
void SamplerInit()
{
  pinMode(port_AD_Scope, INPUT); // set AD port as input
  InitADConversion(); // setup for AD conversion
}


//-----------------------------------------------------------------------------------------------
void Sampler()
{
  static unsigned long SampleTime = 0; 

// Single event mode end of buffer but event has not yet occured
  if (TriggerMode == Single && SampleReady && !SingleEventTrig)
  {
    SampleReady = false; // Set for next sample run
    Sampling = false;
    SampleValues[0] = 0;
  }
  
// Start a new sample run
  if ( !SampleReady && !Sampling && RunState)
  { // start a new scan
    TriggerValue = TriggerLevel * (255.0 / (float)GridSize); // calculate trigger value from level
    SampleIndex = 0; // reset Sample index   
    SampleCount = 0; // reset Sample counter
    Sampling = true; // flag for sampling
    if (TriggerMode == Single) SampleIndex = 1;
    bitSet( ADCSRA,ADSC);  // start next ADC measurement (samples will be caugt in ISR(ADC_vect) routine
    SampleTime = micros(); // register start time
  }

//-- Sample is in the buffer: Analyse and output
  if (SampleReady && !(TriggerMode == Single && !SingleEventTrig))
  { // analyze sample buffer
    
    SampleTime = micros() - SampleTime;    

    unsigned int SampleMax  = 0; // Maximum Sample value in sample buffer
    unsigned int SampleMin  = 255; // Minimum Sample value in sample buffer
    unsigned int TriggerCount = 0; // Number of trigger points in sample buffer
    unsigned int TriggerPos = 0; // Position of the (central) trigger 
    unsigned int FirstTriggerPos = 0; // First trigger position ( for freq. calc.)
    unsigned int LastTriggerPos = 0; // Last trigger position (for freq. calc.)
    char  outstr1[10]; // float conversion buffer 1
    char  outstr2[10]; // float conversion buffer 2
    char  outstr3[10]; // float conversion buffer 3
    float tmpfloat; // temp float var
    float Period; // Signal period 
    float Frequency; // Signal Frequency calculated from trigger distances
    int   WindowStart = 0; // start position of the view window in the sample buffer

    TriggerValue = TriggerLevel * (255.0 / (float)GridSize); // calculate trigger value from level

    Panel.send(Led_12, F("$ORANGE")); // frame indicator on
    delay(12); // Support FTDI FT232R chips (else buffered USB output does not blink led)
    
    SetVertPos(0, false); // remove position line (if there)
    float TimePerSample = (float)SampleTime/(float)(long)(MaxSampleValues+1); // calculate time per sample

    // Output timing to monitor 
    Panel.sendf(MonitorField_1,"Samples %ld", ((long)(MaxSampleValues+1)*msDiv)); // output to monitor 
    Panel.sendf(MonitorField_2,"Sampletime: %u µs", SampleTime); // output to graph label
    dtostrf(TimePerSample,0,1,outstr1); // convert float to string 
    Panel.sendf(MonitorField_3,"Time/sample: %s µs", outstr1 ); // output to graph label
    
    // search trigger point
    for (int i=0; i < MaxSampleValues-1; i++) // loop over the sample buffer
    {
      if( ( TriggerEdgeRizing && (SampleValues[i] < TriggerValue && SampleValues[i+1] >= TriggerValue)) || //rizing
          (!TriggerEdgeRizing && (SampleValues[i] > TriggerValue && SampleValues[i+1] <= TriggerValue)) )  //faling
      { 
        if (abs((int)TriggerPos-(MaxSampleValues/2)) > abs(i-(MaxSampleValues/2))) TriggerPos = i; // close to middel of buff.
        TriggerCount++; // count the number of trigger points (freq. calc.)
        if (FirstTriggerPos == 0) FirstTriggerPos = i; // first trigger position (freq.calc)
        LastTriggerPos = i; // last trigger position (freq. calc.)
      }
      if (SampleValues[i] < SampleMin) SampleMin = SampleValues[i]; // find lowest value in output
      if (SampleValues[i] > SampleMax) SampleMax = SampleValues[i]; // find highest value in output
    }

    // check trigger found
    if (TriggerPos == 0)
    { // no trigger found
      Panel.send(Led_13,"$OFF"); // show no trigger
      if (TriggerMode==Auto) TriggerPos = GraphValues/2; //in auto mode keep on running
    }
    else
      Panel.send(Led_13,"$RED"); // show trigger found
      
    if(TriggerMode == Single) TriggerPos = FirstTriggerPos;
    
    // determine window start point
    if( TriggerPos-(GraphValues/2) <= 0) 
      WindowStart = triggershift;
    else
      WindowStart = TriggerPos-(GraphValues/2) + triggershift;

    // output window
    if ( TriggerPos > 0 || TriggerMode==Auto) // if valid window or auto mode do display
    {
      for (int i = WindowStart; i < WindowStart + GraphValues; i++) // loop over 
      { 
        if (i >= 0 && i <= SampleIndex-1) // within the buffer?
        { // yes
          byte SampleValue = (byte) constrain(((float)(SampleValues[i]-(ACSelect*128))/VDiv) + vpos+(ACSelect*128),0,255); // Calculate value
          // the ACSelect keeps the verical position centered around the set positon when in AC mode.
          // in DC mode 0 is in the bottom.
          //byte SampleValue = (byte) constrain(((float)(SampleValues[i])/VDiv) + vpos,0,255); // Calculate value
          Panel.send(GraphValue_1, SampleValue); // send value to static graph
        }
        else
          Panel.send(GraphValue_1, (byte)0); // outside the buffer send 0
      }
    }

    // output caption
    tmpfloat = ((float)SampleMin/51.0); // min scanvalue / (255/5V = 51 unit/volt) = min. voltage
    if(ACSelect) tmpfloat -= VCCValue/2.0;
    dtostrf(tmpfloat * AttenuatorValue,0,VDecimalCount,outstr1); // convert float to string
    tmpfloat = ((float)SampleMax/51.0); // max scanvalue / (255/5V = 51 unit/volt) = max. voltage
    if(ACSelect) tmpfloat -= VCCValue/2.0;
    dtostrf(tmpfloat * AttenuatorValue,0,VDecimalCount,outstr2); // convert float to string
    tmpfloat = (float)(SampleMax-SampleMin)/51.0;
    dtostrf(tmpfloat * AttenuatorValue,0,VDecimalCount,outstr3); // convert float to string
    Panel.send(GraphText,F("$WHITE"));
    Panel.sendf(GraphCaption_1,"Vmin %sV - Vmax %sV - Vpp %sV", outstr1, outstr2, outstr3); // Output to graph caption 

    // output graph labels
    Panel.sendf(GraphLabel_1,"Vmin %s V - Vmax %s V", outstr1, outstr2); // Output to graph label
    Panel.sendf(GraphLabel_2,"Vpp %s V", outstr3); // Output to graph label
    Period = ((float)(LastTriggerPos - FirstTriggerPos) / ((float) TriggerCount - 1)) * ((float) TimePerSample);
    dtostrf(Period/1000.0,0,2,outstr1);
    Panel.sendf(GraphLabel_3,"Period: %s ms",outstr1);
    Frequency = 1000000.0/Period;
    dtostrf(Frequency,0,1,outstr2);
    Panel.sendf(GraphLabel_4,"Freq %s Hz",outstr2);
    
    // output sub caption
    Panel.send(GraphText,F("$YELLOW"));
    Panel.send(GraphText,_Point(5,200));
    Panel.sendf(GraphText, "T=%s ms f=%s Hz", outstr1, outstr2);

    // frame indicator off
    Panel.send(Led_12, F("$OFF"));

    SampleReady = false; // Set for next samplre run
    Sampling = false; // 

    if(TriggerMode == Single) // single event stop running
    {  
      SingleEventTrig = false;
      RunState=false;
      DisplayStatic();
    }
  }
}


//-----------------------------------------------------------------------------------------------
void InitADConversion()
{ 
  ADCSRA  = 0; //clear ADCSRA register
  ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // AD Prescaler 16 (011).
  ADCSRA |= (1 << ADIE) | (1 << ADEN); // Interrupt Enable, AD Enable.
  ADCSRB  = 0; //clear ADCSRB register 
  ADMUX   = 0; //clear ADMUX register (A0 input default)
  ADMUX   = (1 << ADLAR) | (1 << REFS0); 
  ADMUX   = 0; //clear ADMUX register (A0 input default)
  ADMUX  |= (1 << ADLAR) | (1 << REFS0); // 
#if defined(__AVR_ATmega32U4__)
  ADMUX  |= (1 <<MUX2) | (1 <<MUX1) | (1 <<MUX0); // A0 for ATMEGA 
#endif 
}


//-----------------------------------------------------------------------------------------------
ISR(ADC_vect) //runs when new ADC value is available
{
  if(!(SampleCount++ % msDiv)) SampleValues[SampleIndex++] = ADCH; // store or skip sample value
  
  if(SampleIndex < MaxSampleValues) // check if done
  {
    delayMicroseconds(2);  // delay to make as close as possible to 50uS/sample 
    bitSet( ADCSRA,ADSC);  // no: start next ADC measurement
    if(TriggerMode == Single)
    {
      if( ( TriggerEdgeRizing && (SampleValues[SampleIndex-2] < TriggerValue && SampleValues[SampleIndex-1] >= TriggerValue)) ||
          (!TriggerEdgeRizing && (SampleValues[SampleIndex-2] > TriggerValue && SampleValues[SampleIndex-1] <= TriggerValue)) )
        SingleEventTrig = true;
    }
  } 
  else
    SampleReady = true; // yes: flag ready
}

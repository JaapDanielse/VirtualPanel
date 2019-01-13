// Sampler Module

#define port_AD_Scope  16 // Pin - AD input current

unsigned long sampletime;

//-----------------------------------------------------------------------------------------------
void SamplerInit()
{
  pinMode(port_AD_Scope, INPUT);
  InitADConversion();
}

//-----------------------------------------------------------------------------------------------
void Sampler()
{
  if ( !SampleReady && !Sampling)
  {
     SampleIndex = 0;   
     SampleCount = 0;
     Sampling = true;
     ADCSRA |= (1 << ADEN);
     ADCSRA |= (1 << ADSC); 
     sampletime = micros();
  }

  if (SampleReady)
  {
    sampletime = micros()-sampletime;
    Panel.Sendf(MonitorField_2,"Sampletime: %10d us", sampletime); // output to graph label
    Panel.Sendf(MonitorField_3,"Time/sample: %6d us", sampletime/((MaxSampleValues+1)*StepSize)); // output to graph label
    
    int   SampleMax  = 0;
    int   SampleMin  = 0;
    int   TriggerPos = 0;
    int   TriggerValue = map(trig,0,220,0,255)-vpos;
    char  outstr1[10];
    char  outstr2[10];
    char  outstr3[10];
    float tmpfloat;
    float frequency;
    
    for (int i=TriggerStart; i < MaxSampleValues-TriggerStart-1; i++)
    {
      if(SampleValues[i] < TriggerValue && SampleValues[i+1] >= TriggerValue)
      { 
        TriggerPos = i;
        break;
      }
    }
    
    if (TriggerPos == 0 || TriggerPos >= MaxSampleValues - MaxGraphValues - TriggerStart - 1)
    {
      TriggerPos = TriggerStart;
      Panel.Send(Led_10,"$OFF");
    }
    else
      Panel.Send(Led_10,"$GREEN");
    
    for (int i=TriggerPos + triggershift; i < MaxGraphValues + TriggerPos + triggershift; i++)
    { 
      byte SampleValue = (byte) constrain(((float)SampleValues[i]/vdiv)+vpos,0,255);
      Panel.Send(GraphValue_1,SampleValue); // Send value to static graph
      
      if (SampleValues[i] < SampleMin) SampleMin = SampleValues[i]; // find lowest value in output
      if (SampleValues[i] > SampleMax) SampleMax = SampleValues[i]; // find highest value in output    
    }
    
    tmpfloat = (float)SampleMin/51.0; // min scanvalue / (255/5V = 51 unit/volt) = min. voltage
    dtostrf(tmpfloat,0,2,outstr1); // convert float to string
    tmpfloat = (float)SampleMax/51.0; // max scanvalue / (255/5V = 51 unit/volt) = max. voltage
    dtostrf(tmpfloat,0,2,outstr2); // convert float to string
    tmpfloat = (float)(SampleMax-SampleMin)/51.0;
    dtostrf(tmpfloat,0,2,outstr3); // convert float to string
    Panel.Sendf(GraphCaption_1,"Vmin %s - V Vmax %s - V Vpp %s V", outstr1, outstr2, outstr3); // Output to graph caption 

    Panel.Sendf(GraphLabel_1,"Scan count: %d",ScanCount++); // output to graph label
    Panel.Sendf(GraphLabel_2,"Vmin %s V - Vmax %s V", outstr1, outstr2); // Output to graph label
    Panel.Sendf(GraphLabel_3,"Vpp %s V", outstr3); // Output to graph label
    dtostrf(frequency,0,2,outstr1);
    Panel.Sendf(GraphLabel_4,"Freq: %s Hz",outstr1);

    Panel.Sendf(MonitorField_1,"vert-pos: %d",vpos); // output to graph label

    SampleReady = false; // Set for next samplre run
    Sampling = false; // 
  }
}


//-----------------------------------------------------------------------------------------------
void InitADConversion()
{ 
//  ADCSRA = 0; //clear ADCSRA register
//  //ADCSRA = (1 << ADPS0) | (1 << ADPS2) | (1 << ADIE) | (1 << ADEN); // prescaler/32, interr.ena., AD ena, Start conv.
//  ADCSRA = (1 << ADPS2) | (1 << ADIE) | (1 << ADEN); // prescaler/16, interr.ena., AD dis, Start conv.
//  ADCSRB = 0; //clear ADCSRB register
//  ADMUX = 0; //clear ADMUX register
//  ADMUX = (1 << ADLAR) | (1 << REFS0); 
//  ADATE

  ADCSRA = 0;                                           //clear ADCSRA register
  ADCSRA |= (1 << ADIE) | (0 << ADEN) | (1 << ADATE);    // Int En, AD En, Auto Trig En
  ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // AD Prescaler /16 (0-1-1)
  ADCSRB = 0;                                           //clear ADCSRB register
  ADMUX  = 0; //clear ADMUX register
  ADMUX  = (1 << ADLAR) | (1 << REFS0);                 // ADC Left Adjust result, 5V Voltage Ref Select
 
}


//-----------------------------------------------------------------------------------------------
ISR(ADC_vect) //runs when new ADC value is available
{
  if(!(SampleCount++ % StepSize)) SampleValues[SampleIndex++] = ADCH;
  
  if(SampleIndex >= MaxSampleValues)
  {
    bitClear(ADCSRA,ADEN);
    bitClear(ADCSRA,ADSC);
    //ADCSRA |= (0 << ADEN) | (0 << ADSC);    // AD Ena
    SampleReady = true;
  }
}


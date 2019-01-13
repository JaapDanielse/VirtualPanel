//  Periodic AD Sampler

//  AD Conversion times:
//            Prescaler /  4 = 0,25 us  x 13 clks/conv = 3,25 us  (   42 clk steps)
//            at 20 samples / div = 20 x 3,25 = 130 us            (  840 clk steps)

//            Prescaler /  8 = 0,5 us  x 13 clks/conv = 6,5 us    (  104 clk steps)
//            at 20 samples / div = 20 x 6,5 = 130 us             ( 2080 clk steps)

//            Prescaler / 16 = 1,0 us  x 13 clks/conv = 13  us    (  208 clk steps)
//            at 20 samples / div = 20 x 13  = 260 us             ( 4160 clk steps)

//            Prescaler / 32 = 2,0 us  x 13 clks/conv = 26  us    (  416 clk steps)
//            at 20 samples / div = 20 x 26  = 520 us             ( 8320 clk steps)

//            Prescaler / 64 = 4,0 us  x 13 clks/conv = 52  us    (  832 clk steps)
//            at 20 samples / div = 20 x 52  = 1040 us            (16640 clk steps)

//  Example:  20 Samples / division (1 ms)
//            Countdown Sample Intervals in 62,5 ns (1/16000000) Clock steps
//            1 ms = 10^-3 / (62,5 x 10^-9) = 16000 Clock steps
//            16000 / 20 Samples = 800 Clock steps between Samples
//            if Clock steps between Samples are less than 65535 there is no Overflow
//            these are counted in the Compare Match-B mode

//  Time Base step intervals:

//  Case      time/div   clks/div    clks/sample interval   overflows   remainder  AD-Prescaler  AD Sampletime
//                               (clks/div / 20 samples/div) 
//   1         100us       1600             80      5us          0          80         4?
//   2         200us       3200            160     10us          0         160         4           3,25us
//   3         400us       6400            320     20us          0         320         8 or 16      6,5us (/8)
//   4           1ms      16000            800     50us          0         800        16             13us
//   5           2ms      32000           1600    100us          0        1600        32             26us
//   6           4ms      64000           3200    200us          0        3200        64             52us
//   7          10ms     160000           8000    500us (508us)  0        8000        64
//   8          20ms     320000          16000      1ms          0       16000        64
//   9          40ms     640000          32000      2ms          0       32000        64
//  10         100ms    1600000          80000      5ms          1       14464        64
//  11         200ms    3200000         160000     10ms          2       28928        64
//  12         400ms    6400000         320000     20ms          4       57856        64
//  13           1 s   16000000         800000     50ms         12       13568        64
//  14           2 s   32000000        1600000    100ms         24       27136        64
//  15           4 s   64000000        3200000    200ms         48       54272        64
//  16          10 s  160000000        8000000    500ms        122        4608        64

//-----------------------------------------------------------------------------------------------

  #define port_AD_Scope  16 // Pin - AD input current
  #define LedPin    13                 // Blink Led

//  byte          TB = 5;                // TimeBase mode 10ms (1...16 / 100us ... 10s)
  byte          ADPrescale = 0;        // Prescale 1=/4, 2=/8, 3=/16, 4=/32, 5=/64
  byte          OverflowCounter = 0;   // Overflow Counter
  byte          Overflows = 0;         // Countable Overflows


  unsigned long sampletime;
  
  unsigned long TimeBase =  10;        // Time Base speed in ms/div
  unsigned long TBClks   = 800;        // Number of Time Base Clocks / div
  boolean       LedOn = false;         // 


//-----------------------------------------------------------------------------------------------
void SamplerInit()
{
  pinMode(port_AD_Scope, INPUT);
  pinMode(LedPin, OUTPUT);       // D13
  digitalWrite(LedPin, LOW);
  Init_TC_1();
  InitADConversion();
  SetTimeBase(usDivSelIdx+1);
}


//-----------------------------------------------------------------------------------------------
void Sampler()
{
  if ( !SampleReady && !Sampling)
  {
     OverflowCounter = 0;
     SampleIndex = 0;   
     Sampling = true;
     TCCR1B |= (1<<CS10);  // Start Sampling
     sampletime = micros();
  }

  if (SampleReady)
  {
    sampletime = micros()-sampletime;
    Panel.Sendf(MonitorField_2,"Sampletime: %6d us",sampletime); // output to graph label
    Panel.Sendf(MonitorField_3,"Time/sample: %6d us",sampletime/(MaxSampleValues+1)); // output to graph label
    
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
void Init_TC_1()
{
  TCCR1A = 0;                                  // T/C-1 Control Reg-A
  TIMSK1 = 0;                                  // Reset TC-1 Interrupt Mask Reg
  OverflowCounter = 0;                         // Overflow counter
} 


//-----------------------------------------------------------------------------------------------
void InitADConversion()
{ 
  ADCSRA = (1 << ADIE) | (1 << ADEN) | (1 << ADATE);    // Int En, AD En, Auto Trig En
  ADCSRB = (1 << ADTS2) | (0 << ADTS1) | (1 << ADTS0);  // Select Trigger on TC-1 Compare Match B
  ADMUX  = (1 << ADLAR) | (1 << REFS0);                 // ADC Left Adjust result, 5V Voltage Ref Select
}


//-----------------------------------------------------------------------------------------------
void SetTimeBase(int TB)
{
//-------------------------------------------------------------
// Set TimeBase parameters

  TCCR1B = (0<<CS12) | (0<<CS11) | (0<<CS10);  // No prescaling / F-in = 16MHz
  TCNT1H =  0;           // Reset Timer/Counter-1
  TCNT1L =  0;  

  switch (TB)
  {
//--------------------------- 100us ---------------------------
     case 1:
       OCR1BH =  0;                // Jitter > AD-ISR?
       OCR1BL =  80;               // Table value = 80
       Overflows = 0;
       SetADPrescale(1);           // /4
       break;
//--------------------------- 200us ---------------------------
     case 2:
       OCR1BH =   0;               // Jitter > AD-ISR?
       OCR1BL = 160;               // Table value = 160
       Overflows = 0;
       SetADPrescale(2);           // /8
       break;
//--------------------------- 400us ---------------------------
     case 3:
       OCR1BH = 300 >> 8;          // Tuned to 21,8us (jitter > AD-ISR?)
       OCR1BL = 300;               // Table value = 320
       Overflows = 0;
       SetADPrescale(2);           // /8
       break;
//---------------------------   1ms ---------------------------
     case 4:
       OCR1BH = 752 >> 8;          // Fine Tuned to 50us
       OCR1BL = 752;               // Table value = 800
       Overflows = 0;
       SetADPrescale(2);           // /16
       break;
//---------------------------   2ms ---------------------------
     case 5:
       OCR1BH = 1550 >> 8;         // Fine Tuned to 100us
       OCR1BL = 1550;              // Table value = 1600
       Overflows = 0;
       SetADPrescale(3);           // /32
       break;
//---------------------------   4ms ---------------------------
     case 6:
       OCR1BH = 3140 >> 8;         // Fine Tuned to 200us
       OCR1BL = 3140;              // Table value = 3200
       Overflows = 0;
       SetADPrescale(5);           // /64
       break;
//---------------------------  10ms ---------------------------
     case 7:
       OCR1BH = 7920 >> 8;         // Fine Tuned to 500us
       OCR1BL = 7920;              // Table value = 8000
       Overflows = 0;
       SetADPrescale(5);           // /64
       break;
//---------------------------  20ms ---------------------------
     case 8:
       OCR1BH = 15850 >> 8;        // Fine Tuned to 1ms
       OCR1BL = 15850;             // Table value = 16000
       Overflows = 0;
       SetADPrescale(5);           // /64
       break;
//---------------------------  40ms ---------------------------
     case 9:
       OCR1BH = 31800 >> 8;        // Fine Tuned to 2ms
       OCR1BL = 31800;             // Table value = 32000
       Overflows = 0;
       SetADPrescale(5);           // /64
       break;
//--------------------------- 100ms ---------------------------
     case 10:
       OCR1BH = 14000 >> 8;        // Fine Tuned to 5ms
       OCR1BL = 14000;             // Table value = 14464
       Overflows = 1;
       SetADPrescale(5);           // /64
       break;
//--------------------------- 200ms ---------------------------
     case 11:
       OCR1BH = 28000 >> 8;        // Fine Tuned to 10ms
       OCR1BL = 28000;             // Table value = 28928 
       Overflows = 2;
       SetADPrescale(5);           // /64
       break;
//--------------------------- 400ms ---------------------------
     case 12:
       OCR1BH = 56000 >> 8;        // Fine Tuned to 20ms
       OCR1BL = 56000;             // Table value = 57856
       Overflows = 4;
       SetADPrescale(5);           // /64
       break;
//---------------------------    1s ---------------------------
     case 13:
       OCR1BH = 10000 >> 8;        // Fine Tuned to 50ms
       OCR1BL = 10000;             // Table value = 13568
       Overflows = 12;             // Countable Overflows
       SetADPrescale(5);           // /64
       break;
//---------------------------    2s ---------------------------
     case 14:
       OCR1BH = 20000 >> 8;        // Fine Tuned to 100ms
       OCR1BL = 20000;             // Table value = 27136
       Overflows = 24;
       SetADPrescale(5);           // /64
    break;
//---------------------------    4s ---------------------------
     case 15:
       OCR1BH = 40000 >> 8;        // Fine Tuned to 200ms
       OCR1BL = 40000;             // Table value = 54272
       Overflows = 48;             // Countable Overflows
       SetADPrescale(5);
       break;
//---------------------------   10s ---------------------------
     case 16:  //    10s
       OCR1BH = 10000 >> 8;        // Fine Tuned to 500ms
       OCR1BL = 10000;             // Table value = 4608
       Overflows = 121;            // Table value = 122
       SetADPrescale(5);           // /64
       break;
  }  
//-------------------------------------------------------------
// Set Count detection to Overflow or Compare Match

  if (Overflows >=1) 
   {
     TIMSK1 = (1<<TOIE1) | (0<<OCIE1B);  // En Ovfl Int / Dis Outp Comp Match-B 
   }
  else
   {
     TIMSK1 = (0<<TOIE1) | (1<<OCIE1B);  // Dis Ovfl Int / En Outp Comp Match-B 
     TIFR1  = (1<<OCF1B);                // Output Compare B Match Flag
   }
//-------------------------------------------------------------
// Reset Timer/Counter-1 Register 

   TCNT1H =  0;                                 // Write High Byte First
   TCNT1L =  0;                                 // Reset T/C-1 Register
   TCCR1B = (0<<CS12) | (0<<CS11) | (0<<CS10);  // No prescaling / F-in = 16MHz

   Sampling = false;

}


//-----------------------------------------------------------------------------------------------
void SetADPrescale(byte ADPrescale)
{
//-------------------------------------------------------------
// Set AD Converter Prescaler Mode
  switch (ADPrescale)
  {
//---------------------------   /4  ---------------------------
     case 1:
       ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // AD Prescaler /4 (0-1-0)
//       Serial.println("AD prescale /4");
     break;
//---------------------------   /8  ---------------------------
     case 2:
       ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // AD Prescaler /8 (0-1-1)
//       Serial.println("AD prescale /8");
     break;
//---------------------------  /16  ---------------------------
     case 3:
       ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); // AD Prescaler /16 (1-0-0)
//       Serial.println("AD prescale /16");
     break;
//---------------------------  /32  ---------------------------
     case 4:
       ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0); // AD Prescaler /32 (1-0-1)
//       Serial.println("AD prescale /32");
     break;
//---------------------------  /64  ---------------------------
     case 5:
       ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // AD Prescaler /64 (1-1-0)
//       Serial.println("AD prescale /64");
     break;
  }
}

//-----------------------------------------------------------------------------------------------
// Timer-1 Overflow Interrupt Service Routine
ISR(TIMER1_OVF_vect)
{
  OverflowCounter++;     // increment overflow counter
  if (OverflowCounter == Overflows)
   {
     TIMSK1 = (0<<TOIE1) | (1<<OCIE1B); // Dis Overflow Interrupt / En Outp Comp Match    
     TIFR1  = (1<<OCF1B);               // Output Compare B Match Flag
   }
}

//-----------------------------------------------------------------------------------------------
ISR(TIMER1_COMPB_vect)    // Timer-1 Compare Match-B Interrupt Service Routine
{
  TCNT1H =  0;        // Reset T/C-1 Register
  TCNT1L =  0;        

  LedOn=!LedOn;                            // for Tuning only > Remove !
  if (LedOn) digitalWrite(LedPin, HIGH);   // for Tuning only > Remove !
  else digitalWrite(LedPin, LOW);          // for Tuning only > Remove !

  OverflowCounter = 0;
  
  if (Overflows >= 1)
  {
    TIMSK1 = (1<<TOIE1) | (0<<OCIE1B);     // En Overflow Interrupt / Dis Outp Comp Match    
  }
}

//-----------------------------------------------------------------------------------------------
ISR(ADC_vect) //runs when new ADC value is available
{
  SampleValues[SampleIndex++] = ADCH;
  
  if(SampleIndex >= MaxSampleValues)
  {
    TCCR1B = (0<<CS12) | (0<<CS11) | (0<<CS10);  // No prescaling / F-in = 16MHz
//    TCCR1B |= (0<<CS10 );   // Stop Sampling
    TCNT1H =  0;           // Reset Timer/Counter-1
    TCNT1L =  0;  
    SampleIndex=0;
    SampleReady = true;
  }
}



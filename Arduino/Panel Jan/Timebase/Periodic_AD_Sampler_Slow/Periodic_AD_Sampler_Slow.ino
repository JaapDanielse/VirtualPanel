
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

//  Case      time/div   clks/div    clks/sample interval   overflows   remainder  AD-Prescaler
//                               (clks/div / 20 samples/div) 
//   1         100us       1600             80      5us          0          80         4?
//   2         200us       3200            160     10us          0         160         4           3,25us
//   3         400us       6400            320     20us          0         320         8 or 16      6,5us (/8)
//   4           1ms      16000            800     50us          0         800        16             13us
//   5           2ms      32000           1600    100us          0        1600        32             26us
//   6           4ms      64000           3200    200us          0        3200        64             52us
//   7          10ms     160000           8000    500us          0        8000        64
//   8          20ms     320000          16000      1ms          0       16000        64
//   9          40ms     640000          32000      2ms          0       32000        64
//  10         100ms    1600000          80000      5ms          1       14464        64
//  11         200ms    3200000         160000     10ms          2       28928        64
//  12         400ms    6400000         320000     20ms          4       57856        64
//  13           1 s   16000000         800000     50ms         12       13568        64
//  14           2 s   32000000        1600000    100ms         24       27136        64
//  15           4 s   64000000        3200000    200ms         48       54272        32
//  16          10 s  160000000        8000000    500ms        122        4608        64

//-----------------------------------------------------------------------------------------------
  
  #define LedPin    13                 // Blink Led

  byte          TC1_L = 0;             // TC1 Counter Save
  byte          TC1_H = 0;             // TC1 Counter Save
  unsigned int  TC1   = 0;             // TC1

  byte          CR1_L = 0;             // Compare Save
  byte          CR1_H = 0;             // Compare Save
  unsigned int  CR1   = 0;             // Compare

  byte          TB = 6;               // TimeBase mode 100ms  (100us ... 10s)
  byte          ADPrescale = 0;        // Prescale 1=/4, 2=/8, 3=/16, 4=/32, 5=/64
  byte          SampleValues = 0;      // AD Storage
  byte          OverflowCounter = 0;   // Overflow Counter
  byte          Overflows = 0;         // Countable Overflows


  unsigned long TimeBase =  10;        // Time Base speed in ms/div
  unsigned long TBClks   = 800;        // Number of Time Base Clocks / div
  boolean       LedOn = false;         // 

/*  
  unsigned int  TrimValue = 0;     // the value after the last Overflow
*/
//-----------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  Serial.println("AD Sampling Test");
  pinMode(LedPin, OUTPUT);       // D13
  digitalWrite(LedPin, LOW);
//  MyPanel.Init();
  Init_TC_1();
  InitADConversion();
  SetTimeBase();
}

//-----------------------------------------------------------------------------------------------
void Init_TC_1()
{
  TCCR1A = 0;                                  // T/C-1 Control Reg-A
//  TCCR1B = (0<<CS12) | (1<<CS11) | (0<<CS10);  // Prescaling /64
//  TCCR1B = (0<<CS12) | (0<<CS11) | (1<<CS10);  // No prescaling / F-in = 16MHz
//  TIMSK1 = 0;                                  // Reset TC-1 Interrupt Mask Reg
//  TIMSK1 = (1<<OCIE1B);                        // Enable Interrupt on Counter Overflow

//  TCNT1H =  0;        // Write High Byte First
//  TCNT1L =  0;        // Reset T/C-1 Register

  OverflowCounter = 0;        // Overflow counter
} 

//-----------------------------------------------------------------------------------------------
void InitADConversion()
{ 
  ADCSRA = (1 << ADIE) | (1 << ADEN) | (1 << ADATE);    // Int En, AD En, Auto Trig En
  ADCSRB = (1 << ADTS2) | (0 << ADTS1) | (1 << ADTS0);  // Select Trigger on TC-1 Compare Match B
  ADMUX  = (1 << ADLAR) | (1 << REFS0);                 // ADC Left Adjust result, 5V Voltage Ref Select
}

//-----------------------------------------------------------------------------------------------
void SetTimeBase()
{
  TCCR1B = (0<<CS12) | (0<<CS11) | (0<<CS10);  // No TC-1 input
//-------------------------------------------------------------
// Set TimeBase parameters

  switch (TB)
  {
//--------------------------- 100us ---------------------------
     case 1:
       OCR1BH =  0;                // Output Compare Register-B
       OCR1BL =  80;               // No Ovflows in this range
       Overflows = 0;              // Countable Overflows
       ADPrescale = 1;             // Prescale /4
       Serial.println("100us");
     break;
//--------------------------- 200us ---------------------------
     case 2:
       OCR1BH =   0;               // Output Compare Register-B
       OCR1BL = 160;               // No Ovflows in this range
       Overflows = 0;              // Countable Overflows
       ADPrescale = 2;             // Prescale /8
       Serial.println("200us");
     break;
//--------------------------- 400us ---------------------------
     case 3:
       OCR1BH = 320 >> 8;          // Output Compare Register-B
       OCR1BL = 320;               // No Ovflows in this range
       Overflows = 0;              // Countable Overflows
       ADPrescale = 2;             // Prescale /8
       Serial.println("400us");
     break;
//---------------------------   1ms ---------------------------
     case 4:
       OCR1BH = 800 >> 8;          // Output Compare Register-B
       OCR1BL = 800;               // No Ovflows in this range
       Overflows = 0;              // Countable Overflows
       ADPrescale = 3;             // Prescale /16
       Serial.println("1ms");
     break;
//---------------------------   2ms ---------------------------
     case 5:
       OCR1BH = 1600 >> 8;         // Output Compare Register-B
       OCR1BL = 1600;              // No Ovflows in this range
       Overflows = 0;              // Countable Overflows
       ADPrescale = 4;             // Prescale /32
       Serial.println("2ms");
     break;
//---------------------------   4ms ---------------------------
     case 6:
       OCR1BH = 3200 >> 8;         // Output Compare Register-B
       OCR1BL = 3200;              // No Ovflows in this range
       Overflows = 0;              // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("4ms");
     break;
//---------------------------  10ms ---------------------------
     case 7:
       OCR1BH = 8000 >> 8;         // Output Compare Register-B
       OCR1BL = 8000;              // No Ovflows in this range
       Overflows = 0;              // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("10ms");
     break;
//---------------------------  20ms ---------------------------
     case 8:
       OCR1BH = 16000 >> 8;        // Output Compare Register-B
       OCR1BL = 16000;             // No Ovflows in this range
       Overflows = 0;              // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("20ms");
     break;
//---------------------------  40ms ---------------------------
     case 9:
       OCR1BH = 32000 >> 8;        // Output Compare Register-B
       OCR1BL = 32000;             // No Ovflows in this range
       Overflows = 0;              // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("40ms");
     break;
//--------------------------- 100ms ---------------------------
     case 10:
       OCR1BH = 14464 >> 8;        // Output Compare Register-B
       OCR1BL = 14464;             // 1 Ovflow in this range
       Overflows = 1;              // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("100ms");
     break;
//--------------------------- 200ms ---------------------------
     case 11:
       OCR1BH = 28928 >> 8;        // Output Compare Register-B
       OCR1BL = 28928;             // 2 Ovfl's in this range
       Overflows = 2;              // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("200ms");
     break;
//--------------------------- 400ms ---------------------------
     case 12:
       OCR1BH = 57856 >> 8;        // Output Compare Register-B
       OCR1BL = 57856;             // 4 Ovfl's in this range
       Overflows = 4;              // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("400ms");
     break;
//---------------------------    1s ---------------------------
     case 13:
       OCR1BH = 13568 >> 8;        // Output Compare Register-B
       OCR1BL = 13568;             // 12 Ovfl's in this range
       Overflows = 12;             // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("1s");
     break;
//---------------------------    2s ---------------------------
     case 14:
       OCR1BH = 27136 >> 8;        // Output Compare Register-B
       OCR1BL = 27136;             // 24 Ovfl's in this range
       Overflows = 24;             // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("2s");
    break;
//---------------------------    4s ---------------------------
     case 15:
       OCR1BH = 54272 >> 8;        // Output Compare Register-B
       OCR1BL = 54272;             // 48 Ovfl's in this range
       Overflows = 48;              // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("4s");
     break;
//---------------------------   10s ---------------------------
     case 16:  //    10s
       OCR1BH = 4608 >> 8;         // Output Compare Register-B
       OCR1BL = 4608;              // 122 Ovfl's in this range
       Overflows = 122;            // Countable Overflows
       ADPrescale = 5;             // /64
       Serial.println("10s");
     break;
  }
  
//-------------------------------------------------------------
// Set Count detection to Overflow or Compare Match
  if (Overflows >=1) 
   {
//     TIMSK1 = 0;                         // Reset TC-1 Interrupt Mask Reg
     TIMSK1 = (1<<TOIE1) | (0<<OCIE1B);  // En Ovfl Int / Dis Outp Comp Match-B 
     Serial.print(Overflows);
     Serial.println(" Ovfls");
   }
  else
   {
//     TIMSK1 = 0;                         // Reset TC-1 Interrupt Mask Reg
     TIMSK1 = (0<<TOIE1) | (1<<OCIE1B);  // Dis Ovfl Int / En Outp Comp Match-B 
     TIFR1  = (1<<OCF1B);                // Output Compare B Match Flag !!!
     Serial.println("No Ovfls");
   }

//-------------------------------------------------------------
// Set AD Converter Prescaler Mode
  switch (ADPrescale)
  {
//---------------------------   /4  ---------------------------
     case 1:
       bitClear (ADCSRA, ADPS2);   // AD Prescaler /4 (0-1-0)
       bitSet   (ADCSRA, ADPS1);
       bitClear (ADCSRA, ADPS0);
       Serial.println("AD prescale /4");
     break;
//---------------------------   /8  ---------------------------
     case 2:
       bitClear (ADCSRA, ADPS2);   // AD Prescaler /8 (0-1-1)
       bitSet   (ADCSRA, ADPS1);
       bitSet   (ADCSRA, ADPS0);
       Serial.println("AD prescale /8");
     break;
//---------------------------  /16  ---------------------------
     case 3:
       bitSet   (ADCSRA, ADPS2);   // AD Prescaler /16 (1-0-0)
       bitClear (ADCSRA, ADPS1);
       bitClear (ADCSRA, ADPS0);
       Serial.println("AD prescale /16");
     break;
//---------------------------  /32  ---------------------------
     case 4:
       ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0); // AD Prescaler /32 (1-0-1)
//       bitSet   (ADCSRA, ADPS2);   // AD Prescaler /32 (1-0-1)
//       bitClear (ADCSRA, ADPS1);
//       bitSet   (ADCSRA, ADPS0);
       Serial.println("AD prescale /32");
     break;
//---------------------------  /64  ---------------------------
     case 5:
       ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // AD Prescaler /64 (1-1-0)
//       bitSet   (ADCSRA, ADPS2);   // AD Prescaler /64 (1-1-0)
//       bitSet   (ADCSRA, ADPS1);
//       bitClear (ADCSRA, ADPS0);
       Serial.println("AD prescale /64");
     break;
  }
//-------------------------------------------------------------
// Reset TC-1 Register

  TCNT1H =  0;                    // Write High Byte First
  TCNT1L =  0;                    // Reset T/C-1 Register

//-------------------------------------------------------------

//  Serial.println("");
  TCCR1B = (0<<CS12) | (1<<CS11) | (0<<CS10);  // Prescaling /64
//  TCCR1B = (0<<CS12) | (0<<CS11) | (1<<CS10);  // No prescaling / F-in = 16MHz
}

//-----------------------------------------------------------------------------------------------
// Timer-1 Overflow Interrupt Service Routine
ISR(TIMER1_OVF_vect)
{
  OverflowCounter++;     // increment overflow counter
  Serial.print("Overflow : ");
  Serial.println(OverflowCounter);
  if (OverflowCounter == Overflows)
   {
//     TIMSK1 = 0; //     
     TIMSK1 = (0<<TOIE1) | (1<<OCIE1B); // Dis Overflow Interrupt / En Outp Comp Match    
     TIFR1 = (1<<OCF1B);                // Output Compare B Match Flag !!!
   }
}

//-----------------------------------------------------------------------------------------------
ISR(TIMER1_COMPB_vect)    // Timer-1 Compare Match-B Interrupt Service Routine
{
  TC1_L = TCNT1L;         // TC1 Counter Save
  TC1_H = TCNT1H;         //

  TCNT1H =  0;            // Write High Byte First
  TCNT1L =  0;            // Reset T/C-1 Register

  TC1   = TC1_H << 8;     //
  TC1  += TC1_L;          // TC1
  Serial.print("Comp TC-1 : ");
  Serial.println(TC1);

  CR1_L = OCR1BL;         // CM1 Counter Save
  CR1_H = OCR1BH;         //
  CR1   = CR1_H << 8;     //
  CR1  += CR1_L;          // CompReg-1-B
  Serial.print("Comp Match : ");
  Serial.println(CR1);
  Serial.println(" ");

  CR1_L = 0;              // Compare Save
  CR1_H = 0;              // Compare Save
  CR1   = 0;              // Compare

  LedOn=!LedOn; 
  if (LedOn) digitalWrite(LedPin, HIGH);
  else digitalWrite(LedPin, LOW);  

  OverflowCounter = 0;
  
  if (Overflows >= 1)  // 
  {
//    TIMSK1 =  0;
    TIMSK1 = (1<<TOIE1) | (0<<OCIE1B); // En Overflow Interrupt / Dis Outp Comp Match    
  }
  
//  TCNT1H =  0;   // Write TCNT1High First
//  TCNT1L =  0;   // Reset Timer/Counter-1  

}

//-----------------------------------------------------------------------------------------------
ISR(ADC_vect) //runs when new ADC value is available
{
 SampleValues = ADCH;
 Serial.println(SampleValues);
/*  
  if(Sampling) SampleValues[SampleIndex] = ADCH;
  if(++SampleCount % StepSize == 0) SampleIndex++;
  if(SampleIndex < MaxSampleValues)
    bitSet( ADCSRA,ADSC);  // start next ADC measurement  
  else
    SampleReady = true;
*/
}

//-----------------------------------------------------------------------------------------------
void loop()
{
//   for (TB=1; TB <= 16; TB++)
//   {
//     SetTimeBase();
//     delay(6000);
//   }
}

//-----------------------------------------------------------------------------------------------




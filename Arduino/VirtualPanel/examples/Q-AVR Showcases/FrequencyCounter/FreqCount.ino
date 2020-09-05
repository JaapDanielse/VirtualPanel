
  bool measuring = false;
  
  unsigned long  maxFreq = 5000000; //4550000
  //unsigned int tovf1 = 0; // Overflow counter
  unsigned long gateTime = 1000000; // Measuring Time
  unsigned int  TC1_Ovf = 0; // Overflow counter
  unsigned long measureTimer = 0;
  unsigned long measureStart = 0;
  unsigned long measureStop = 0;

// Timer 1 is connected to Pin 5 as external source.
// Mesurement is taken during 1 second, measured in micro seconds 
// The 16-bit Timer 1 counter overflows after 65536 counts
// tovfl (using overflow interrupt will keep track of how many times we overflow


//------------------------------------------------------------------------
ISR(TIMER1_OVF_vect) // Timer 1 Overflow interrupt service routine
{
  if (measuring == false) 
  {
     measureStart = micros();
     measureTimer = measureStart + gateTime;
     TCNT1H = 0;    // Write TCNT1High First
     TCNT1L = 0;
     TC1_Ovf = 0; // Overflow counter
     measuring = true;
  }
  else
  {
    TC1_Ovf++; // increment overflow counter
  }
}

//------------------------------------------------------------------------
void InitFreqCount()
{
  // Timer 1 will be setup as a counter
  // Maximum frequency is Fclk_io/2
  // (recommended to be < Fclk_io/2.5)
  // Fclk_io is 16MHz
  TCCR1A = 0; // clear A register
  TCCR1B = (1<<CS12) | (1<<CS11) | (1<<CS10);  // Timer 1 external clock source on D5, trigger on rising edge:
  TIMSK1 = (1<<TOIE1); // Will jump into ISR(TIMER1_OVF_vect) when overflowed:
} 


//------------------------------------------------------------------------
float FrequencyCount() 
{
    unsigned long f  = 0; // total count
    unsigned int  f1 = 0; // TC-1 16-bit Counter Lower Byte
    unsigned int  f2 = 0; // TC-1 16-bit Counter Upper Byte
    unsigned long t; // exact measurement time (delta start-stop)
    float freq = 0.0; // calculated frequency

    // setup for measurement
    TCNT1H = 255;    // Write TCNT1High First
    TCNT1L = 254;    // 65530 - Interrupt after 1 count
    TC1_Ovf  = 0;

    measureStart = micros(); // register mesurement start time
    measureTimer = measureStart + gateTime;  
    
    TCCR1B = (1<<CS12) | (1<<CS11) | (1<<CS10);   // Start measurement (enable D5 input)

    while(measureTimer >= micros()); // wait one second   
    
    TCCR1B = 0;     // Stop measurement (disable D5 input)
    measureStop = micros(); // register measurement stop time
     
    f1 = TCNT1L;    // read counter Low byte first
    f2 = TCNT1H;    // read counter High byte
    f = (f2<<8) | f1; // calculate total count
    f += (65536 * TC1_Ovf);
    t = measureStop - measureStart; // calculate measurement duration
    if (!measuring) f = 0;
    measuring = false;
    
    if( f > 0 ) 
      freq = (float)f*(1000000.0 /(float)t); 
    else 
      freq = 0.0;  // calculate frequency

    return freq; // return frequency
}

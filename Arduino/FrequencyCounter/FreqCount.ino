
// Based on Frequency Counter Arduino Sketch by: Jim Lindblom, sparkfun

unsigned int tovf1 = 0; // Overflow counter

// Timer 1 is connected to Pin 5 as external source.
// Mesurement is taken during 1 second, measured in micro seconds 
// The 16-bit Timer 1 counter overflows after 65536 counts
// tovfl (using overflow interrupt will keep track of how many times we overflow


//------------------------------------------------------------------------
ISR(TIMER1_OVF_vect) // Timer 1 Overflow interrupt service routine
{
  tovf1++; // increment overflow counter
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
    unsigned long measureTimer = 0; // one second timer
    unsigned long measureStart = 0; // measurement start time in micros
    unsigned long measureStop  = 0; // measurement stop time in micros
    unsigned long t; // exact measurement time (delta start-stop)
    float freq = 0.0; // calculated frequency

    // setup for measurement
    TCNT1H = 0;  // clear counter High byte
    TCNT1L = 0;  // clear counter Low byte
    tovf1  = 0;  // clear overflow couner

    measureTimer = micros() + 1000000; // setup one second timer in micros
    
    measureStart = micros(); // register mesurement start time
    TCCR1B = (1<<CS12) | (1<<CS11) | (1<<CS10);   // Start measurement (enable D5 input)

    while(measureTimer >= micros()); // wait one second   
    
    TCCR1B = 0;     // Stop measurement (disable D5 input)
    measureStop = micros(); // register measurement stop time
 
    f1 = TCNT1L;    // read counter Low byte first
    f2 = TCNT1H;    // read counter High byte
    f = (f2<<8) | f1; // calculate total count
    f += (65536 * tovf1); // including accounted by overflow
    t = measureStop - measureStart; // calculate measurement duration
    
    if( f > 0) 
      freq = (1.0 / ((float)t / 1000000.0)) * (float)f; 
    else 
      freq = 0.0;  // calculate frequency

        // debug/statistic data to panel
        Panel.Sendf(MonitorField_1,"TCNT1H: %03d",f2);
        Panel.Sendf(MonitorField_2,"TCNT1L: %03d",f1);
        Panel.Sendf(MonitorField_3,"Overflow: %03d ", tovf1);
        Panel.Sendf(MonitorField_4,"Micros: %6ld ", t);

    return freq; // return frequency
}





 // Frequency Counter Arduino Sketch
 // by: Jim Lindblom
 // SparkFun Electronics
 // License: Beerware

unsigned int tovf1 = 0; // Overflow counter

// Timer 1 is our counter
// 16-bit counter overflows after 65536 counts
// tovfl will keep track of how many times we overflow

//------------------------------------------------------------------------
ISR(TIMER1_OVF_vect) // Timer 1 interrupt service routine
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
  TCCR1A = 0; // 
  TCCR1B = (1<<CS12) | (1<<CS11) | (1<<CS10);  // External clock source on D5, trigger on rising edge:
  TIMSK1 = (1<<TOIE1); // Will jump into ISR(TIMER1_OVF_vect) when overflowed:
} 


//------------------------------------------------------------------------
float FrequencyCount() 
{
    unsigned long f = 0;     // Measured Frequency
    unsigned int  f1 = 0;     // TC-1 16-bit Counter Lower Byte
    unsigned int  f2 = 0;     // TC-1 16-bit Counter Upper Byte
    unsigned long temp = 0;
    unsigned long measureTimer = 0;
    unsigned long measureStart = 0;
    unsigned long measureStop = 0;
    unsigned long t;
    float freq = 0.0;
  
    TCNT1H = 0;    // Write TCNT1High First
    TCNT1L = 0;
    tovf1  = 0;

    measureTimer = micros() + 1000000;
    
    measureStart = micros();
    TCCR1B = (1<<CS12) | (1<<CS11) | (1<<CS10);   // Enable Input Pin - Mux (Page 135)

    while(measureTimer >= micros());    
    
    TCCR1B = 0;     // Disable Input Pin - Mux (Page 135)
    measureStop = micros();
 
    f1 = TCNT1L;    // Read TCNT1Low First
    f2 = TCNT1H;
    f = (f2<<8) | f1;
    f += (65536 * tovf1);
    t = measureStop - measureStart;
    freq = (1.0 / (float (t)/1000000.0)) * float (f);
    freq -= freq / 1000.0;
    
    MyPanel.Sendf(StatField_1,"TCNT1H: %03d",f2);
    MyPanel.Sendf(StatField_2,"TCNT1L: %03d",f1);
    MyPanel.Sendf(StatField_3,"Overflow: %03d ", tovf1);
    MyPanel.Sendf(StatField_4,"Micros: %6ld ", t);

    return freq;
}




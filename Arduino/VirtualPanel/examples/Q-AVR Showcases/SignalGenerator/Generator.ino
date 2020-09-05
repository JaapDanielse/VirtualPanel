//-----------------------------------------------------------------------------------------------
// Initiate 16-bit T/C-1 in fast PWM - Mode-14 (No Prescaling = 3,86kHz) 

void InitSignalGenerator() // setup PWM 12 bit.
{ 
  pinMode( 9, OUTPUT); // Output pin ATMega328 
  pinMode( 11, OUTPUT); // OutputPin Mega2560 / Mega1280
  
  TCCR1A = 0;                                              // Reset Control Register A        (Page 132)
  TCCR1A = (1 << COM1A1) | (1 << WGM11) | (0 << WGM10) ;   // Enable Fast PWM on OC1A (Pin 9) OC1B (pin 10)
  TCCR1B = 0;                                              // Reset Control Register B        (Page 132)
  TCCR1B = (1 << WGM13) | (1 << WGM12) ;                   // Enable Fast PWM on OC1A (Pin 9) OC1B (pin 10)


  ICR1H = 0;  // Set the TOP value for 12-bit PWM (high byte) frequentie
  ICR1L = 0;  // (low byte)

  OCR1AH = 0;  // Set to 0, Timer/counter-1 Output Compare, Register A (pin9) high byte Duty cycle.
  OCR1AL = 0;  // Low byte 

  TCNT1H = 0;  // Reset the timer/Counter-1 High byte
  TCNT1L = 0;  // Low byte
}
//-----------------------------------------------------------------------------------------------


void SetFrequency(int Prescaler, int TopValue, int Duty)
{

  TCCR1A = 0;                                              // Reset Control Register A        (Page 132)
  TCCR1A = (1 << COM1A1) | (1 << WGM11) | (0 << WGM10) ;   // Enable Fast PWM on OC1A (Pin 9) OC1B (pin 10)
  TCCR1B = 0;                                              // Reset Control Register B        (Page 132)
  TCCR1B = (1 << WGM13) | (1 << WGM12) ;                   // Enable Fast PWM on OC1A (Pin 9) OC1B (pin 10)
  
  // Prescaler
  if (Prescaler == 0)   TCCR1B |= (0 << CS12) | (0 << CS11) | (0 << CS10);
  if (Prescaler == 1)   TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
  if (Prescaler == 8)   TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
  if (Prescaler == 64)  TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
  if (Prescaler == 256) TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);

  // Topvalue
  ICR1H = TopValue >> 8; // Set the frequentie Top value
  ICR1L = TopValue;      // (Low byte)

  // Duty
  OCR1AH = Duty >> 8;  // Set to 0, Timer/counter-1 Output Compare, Register A (pin9) high byte Duty cycle.
  OCR1AL = Duty;  // Low byte 

}

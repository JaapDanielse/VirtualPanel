//-----------------------------------------------------------------------------------------------
// Initiate 16-bit T/C-1 in fast 12 bit(TOP) PWM - Mode-14 (No Prescaling = 3,86kHz) 

void InitSignalGenerator() // setup PWM 12 bit.
{ 
  TCCR1A = 0;                                              // Reset Control Register A        (Page 132)
  TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << COM1B1);   // Enable Fast PWM on OC1A (Pin 9) OC1B (pin 10)

  ICR1H = 4095 >> 8; // Set the TOP value for 12-bit PWM (high byte) frequentie
  ICR1L = 255;      // (low byte)

  OCR1AH = 0;  // Set to 0, Timer/counter-1 Output Compare, Register A (pin9) high byte Duty cycle.
  OCR1AL = 0;  // Low byte 

  TCNT1H = 0;  // Reset the timer/Counter-1 High byte
  TCNT1L = 0;  // Low byte

//-----------------------------------------------------------------------------------------------





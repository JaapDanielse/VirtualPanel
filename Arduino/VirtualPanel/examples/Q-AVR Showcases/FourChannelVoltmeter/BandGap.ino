// BandGap Module
// Determine Bandgap based on (external measured) Arduino AREF (VCC) 
// Determine ArduinoVCC based on known bandgap Voltage
// This module will be available in a separate library
// In this example to avoid depencency

#if defined(ARDUINO_ARCH_AVR)

//---------------------------------------------------------------
float VCCVoltage(float BandGapVoltage)
{
  return (BandGapVoltage / BandGapAD() * 1023.0);
}

//---------------------------------------------------------------
float BandGapVoltage(float AREF)
{
    return ((BandGapAD() * AREF) / 1023.0);  
}

//---------------------------------------------------------------
float BandGapAD()
{ 
  const int16_t AccSampleCount = 256;
  uint32_t AccBG = 0;
  

  ADCSRA = (1 << ADPS0) | (1 << ADPS2) | (0 << ADIE) | (1 << ADEN) | (0 << ADSC); 
  #if defined(__AVR_ATmega328P__) 
    ADMUX = (1 << REFS0) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1); 
  #elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = (1 << REFS0) | (1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1); 
  #endif
  delay(5); // 
  for (int16_t i=0; i<AccSampleCount; i++)
  {
    bitSet( ADCSRA,ADSC); // Start ADC conversion
    while (bitRead(ADCSRA,ADSC));
    AccBG += ADC; 
  }
  return (float)AccBG/(float)AccSampleCount;
}

#else
  #error “This library only supports boards with an AVR processor.”
#endif

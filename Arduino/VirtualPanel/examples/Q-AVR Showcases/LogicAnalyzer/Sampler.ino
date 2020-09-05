
//---------------------------------------------------------------------------------
void SampleInit()
{
  DDRB  = B11000000; // set all pins on port B (pin 8-13) as inputs
}


//---------------------------------------------------------------------------------
void Sample()
{
  unsigned long SampleTime;
  char outstr[10];
  bool SwitchNibles = false;
  byte TriggerBitHigh = 0;

  TriggerBitHigh = TriggerBit + 4;

  if(Trigger)
  {
    if(TRizing) SampleBuffer[0]=0xFF; else SampleBuffer[0]=0x00;
    while(1)
    {
      SampleBuffer[0] &= B00001111;
      SampleBuffer[0] |= (B11110000 & (PINB << 4)); // read pin 8,9,10,11 into high buffer byte
      if( bitRead(SampleBuffer[0],TriggerBitHigh)==TRizing && bitRead(SampleBuffer[0],TriggerBit)==!TRizing)
      { SwitchNibles = true; break; }
      delayMicroseconds(SampleSpeed);
  
      SampleBuffer[0] &= B11110000;
      SampleBuffer[0] |= (B00001111 & PINB);  // read pin 8,9,10,11 into low buffer byte
      if( bitRead(SampleBuffer[0],TriggerBit)==TRizing && bitRead(SampleBuffer[0],TriggerBitHigh)==!TRizing) 
      { break; }
      delayMicroseconds(SampleSpeed);

      if (Serial.available()) return;
    }
  }
 
  SampleTime = micros();
 
  for (SampleBufferIdx=Trigger; SampleBufferIdx <= SampleBufSize; SampleBufferIdx++)
  {
    SampleBuffer[SampleBufferIdx]  = PINB << 4; // read pin 8,9,10,11 into high buffer byte
    delayMicroseconds(SampleSpeed);
    SampleBuffer[SampleBufferIdx] |= (B00001111 & PINB);  // read pin 8,9,10,11 into low buffer byte
    delayMicroseconds(SampleSpeed);
    
    if (Serial.available()) return;
  }
  
  SampleTime = micros() - SampleTime;
  float OneSampleTime = (float)SampleTime/(float)(SampleBufSize*2);
  dtostrf(OneSampleTime,0,1,outstr);
  Panel.sendf(MonitorField_1,F("Time/sample: %s µs"),outstr); // output to graph label

  if (SwitchNibles)
  {
    byte temp = SampleBuffer[0];
    SampleBuffer[0] = temp << 4;
    SampleBuffer[0] |= (B00001111 & (temp >> 4)) ;
  }
  

}

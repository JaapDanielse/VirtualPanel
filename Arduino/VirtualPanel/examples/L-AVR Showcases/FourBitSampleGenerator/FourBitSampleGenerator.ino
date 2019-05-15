void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("signalSource");
  DDRB = B00001111;
  

}

void loop() 
{
  static int i=0;
  #define Speed 1000 //

  Serial.print(i++);

  // D11,D10,D9,D8
  
  PORTB = B00000101;
  delayMicroseconds(Speed);
  PORTB = B00000100;
  delayMicroseconds(Speed);
  PORTB = B00000011;
  delayMicroseconds(Speed);
  PORTB = B00001000;
  delayMicroseconds(Speed);
  PORTB = B00001101;
  delayMicroseconds(Speed);
  PORTB = B00001110;
  delayMicroseconds(Speed);
  PORTB = B00001001;
  delayMicroseconds(Speed);
  PORTB = B00000000;
  delayMicroseconds(Speed);



//  PORTB = B00001010;
//  delayMicroseconds(Speed);
//  PORTB = B00000010;
//  delayMicroseconds(Speed);
//  PORTB = B00001100;
//  delayMicroseconds(Speed);
//  PORTB = B00000001;
//  delayMicroseconds(Speed);
//  PORTB = B00001011;
//  delayMicroseconds(Speed);
//  PORTB = B00000111;
//  delayMicroseconds(Speed);
//  PORTB = B00001001;
//  delayMicroseconds(Speed);
//  PORTB = B00000001;
//  delayMicroseconds(Speed);
}
